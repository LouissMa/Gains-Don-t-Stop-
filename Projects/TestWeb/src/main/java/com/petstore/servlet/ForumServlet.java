package com.petstore.servlet;

import com.petstore.dao.ForumDAO;
import com.petstore.model.ForumPost;
import com.petstore.model.Product;
import com.petstore.model.User;
import com.petstore.service.ProductService;
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
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.UUID;

@WebServlet("/forum")
@MultipartConfig
public class ForumServlet extends HttpServlet {
    private ForumDAO forumDAO = new ForumDAO();
    private ProductService productService = new ProductService();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        forumDAO.seedDemoPostsIfEmpty();
        req.setAttribute("posts", forumDAO.findAll());
        req.setAttribute("products", productService.getAllProducts());
        req.getRequestDispatcher("/forum.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        req.setCharacterEncoding("UTF-8");
        User user = getLoginUser(req.getSession());
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        String title = trimToNull(req.getParameter("title"));
        String content = trimToNull(req.getParameter("content"));
        Integer productId = parseNullableInt(req.getParameter("productId"));

        if (title == null || content == null) {
            resp.sendRedirect("forum?error=invalid");
            return;
        }

        if (productId != null && productId <= 0) productId = null;

        if (productId != null) {
            Product p = productService.getProductById(productId);
            if (p == null) productId = null;
        }

        ForumPost post = new ForumPost();
        post.setUserId(user.getId());
        post.setProductId(productId);
        post.setTitle(title);
        post.setContent(content);

        int postId = forumDAO.addPost(post);
        if (postId <= 0) {
            resp.sendRedirect("forum?error=save_failed");
            return;
        }

        List<String> urls = saveImageParts(req.getParts(), "images", "post-" + postId + "-");
        forumDAO.addPostImages(postId, urls);
        resp.sendRedirect("forum?posted=1&t=" + System.currentTimeMillis());
    }

    private List<String> saveImageParts(Iterable<Part> parts, String partName, String prefix) throws IOException {
        List<String> urls = new ArrayList<>();
        Path baseDir = UploadServlet.getUploadBaseDir();
        Files.createDirectories(baseDir);

        for (Part part : parts) {
            if (!partName.equals(part.getName())) continue;
            if (part.getSize() <= 0) continue;
            String contentType = part.getContentType();
            if (contentType == null || !contentType.toLowerCase(Locale.ROOT).startsWith("image/")) continue;

            String ext = guessExt(part.getSubmittedFileName());
            String fileName = prefix + UUID.randomUUID() + ext;
            Path target = baseDir.resolve(fileName).normalize();
            try (InputStream in = part.getInputStream()) {
                Files.copy(in, target, StandardCopyOption.REPLACE_EXISTING);
            }
            urls.add("uploads/" + fileName);
        }
        return urls;
    }

    private Integer parseNullableInt(String s) {
        try {
            if (s == null) return null;
            s = s.trim();
            if (s.isEmpty()) return null;
            return Integer.parseInt(s);
        } catch (Exception e) {
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
