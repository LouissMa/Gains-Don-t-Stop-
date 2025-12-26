package com.petstore.servlet.admin;

import com.petstore.dao.OrderDAO;
import com.petstore.dao.PetProfileDAO;
import com.petstore.dao.ProductDAO;
import com.petstore.dao.UserDAO;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

@WebServlet("/admin/dashboard")
public class AdminDashboardServlet extends HttpServlet {
    private final OrderDAO orderDAO = new OrderDAO();
    private final UserDAO userDAO = new UserDAO();
    private final ProductDAO productDAO = new ProductDAO();
    private final PetProfileDAO petProfileDAO = new PetProfileDAO();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        BigDecimal todaySales = orderDAO.sumTodaySales();
        int pendingOrders = orderDAO.countPendingOrders();
        int newUsersThisMonth = userDAO.countUsersCreatedThisMonth();
        int lowStockCount = productDAO.countLowStock(10);

        int catCount = petProfileDAO.countByTypeKeyword("猫");
        int dogCount = petProfileDAO.countByTypeKeyword("狗");

        LocalDate start = LocalDate.now().minusDays(6);
        Map<LocalDate, Integer> orderCountMap = orderDAO.countOrdersByDaySince(start);
        List<String> labels = new ArrayList<>();
        List<Integer> values = new ArrayList<>();
        for (int i = 0; i < 7; i++) {
            LocalDate d = start.plusDays(i);
            labels.add(d.toString());
            values.add(orderCountMap.getOrDefault(d, 0));
        }

        req.setAttribute("todaySales", todaySales.setScale(2, RoundingMode.HALF_UP).toPlainString());
        req.setAttribute("pendingOrders", pendingOrders);
        req.setAttribute("newUsersThisMonth", newUsersThisMonth);
        req.setAttribute("lowStockCount", lowStockCount);
        req.setAttribute("catCount", catCount);
        req.setAttribute("dogCount", dogCount);
        req.setAttribute("orderTrendLabelsJson", toJsonStringArray(labels));
        req.setAttribute("orderTrendValuesJson", toJsonNumberArray(values));

        req.getRequestDispatcher("/admin/dashboard.jsp").forward(req, resp);
    }

    private String toJsonStringArray(List<String> list) {
        StringBuilder sb = new StringBuilder();
        sb.append('[');
        for (int i = 0; i < list.size(); i++) {
            if (i > 0) sb.append(',');
            sb.append('"').append(escapeJsonString(list.get(i))).append('"');
        }
        sb.append(']');
        return sb.toString();
    }

    private String toJsonNumberArray(List<Integer> list) {
        StringBuilder sb = new StringBuilder();
        sb.append('[');
        for (int i = 0; i < list.size(); i++) {
            if (i > 0) sb.append(',');
            sb.append(list.get(i));
        }
        sb.append(']');
        return sb.toString();
    }

    private String escapeJsonString(String s) {
        if (s == null) return "";
        return s.replace("\\", "\\\\").replace("\"", "\\\"");
    }
}
