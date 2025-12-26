package com.petstore.servlet.admin;

import com.petstore.model.Product;
import com.petstore.service.ProductService;
import com.petstore.servlet.UploadServlet;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.MultipartConfig;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.Part;

import java.io.InputStream;
import java.io.IOException;
import java.math.BigDecimal;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.util.Locale;
import java.util.UUID;

@WebServlet("/admin/products")
@MultipartConfig
public class AdminProductServlet extends HttpServlet {
    private ProductService productService = new ProductService();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String action = req.getParameter("action");
        if ("delete".equals(action)) {
            int id = Integer.parseInt(req.getParameter("id"));
            productService.deleteProduct(id);
            resp.sendRedirect("products");
        } else if ("edit".equals(action)) {
            int id = Integer.parseInt(req.getParameter("id"));
            Product product = productService.getProductById(id);
            req.setAttribute("product", product);
            req.getRequestDispatcher("/admin/product_form.jsp").forward(req, resp);
        } else if ("new".equals(action)) {
            req.getRequestDispatcher("/admin/product_form.jsp").forward(req, resp);
        } else {
            req.setAttribute("products", productService.getAllProducts());
            req.getRequestDispatcher("/admin/product_list.jsp").forward(req, resp);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setCharacterEncoding("UTF-8");
        String idStr = req.getParameter("id");
        String name = req.getParameter("name");
        String description = req.getParameter("description");
        String priceStr = req.getParameter("price");
        String stockStr = req.getParameter("stock");
        String imageUrl = trimToNull(req.getParameter("imageUrl"));
        boolean isHot = req.getParameter("isHot") != null;
        int categoryId = Integer.parseInt(req.getParameter("categoryId"));

        Part imagePart = safeGetPart(req, "image");
        if (imagePart != null && imagePart.getSize() > 0) {
            String contentType = imagePart.getContentType();
            if (contentType != null && contentType.toLowerCase(Locale.ROOT).startsWith("image/")) {
                Path baseDir = UploadServlet.getUploadBaseDir();
                Files.createDirectories(baseDir);
                String ext = guessExt(imagePart.getSubmittedFileName());
                String fileName = "product-" + UUID.randomUUID() + ext;
                Path target = baseDir.resolve(fileName).normalize();
                try (InputStream in = imagePart.getInputStream()) {
                    Files.copy(in, target, StandardCopyOption.REPLACE_EXISTING);
                }
                imageUrl = "uploads/" + fileName;
            }
        }

        Product product = new Product();
        product.setName(name);
        product.setDescription(description);
        product.setPrice(new BigDecimal(priceStr));
        product.setStock(Integer.parseInt(stockStr));
        product.setImageUrl(imageUrl);
        product.setIsHot(isHot);
        product.setCategoryId(categoryId);

        if (idStr != null && !idStr.isEmpty()) {
            product.setId(Integer.parseInt(idStr));
            if (product.getImageUrl() == null) {
                Product existing = productService.getProductById(product.getId());
                if (existing != null) {
                    product.setImageUrl(existing.getImageUrl());
                }
            }
            productService.updateProduct(product);
        } else {
            productService.createProduct(product);
        }
        resp.sendRedirect("products");
    }

    private Part safeGetPart(HttpServletRequest req, String name) {
        try {
            return req.getPart(name);
        } catch (Exception e) {
            return null;
        }
    }

    private String trimToNull(String s) {
        if (s == null) return null;
        String t = s.trim();
        return t.isEmpty() ? null : t;
    }

    private String guessExt(String submittedName) {
        if (submittedName == null) return "";
        int dot = submittedName.lastIndexOf('.');
        if (dot < 0 || dot == submittedName.length() - 1) return "";
        String ext = submittedName.substring(dot).toLowerCase(Locale.ROOT);
        if (ext.length() > 10) return "";
        return ext;
    }
}
