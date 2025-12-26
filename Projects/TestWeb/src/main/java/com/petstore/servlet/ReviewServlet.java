package com.petstore.servlet;

import com.petstore.dao.ReviewDAO;
import com.petstore.model.Review;
import com.petstore.model.User;
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

@WebServlet("/review")
@MultipartConfig
public class ReviewServlet extends HttpServlet {
    private ReviewDAO reviewDAO = new ReviewDAO();

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, ServletException {
        req.setCharacterEncoding("UTF-8");
        User user = getLoginUser(req.getSession());
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        int productId = parseInt(req.getParameter("productId"), -1);
        int rating = parseInt(req.getParameter("rating"), 0);
        String content = trimToNull(req.getParameter("content"));

        if (productId <= 0 || rating < 1 || rating > 5 || content == null) {
            resp.sendRedirect("product?id=" + productId);
            return;
        }

        Review review = new Review();
        review.setUserId(user.getId());
        review.setProductId(productId);
        review.setRating(rating);
        review.setContent(content);
        int reviewId = reviewDAO.addReview(review);
        if (reviewId <= 0) {
            resp.sendRedirect("product?id=" + productId + "&error=review_failed");
            return;
        }

        List<String> urls = saveImageParts(req.getParts(), "images", "review-" + reviewId + "-");
        reviewDAO.addReviewImages(reviewId, urls);
        resp.sendRedirect("product?id=" + productId + "&reviewed=1&t=" + System.currentTimeMillis());
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

    private int parseInt(String s, int def) {
        try {
            return Integer.parseInt(s);
        } catch (Exception e) {
            return def;
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
