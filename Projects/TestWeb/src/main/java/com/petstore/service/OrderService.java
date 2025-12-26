package com.petstore.service;

import com.petstore.dao.OrderDAO;
import com.petstore.model.Cart;
import com.petstore.model.CartItem;
import com.petstore.model.Order;
import com.petstore.model.OrderItem;
import com.petstore.model.User;
import com.petstore.util.DBUtil;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

public class OrderService {
    private OrderDAO orderDAO = new OrderDAO();

    public boolean placeOrder(User user, Cart cart) {
        if (cart == null || cart.getItems().isEmpty()) {
            return false;
        }

        Connection conn = null;
        try {
            conn = DBUtil.getConnection();
            conn.setAutoCommit(false);

            Order order = new Order();
            order.setUserId(user.getId());
            order.setTotalAmount(cart.getTotalAmount());
            order.setStatus("PENDING");
            order.setShippingAddress(user.getAddress());
            order.setShippingPhone(user.getPhone());

            Integer orderId = orderDAO.createOrder(conn, order);
            if (orderId == null) {
                throw new SQLException("Failed to create order");
            }

            for (CartItem cartItem : cart.getItems()) {
                OrderItem orderItem = new OrderItem();
                orderItem.setOrderId(orderId);
                orderItem.setProductId(cartItem.getProduct().getId());
                orderItem.setQuantity(cartItem.getQuantity());
                orderItem.setPrice(cartItem.getProduct().getPrice());
                orderDAO.createOrderItem(conn, orderItem);
            }

            conn.commit();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            if (conn != null) {
                try {
                    conn.rollback();
                } catch (SQLException ex) {
                    ex.printStackTrace();
                }
            }
            return false;
        } finally {
            DBUtil.close(conn, null);
        }
    }

    public List<Order> getUserOrders(Integer userId) {
        return orderDAO.findByUserId(userId);
    }

    public List<Order> getAllOrders() {
        return orderDAO.findAll();
    }

    public boolean updateOrderStatus(int orderId, String status) {
        return orderDAO.updateStatus(orderId, status);
    }
}
