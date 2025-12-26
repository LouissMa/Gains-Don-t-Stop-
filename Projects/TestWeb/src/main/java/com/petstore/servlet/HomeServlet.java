package com.petstore.servlet;

import com.petstore.model.User;
import com.petstore.service.ProductService;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

@WebServlet("/home")
public class HomeServlet extends HttpServlet {
    private ProductService productService = new ProductService();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");

        req.setAttribute("hotProducts", productService.getHotProducts());
        if (user != null) {
            req.setAttribute("recommendedProducts", productService.getRecommendedProducts(user));
        }
        req.getRequestDispatcher("/home.jsp").forward(req, resp);
    }
}
