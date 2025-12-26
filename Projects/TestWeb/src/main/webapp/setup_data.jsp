<%@ page import="java.sql.*" %>
<%@ page import="com.petstore.util.DBUtil" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Updating Database...</title>
</head>
<body>
<h1>Updating Database with New Products and Images...</h1>
<%
    Connection conn = null;
    Statement stmt = null;
    try {
        conn = DBUtil.getConnection();
        stmt = conn.createStatement();
        
        // 1. Update Categories
        stmt.executeUpdate("UPDATE categories SET name='主粮' WHERE id=1");
        stmt.executeUpdate("UPDATE categories SET name='玩具' WHERE id=2");
        stmt.executeUpdate("UPDATE categories SET name='用品' WHERE id=3");
        
        // 2. Update/Insert Products
        // Note: Using ON DUPLICATE KEY UPDATE might be safer if ID exists, or just specific updates.
        // Assuming IDs 1, 2, 3 exist from previous init.
        
        // Update ID 1: Dog Food
        String sql1 = "UPDATE products SET name='优质狗粮', description='营养均衡的优质狗粮 5kg', price=128.00, image_url='images/prod-dogfood.jpg', is_hot=TRUE WHERE id=1";
        stmt.executeUpdate(sql1);
        
        // Update ID 2: Cat Toy -> Cat Stick
        String sql2 = "UPDATE products SET name='互动逗猫棒', description='色彩鲜艳的互动逗猫棒，猫咪最爱', price=19.90, image_url='images/prod-cat-stick.jpg', is_hot=TRUE WHERE id=2";
        stmt.executeUpdate(sql2);
        
        // Update ID 3: Leash
        String sql3 = "UPDATE products SET name='坚固狗链', description='防爆冲结实耐用的狗绳项圈', price=39.00, image_url='images/prod-leash.jpg', is_hot=FALSE WHERE id=3";
        stmt.executeUpdate(sql3);
        
        // Insert new products if they don't exist (Check by name to avoid duplicates if re-run)
        
        // Cat Food
        ResultSet rs = stmt.executeQuery("SELECT id FROM products WHERE image_url='images/prod-catfood.jpg'");
        if (!rs.next()) {
             stmt.executeUpdate("INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) VALUES (1, '全价猫粮', '美味营养猫粮/猫罐头组合', 88.00, 100, 'images/prod-catfood.jpg', TRUE)");
             out.println("<p>Inserted Cat Food.</p>");
        }
        rs.close();
        
        // Toy Ball
        rs = stmt.executeQuery("SELECT id FROM products WHERE image_url='images/prod-toy-ball.jpg'");
        if (!rs.next()) {
             stmt.executeUpdate("INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) VALUES (2, '耐咬磨牙球', '环保材质磨牙球，结实耐玩', 25.00, 150, 'images/prod-toy-ball.jpg', FALSE)");
             out.println("<p>Inserted Toy Ball.</p>");
        }
        rs.close();
        
        // Pet Bed
        rs = stmt.executeQuery("SELECT id FROM products WHERE image_url='images/prod-bed.jpg'");
        if (!rs.next()) {
             stmt.executeUpdate("INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) VALUES (3, '舒适宠物窝', '四季通用柔软舒适宠物窝垫', 158.00, 30, 'images/prod-bed.jpg', TRUE)");
             out.println("<p>Inserted Pet Bed.</p>");
        }
        rs.close();

        out.println("<h2 style='color:green'>Database Updated Successfully!</h2>");
        out.println("<p><a href='home'>Go to Home Page</a></p>");
        
    } catch (Exception e) {
        out.println("<h2 style='color:red'>Error: " + e.getMessage() + "</h2>");
        e.printStackTrace(new java.io.PrintWriter(out));
    } finally {
        if (stmt != null) stmt.close();
        if (conn != null) conn.close();
    }
%>
</body>
</html>
