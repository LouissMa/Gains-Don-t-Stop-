package com.petstore.service;

import com.petstore.dao.UserDAO;
import com.petstore.model.User;

public class UserService {
    private UserDAO userDAO = new UserDAO();

    public User login(String username, String password) {
        User user = userDAO.findByUsername(username);
        if (user != null && user.getPassword().equals(password)) {
            return user;
        }
        return null;
    }

    public boolean register(User user) {
        if (userDAO.findByUsername(user.getUsername()) != null) {
            return false; // Username already exists
        }
        return userDAO.createUser(user);
    }

    public User getUserById(int id) {
        return userDAO.findById(id);
    }

    public boolean updateProfile(User user) {
        return userDAO.updateProfile(user);
    }
}
