package com.petstore.servlet;

import com.petstore.service.ProductService;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/products")
public class ProductListServlet extends HttpServlet {
    private ProductService productService = new ProductService();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String q = req.getParameter("q");
        if (q != null) q = q.trim();

        if (q != null && !q.isEmpty()) {
            req.setAttribute("keyword", q);
            req.setAttribute("products", productService.searchProducts(q));
        } else {
            req.setAttribute("products", productService.getAllProducts());
        }
        req.getRequestDispatcher("/product_list.jsp").forward(req, resp);
    }
}
