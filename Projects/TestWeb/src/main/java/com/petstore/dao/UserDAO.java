package com.petstore.dao;

import com.petstore.model.User;
import com.petstore.util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;

public class UserDAO {

    public User findByUsername(String username) {
        String sql = "SELECT * FROM users WHERE username = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return mapRowToUser(rs);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public User findById(int id) {
        String sql = "SELECT * FROM users WHERE id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, id);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return mapRowToUser(rs);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean createUser(User user) {
        String sqlV2 = "INSERT INTO users (username, password, email, phone, address, bio, avatar_url, role) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sqlV2)) {
            stmt.setString(1, user.getUsername());
            stmt.setString(2, user.getPassword());
            stmt.setString(3, user.getEmail());
            stmt.setString(4, user.getPhone());
            stmt.setString(5, user.getAddress());
            stmt.setString(6, user.getBio());
            stmt.setString(7, user.getAvatarUrl());
            stmt.setString(8, user.getRole() == null ? "USER" : user.getRole());
            return stmt.executeUpdate() > 0;
        } catch (SQLException e) {
            if (isUnknownColumn(e)) {
                String sqlV1 = "INSERT INTO users (username, password, email, phone, address, role) VALUES (?, ?, ?, ?, ?, ?)";
                try (Connection conn = DBUtil.getConnection();
                     PreparedStatement stmt = conn.prepareStatement(sqlV1)) {
                    stmt.setString(1, user.getUsername());
                    stmt.setString(2, user.getPassword());
                    stmt.setString(3, user.getEmail());
                    stmt.setString(4, user.getPhone());
                    stmt.setString(5, user.getAddress());
                    stmt.setString(6, user.getRole() == null ? "USER" : user.getRole());
                    return stmt.executeUpdate() > 0;
                } catch (SQLException ex) {
                    ex.printStackTrace();
                    return false;
                }
            }
            e.printStackTrace();
            return false;
        }
    }

    public boolean updateProfile(User user) {
        String sqlV2 = "UPDATE users SET email = ?, phone = ?, address = ?, bio = ?, avatar_url = ? WHERE id = ?";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sqlV2)) {
            stmt.setString(1, user.getEmail());
            stmt.setString(2, user.getPhone());
            stmt.setString(3, user.getAddress());
            stmt.setString(4, user.getBio());
            stmt.setString(5, user.getAvatarUrl());
            stmt.setInt(6, user.getId());
            return stmt.executeUpdate() > 0;
        } catch (SQLException e) {
            if (isUnknownColumn(e)) {
                String sqlV1 = "UPDATE users SET email = ?, phone = ?, address = ? WHERE id = ?";
                try (Connection conn = DBUtil.getConnection();
                     PreparedStatement stmt = conn.prepareStatement(sqlV1)) {
                    stmt.setString(1, user.getEmail());
                    stmt.setString(2, user.getPhone());
                    stmt.setString(3, user.getAddress());
                    stmt.setInt(4, user.getId());
                    return stmt.executeUpdate() > 0;
                } catch (SQLException ex) {
                    ex.printStackTrace();
                    return false;
                }
            }
            e.printStackTrace();
            return false;
        }
    }

    public int countUsersCreatedThisMonth() {
        String sql = "SELECT COUNT(*) AS c FROM users WHERE create_time >= DATE_FORMAT(CURDATE(), '%Y-%m-01')";
        try (Connection conn = DBUtil.getConnection();
             PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {
            if (rs.next()) {
                return rs.getInt("c");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    private User mapRowToUser(ResultSet rs) throws SQLException {
        Set<String> columns = getColumnNames(rs);
        User user = new User();
        user.setId(rs.getInt("id"));
        user.setUsername(rs.getString("username"));
        user.setPassword(rs.getString("password"));
        user.setEmail(rs.getString("email"));
        user.setPhone(rs.getString("phone"));
        user.setAddress(rs.getString("address"));
        if (columns.contains("bio")) {
            user.setBio(rs.getString("bio"));
        }
        if (columns.contains("avatar_url")) {
            user.setAvatarUrl(rs.getString("avatar_url"));
        }
        user.setRole(rs.getString("role"));
        user.setCreateTime(rs.getTimestamp("create_time"));
        return user;
    }

    private Set<String> getColumnNames(ResultSet rs) throws SQLException {
        ResultSetMetaData meta = rs.getMetaData();
        Set<String> cols = new HashSet<>();
        int count = meta.getColumnCount();
        for (int i = 1; i <= count; i++) {
            String label = meta.getColumnLabel(i);
            if (label != null) cols.add(label.toLowerCase(Locale.ROOT));
            String name = meta.getColumnName(i);
            if (name != null) cols.add(name.toLowerCase(Locale.ROOT));
        }
        return cols;
    }

    private boolean isUnknownColumn(SQLException e) {
        String msg = e.getMessage();
        if (msg == null) return false;
        String lower = msg.toLowerCase(Locale.ROOT);
        return lower.contains("unknown column") || lower.contains("column") && lower.contains("doesn't exist");
    }
}
