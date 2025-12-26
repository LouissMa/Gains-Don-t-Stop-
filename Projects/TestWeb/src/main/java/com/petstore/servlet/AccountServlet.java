package com.petstore.servlet;

import com.petstore.dao.ReviewDAO;
import com.petstore.model.User;
import com.petstore.service.UserService;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import jakarta.servlet.http.Part;

import java.io.InputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.Locale;
import java.util.UUID;

@WebServlet("/account")
@MultipartConfig
public class AccountServlet extends HttpServlet {
    private UserService userService = new UserService();
    private ReviewDAO reviewDAO = new ReviewDAO();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        User loginUser = getLoginUser(req.getSession());
        if (loginUser == null) {
            resp.sendRedirect("login");
            return;
        }

        User fresh = userService.getUserById(loginUser.getId());
        if (fresh != null) {
            req.getSession().setAttribute("user", fresh);
            loginUser = fresh;
        }

        req.setAttribute("profile", loginUser);
        req.setAttribute("myReviews", reviewDAO.findByUserId(loginUser.getId()));
        req.getRequestDispatcher("/account.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        User loginUser = getLoginUser(req.getSession());
        if (loginUser == null) {
            resp.sendRedirect("login");
            return;
        }

        String email = trimToNull(req.getParameter("email"));
        String phone = trimToNull(req.getParameter("phone"));
        String address = trimToNull(req.getParameter("address"));
        String bio = trimToNull(req.getParameter("bio"));

        String avatarUrl = loginUser.getAvatarUrl();
        Part avatarPart = safeGetPart(req, "avatar");
        if (avatarPart != null && avatarPart.getSize() > 0) {
            String contentType = avatarPart.getContentType();
            if (contentType != null && contentType.toLowerCase(Locale.ROOT).startsWith("image/")) {
                Path baseDir = UploadServlet.getUploadBaseDir();
                Files.createDirectories(baseDir);
                String submittedName = avatarPart.getSubmittedFileName();
                String ext = guessExt(submittedName);
                String fileName = "avatar-" + loginUser.getId() + "-" + UUID.randomUUID() + ext;
                Path target = baseDir.resolve(fileName).normalize();
                try (InputStream in = avatarPart.getInputStream()) {
                    Files.copy(in, target, StandardCopyOption.REPLACE_EXISTING);
                }
                avatarUrl = "uploads/" + fileName;
            }
        }

        User update = new User();
        update.setId(loginUser.getId());
        update.setEmail(email);
        update.setPhone(phone);
        update.setAddress(address);
        update.setBio(bio);
        update.setAvatarUrl(avatarUrl);

        boolean ok = userService.updateProfile(update);
        if (ok) {
            User fresh = userService.getUserById(loginUser.getId());
            if (fresh != null) {
                req.getSession().setAttribute("user", fresh);
            }
            resp.sendRedirect("account?success=1");
        } else {
            resp.sendRedirect("account?error=save_failed");
        }
    }

    private Part safeGetPart(HttpServletRequest req, String name) {
        try {
            return req.getPart(name);
        } catch (Exception ignored) {
            return null;
        }
    }

    private String trimToNull(String s) {
        if (s == null) return null;
        s = s.trim();
        return s.isEmpty() ? null : s;
    }

    private String guessExt(String fileName) {
        if (fileName == null) return "";
        int idx = fileName.lastIndexOf('.');
        if (idx < 0) return "";
        String ext = fileName.substring(idx).trim();
        if (ext.length() > 10) return "";
        String lower = ext.toLowerCase(Locale.ROOT);
        if (lower.equals(".png") || lower.equals(".jpg") || lower.equals(".jpeg") || lower.equals(".gif") || lower.equals(".webp")) {
            return lower;
        }
        return "";
    }

    private User getLoginUser(HttpSession session) {
        return (User) session.getAttribute("user");
    }
}
