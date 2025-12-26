package com.petstore.dao;

import com.petstore.model.Review;
import com.petstore.util.DBUtil;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ReviewDAO {

    public List<Review> findByProductId(int productId) {
        String sql = "SELECT r.*, u.username, p.name AS product_name " +
                "FROM reviews r " +
                "JOIN users u ON r.user_id = u.id " +
                "JOIN products p ON r.product_id = p.id " +
                "WHERE r.product_id = ? " +
                "ORDER BY r.create_time DESC";
        List<Review> reviews = new ArrayList<>();
        try (Connection conn = DBUtil.getConnection()) {
            ensureReviewTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setInt(1, productId);
                try (ResultSet rs = stmt.executeQuery()) {
                    while (rs.next()) {
                        reviews.add(mapRow(rs));
                    }
                }
                loadImages(conn, reviews);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reviews;
    }

    public List<Review> findByUserId(int userId) {
        String sql = "SELECT r.*, u.username, p.name AS product_name " +
                "FROM reviews r " +
                "JOIN users u ON r.user_id = u.id " +
                "JOIN products p ON r.product_id = p.id " +
                "WHERE r.user_id = ? " +
                "ORDER BY r.create_time DESC";
        List<Review> reviews = new ArrayList<>();
        try (Connection conn = DBUtil.getConnection()) {
            ensureReviewTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setInt(1, userId);
                try (ResultSet rs = stmt.executeQuery()) {
                    while (rs.next()) {
                        reviews.add(mapRow(rs));
                    }
                }
                loadImages(conn, reviews);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reviews;
    }

    public List<Review> findAll() {
        String sql = "SELECT r.*, u.username, p.name AS product_name " +
                "FROM reviews r " +
                "JOIN users u ON r.user_id = u.id " +
                "JOIN products p ON r.product_id = p.id " +
                "ORDER BY r.create_time DESC";
        List<Review> reviews = new ArrayList<>();
        try (Connection conn = DBUtil.getConnection()) {
            ensureReviewTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql);
                 ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    reviews.add(mapRow(rs));
                }
                loadImages(conn, reviews);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return reviews;
    }

    public int addReview(Review review) {
        String sql = "INSERT INTO reviews (user_id, product_id, rating, content) VALUES (?, ?, ?, ?)";
        try (Connection conn = DBUtil.getConnection()) {
            ensureReviewTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
                stmt.setInt(1, review.getUserId());
                stmt.setInt(2, review.getProductId());
                stmt.setInt(3, review.getRating());
                stmt.setString(4, review.getContent());
                int updated = stmt.executeUpdate();
                if (updated <= 0) return -1;
                try (ResultSet rs = stmt.getGeneratedKeys()) {
                    if (rs.next()) {
                        return rs.getInt(1);
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return -1;
    }

    public void addReviewImages(int reviewId, List<String> imageUrls) {
        if (imageUrls == null || imageUrls.isEmpty()) return;
        String sql = "INSERT INTO review_images (review_id, image_url) VALUES (?, ?)";
        try (Connection conn = DBUtil.getConnection()) {
            ensureReviewTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                for (String url : imageUrls) {
                    stmt.setInt(1, reviewId);
                    stmt.setString(2, url);
                    stmt.addBatch();
                }
                stmt.executeBatch();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private Review mapRow(ResultSet rs) throws SQLException {
        Review review = new Review();
        review.setId(rs.getInt("id"));
        review.setUserId(rs.getInt("user_id"));
        review.setProductId(rs.getInt("product_id"));
        review.setRating(rs.getInt("rating"));
        review.setContent(rs.getString("content"));
        review.setCreateTime(rs.getTimestamp("create_time"));
        review.setUsername(rs.getString("username"));
        review.setProductName(rs.getString("product_name"));
        return review;
    }

    private void loadImages(Connection conn, List<Review> reviews) throws SQLException {
        if (reviews == null || reviews.isEmpty()) return;
        Map<Integer, Review> byId = new HashMap<>();
        for (Review r : reviews) {
            if (r.getId() != null) byId.put(r.getId(), r);
        }
        String ids = byId.keySet().stream().map(String::valueOf).collect(Collectors.joining(","));
        if (ids.isEmpty()) return;
        String sql = "SELECT review_id, image_url FROM review_images WHERE review_id IN (" + ids + ")";
        try (PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {
            while (rs.next()) {
                int reviewId = rs.getInt("review_id");
                Review review = byId.get(reviewId);
                if (review != null) {
                    review.getImageUrls().add(rs.getString("image_url"));
                }
            }
        }
    }

    private void ensureReviewTables(Connection conn) throws SQLException {
        try (Statement stmt = conn.createStatement()) {
            try {
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS reviews (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "user_id INT NOT NULL," +
                                "product_id INT NOT NULL," +
                                "rating INT NOT NULL," +
                                "content TEXT NOT NULL," +
                                "create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP," +
                                "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE," +
                                "FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE CASCADE" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS review_images (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "review_id INT NOT NULL," +
                                "image_url VARCHAR(255) NOT NULL," +
                                "FOREIGN KEY (review_id) REFERENCES reviews(id) ON DELETE CASCADE" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
            } catch (SQLException ignored) {
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS reviews (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "user_id INT NOT NULL," +
                                "product_id INT NOT NULL," +
                                "rating INT NOT NULL," +
                                "content TEXT NOT NULL," +
                                "create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS review_images (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "review_id INT NOT NULL," +
                                "image_url VARCHAR(255) NOT NULL" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
            }
        }

        ensureColumnExists(conn, "reviews", "user_id", "ALTER TABLE reviews ADD COLUMN user_id INT NOT NULL");
        ensureColumnExists(conn, "reviews", "product_id", "ALTER TABLE reviews ADD COLUMN product_id INT NOT NULL");
        ensureColumnExists(conn, "reviews", "rating", "ALTER TABLE reviews ADD COLUMN rating INT NOT NULL");
        ensureColumnExists(conn, "reviews", "content", "ALTER TABLE reviews ADD COLUMN content TEXT NOT NULL");
        ensureColumnExists(conn, "reviews", "create_time", "ALTER TABLE reviews ADD COLUMN create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP");

        ensureColumnExists(conn, "review_images", "review_id", "ALTER TABLE review_images ADD COLUMN review_id INT NOT NULL");
        ensureColumnExists(conn, "review_images", "image_url", "ALTER TABLE review_images ADD COLUMN image_url VARCHAR(255) NOT NULL");
    }

    private void ensureColumnExists(Connection conn, String table, String column, String alterSql) throws SQLException {
        String currentDb = null;
        try (PreparedStatement s = conn.prepareStatement("SELECT DATABASE() AS db");
             ResultSet rs = s.executeQuery()) {
            if (rs.next()) currentDb = rs.getString("db");
        }
        if (currentDb == null || currentDb.isBlank()) return;

        String check = "SELECT COUNT(*) AS c FROM information_schema.columns WHERE table_schema = ? AND table_name = ? AND column_name = ?";
        try (PreparedStatement stmt = conn.prepareStatement(check)) {
            stmt.setString(1, currentDb);
            stmt.setString(2, table);
            stmt.setString(3, column);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next() && rs.getInt("c") > 0) return;
            }
        }
        try (Statement stmt = conn.createStatement()) {
            stmt.executeUpdate(alterSql);
        }
    }
}
