package com.petstore.servlet.admin;

import com.petstore.dao.ForumDAO;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet("/admin/forum")
public class AdminForumServlet extends HttpServlet {
    private ForumDAO forumDAO = new ForumDAO();

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setAttribute("posts", forumDAO.findAll());
        req.getRequestDispatcher("/admin/forum_list.jsp").forward(req, resp);
    }
}

