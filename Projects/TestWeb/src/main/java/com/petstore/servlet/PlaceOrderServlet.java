package com.petstore.servlet;

import com.petstore.model.Cart;
import com.petstore.model.User;
import com.petstore.service.OrderService;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;

@WebServlet("/place-order")
public class PlaceOrderServlet extends HttpServlet {
    private OrderService orderService = new OrderService();

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        Cart cart = (Cart) session.getAttribute("cart");

        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        if (cart != null && !cart.getItems().isEmpty()) {
            boolean success = orderService.placeOrder(user, cart);
            if (success) {
                cart.clear();
                resp.sendRedirect("orders?success=true");
            } else {
                resp.sendRedirect("cart?error=Failed to place order");
            }
        } else {
            resp.sendRedirect("cart");
        }
    }
}
