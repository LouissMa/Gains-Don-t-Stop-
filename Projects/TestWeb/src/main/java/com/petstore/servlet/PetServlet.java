package com.petstore.servlet;

import com.petstore.dao.PetProfileDAO;
import com.petstore.model.PetProfile;
import com.petstore.model.User;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;

import java.io.IOException;
import java.util.Set;

@WebServlet("/pet")
public class PetServlet extends HttpServlet {
    private PetProfileDAO petProfileDAO = new PetProfileDAO();
    private static final Set<String> ALLOWED_TYPES = Set.of(
            "DOG", "CAT", "PIG", "TURTLE", "RABBIT", "HAMSTER", "BIRD", "FISH", "OTHER"
    );

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String action = req.getParameter("action");
        if ("delete".equals(action)) {
            handleDelete(req, resp);
            return;
        }
        handleList(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String action = req.getParameter("action");
        if ("add".equals(action)) {
            handleAdd(req, resp);
            return;
        }
        resp.sendRedirect("pet?action=list");
    }

    private void handleList(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        User user = getLoginUser(req.getSession());
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        req.setAttribute("pets", petProfileDAO.getPetsByUserId(user.getId()));
        req.getRequestDispatcher("/my_pets.jsp").forward(req, resp);
    }

    private void handleAdd(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        User user = getLoginUser(req.getSession());
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        String name = req.getParameter("name");
        String type = req.getParameter("type");
        String breed = req.getParameter("breed");
        String ageStr = req.getParameter("age");

        int age = 0;
        try {
            age = Integer.parseInt(ageStr);
        } catch (Exception ignored) {}

        if (name != null) name = name.trim();
        if (type != null) type = type.trim().toUpperCase();
        if (breed != null) breed = breed.trim();

        if (name == null || name.isEmpty() || type == null || !ALLOWED_TYPES.contains(type) || breed == null || breed.isEmpty() || age <= 0) {
            resp.sendRedirect("pet?action=list&error=invalid");
            return;
        }

        PetProfile pet = new PetProfile();
        pet.setUserId(user.getId());
        pet.setName(name);
        pet.setType(type);
        pet.setBreed(breed);
        pet.setAge(age);

        boolean ok = petProfileDAO.addPet(pet);
        if (ok) {
            resp.sendRedirect("pet?action=list");
        } else {
            resp.sendRedirect("pet?action=list&error=save_failed");
        }
    }

    private void handleDelete(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        User user = getLoginUser(req.getSession());
        if (user == null) {
            resp.sendRedirect("login");
            return;
        }

        String idStr = req.getParameter("id");
        try {
            int petId = Integer.parseInt(idStr);
            petProfileDAO.deletePet(petId);
        } catch (Exception ignored) {}

        resp.sendRedirect("pet?action=list");
    }

    private User getLoginUser(HttpSession session) {
        return (User) session.getAttribute("user");
    }
}
