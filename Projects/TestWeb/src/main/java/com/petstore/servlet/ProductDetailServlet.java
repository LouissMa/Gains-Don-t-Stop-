package com.petstore.servlet;

import com.petstore.model.Product;
import com.petstore.dao.ReviewDAO;
import com.petstore.service.ProductService;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/product")
public class ProductDetailServlet extends HttpServlet {
    private ProductService productService = new ProductService();
    private ReviewDAO reviewDAO = new ReviewDAO();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String idStr = req.getParameter("id");
        if (idStr != null) {
            try {
                int id = Integer.parseInt(idStr);
                Product product = productService.getProductById(id);
                req.setAttribute("product", product);
                if (product != null) {
                    req.setAttribute("reviews", reviewDAO.findByProductId(id));
                }
                req.getRequestDispatcher("/product_detail.jsp").forward(req, resp);
                return;
            } catch (NumberFormatException e) {
                // Ignore
            }
        }
        resp.sendRedirect("home");
    }
}
