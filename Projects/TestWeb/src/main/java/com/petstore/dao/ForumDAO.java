package com.petstore.dao;

import com.petstore.model.ForumPost;
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
import java.util.Objects;
import java.util.stream.Collectors;

public class ForumDAO {

    public List<ForumPost> findAll() {
        String sql = "SELECT fp.*, u.username, p.name AS product_name " +
                "FROM forum_posts fp " +
                "JOIN users u ON fp.user_id = u.id " +
                "LEFT JOIN products p ON fp.product_id = p.id " +
                "ORDER BY fp.create_time DESC";
        List<ForumPost> posts = new ArrayList<>();
        try (Connection conn = DBUtil.getConnection()) {
            ensureForumTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql);
                 ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    posts.add(mapRow(rs));
                }
                loadImages(conn, posts);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return posts;
    }

    public int countPosts() {
        String sql = "SELECT COUNT(*) AS c FROM forum_posts";
        try (Connection conn = DBUtil.getConnection()) {
            ensureForumTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql);
                 ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt("c");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public void seedDemoPostsIfEmpty() {
        if (countPosts() > 0) return;
        try (Connection conn = DBUtil.getConnection()) {
            ensureForumTables(conn);
            conn.setAutoCommit(false);

            Integer u1 = ensureUser(conn, "mimi", "123456");
            Integer u2 = ensureUser(conn, "rocky", "123456");
            Integer u3 = ensureUser(conn, "lulu", "123456");
            Integer u4 = ensureUser(conn, "doudou", "123456");

            Integer catFoodId = findProductId(conn, "猫粮");
            Integer leashId = findProductId(conn, "狗链");

            Integer p1 = insertPost(conn, Objects.requireNonNullElse(u1, 2), catFoodId, "猫粮适口性真的不错", "这款猫粮颗粒大小合适，香味不冲，挑食猫也愿意吃。吃了两周精神状态不错，便便也正常。");
            if (p1 != null) {
                insertPostImage(conn, p1, "images/论坛猫粮.png");
            }
            Integer p2 = insertPost(conn, Objects.requireNonNullElse(u2, 3), leashId, "栓狗链上手体验", "材质结实，扣子顺滑，拉扯的时候也不勒手。带狗狗出门更安心了。");
            if (p2 != null) {
                insertPostImage(conn, p2, "images/论坛栓狗链.png");
            }

            insertPost(conn, Objects.requireNonNullElse(u3, 4), null, "新手养猫必备清单", "猫砂盆、猫抓板、逗猫棒、化毛膏、指甲剪，建议一步到位，不然后面补买更花钱。");
            insertPost(conn, Objects.requireNonNullElse(u4, 2), null, "狗狗磨牙玩具怎么选？", "优先选耐咬、无异味、边缘不锋利的。太软的几下就咬烂，容易误吞。");
            insertPost(conn, Objects.requireNonNullElse(u1, 2), null, "宠物窝冬天要不要加垫子", "我家猫喜欢软一点的，里面再铺一层小毯子就不容易着凉。");

            conn.commit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public int addPost(ForumPost post) {
        String sql = "INSERT INTO forum_posts (user_id, product_id, title, content) VALUES (?, ?, ?, ?)";
        try (Connection conn = DBUtil.getConnection()) {
            ensureForumTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
                stmt.setInt(1, post.getUserId());
                if (post.getProductId() == null) {
                    stmt.setNull(2, java.sql.Types.INTEGER);
                } else {
                    stmt.setInt(2, post.getProductId());
                }
                stmt.setString(3, post.getTitle());
                stmt.setString(4, post.getContent());
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

    public void addPostImages(int postId, List<String> imageUrls) {
        if (imageUrls == null || imageUrls.isEmpty()) return;
        String sql = "INSERT INTO forum_post_images (post_id, image_url) VALUES (?, ?)";
        try (Connection conn = DBUtil.getConnection()) {
            ensureForumTables(conn);
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                for (String url : imageUrls) {
                    stmt.setInt(1, postId);
                    stmt.setString(2, url);
                    stmt.addBatch();
                }
                stmt.executeBatch();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private ForumPost mapRow(ResultSet rs) throws SQLException {
        ForumPost post = new ForumPost();
        post.setId(rs.getInt("id"));
        post.setUserId(rs.getInt("user_id"));
        int pid = rs.getInt("product_id");
        if (rs.wasNull()) post.setProductId(null);
        else post.setProductId(pid);
        post.setTitle(rs.getString("title"));
        post.setContent(rs.getString("content"));
        post.setCreateTime(rs.getTimestamp("create_time"));
        post.setUsername(rs.getString("username"));
        post.setProductName(rs.getString("product_name"));
        return post;
    }

    private void loadImages(Connection conn, List<ForumPost> posts) throws SQLException {
        if (posts == null || posts.isEmpty()) return;
        Map<Integer, ForumPost> byId = new HashMap<>();
        for (ForumPost p : posts) {
            if (p.getId() != null) byId.put(p.getId(), p);
        }
        String ids = byId.keySet().stream().map(String::valueOf).collect(Collectors.joining(","));
        if (ids.isEmpty()) return;
        String sql = "SELECT post_id, image_url FROM forum_post_images WHERE post_id IN (" + ids + ")";
        try (PreparedStatement stmt = conn.prepareStatement(sql);
             ResultSet rs = stmt.executeQuery()) {
            while (rs.next()) {
                int postId = rs.getInt("post_id");
                ForumPost post = byId.get(postId);
                if (post != null) {
                    post.getImageUrls().add(rs.getString("image_url"));
                }
            }
        }
    }

    private Integer ensureUser(Connection conn, String username, String password) throws SQLException {
        String insert = "INSERT IGNORE INTO users (username, password, role) VALUES (?, ?, 'USER')";
        try (PreparedStatement stmt = conn.prepareStatement(insert)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.executeUpdate();
        }
        String select = "SELECT id FROM users WHERE username = ?";
        try (PreparedStatement stmt = conn.prepareStatement(select)) {
            stmt.setString(1, username);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) return rs.getInt("id");
            }
        }
        return null;
    }

    private Integer findProductId(Connection conn, String keyword) throws SQLException {
        String sql = "SELECT id FROM products WHERE name LIKE ? ORDER BY id ASC LIMIT 1";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, "%" + keyword + "%");
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) return rs.getInt("id");
            }
        }
        return null;
    }

    private Integer insertPost(Connection conn, int userId, Integer productId, String title, String content) throws SQLException {
        String sql = "INSERT INTO forum_posts (user_id, product_id, title, content) VALUES (?, ?, ?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            stmt.setInt(1, userId);
            if (productId == null) stmt.setNull(2, java.sql.Types.INTEGER);
            else stmt.setInt(2, productId);
            stmt.setString(3, title);
            stmt.setString(4, content);
            int updated = stmt.executeUpdate();
            if (updated <= 0) return null;
            try (ResultSet rs = stmt.getGeneratedKeys()) {
                if (rs.next()) return rs.getInt(1);
            }
        }
        return null;
    }

    private void insertPostImage(Connection conn, int postId, String imageUrl) throws SQLException {
        String sql = "INSERT INTO forum_post_images (post_id, image_url) VALUES (?, ?)";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, postId);
            stmt.setString(2, imageUrl);
            stmt.executeUpdate();
        }
    }

    private void ensureForumTables(Connection conn) throws SQLException {
        try (Statement stmt = conn.createStatement()) {
            try {
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS forum_posts (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "user_id INT NOT NULL," +
                                "product_id INT," +
                                "title VARCHAR(100) NOT NULL," +
                                "content TEXT NOT NULL," +
                                "create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP," +
                                "FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE," +
                                "FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE SET NULL" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS forum_post_images (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "post_id INT NOT NULL," +
                                "image_url VARCHAR(255) NOT NULL," +
                                "FOREIGN KEY (post_id) REFERENCES forum_posts(id) ON DELETE CASCADE" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
            } catch (SQLException ignored) {
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS forum_posts (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "user_id INT NOT NULL," +
                                "product_id INT," +
                                "title VARCHAR(100) NOT NULL," +
                                "content TEXT NOT NULL," +
                                "create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
                stmt.executeUpdate(
                        "CREATE TABLE IF NOT EXISTS forum_post_images (" +
                                "id INT AUTO_INCREMENT PRIMARY KEY," +
                                "post_id INT NOT NULL," +
                                "image_url VARCHAR(255) NOT NULL" +
                                ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4"
                );
            }

            ensureColumnExists(conn, "forum_posts", "user_id", "ALTER TABLE forum_posts ADD COLUMN user_id INT NOT NULL");
            ensureColumnExists(conn, "forum_posts", "product_id", "ALTER TABLE forum_posts ADD COLUMN product_id INT NULL");
            ensureColumnExists(conn, "forum_posts", "title", "ALTER TABLE forum_posts ADD COLUMN title VARCHAR(100) NOT NULL");
            ensureColumnExists(conn, "forum_posts", "content", "ALTER TABLE forum_posts ADD COLUMN content TEXT NOT NULL");
            ensureColumnExists(conn, "forum_posts", "create_time", "ALTER TABLE forum_posts ADD COLUMN create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP");

            ensureColumnExists(conn, "forum_post_images", "post_id", "ALTER TABLE forum_post_images ADD COLUMN post_id INT NOT NULL");
            ensureColumnExists(conn, "forum_post_images", "image_url", "ALTER TABLE forum_post_images ADD COLUMN image_url VARCHAR(255) NOT NULL");
        }
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
