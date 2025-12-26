<%@ page import="java.sql.*" %>
<%@ page import="com.petstore.util.DBUtil" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Fixing Data V3...</title>
</head>
<body>
<h1>Applying User Requested Database Updates...</h1>
<%
    Connection conn = null;
    Statement stmt = null;
    try {
        conn = DBUtil.getConnection();
        stmt = conn.createStatement();
        
        // 1. Update Existing Products based on exact keywords provided
        
        // "狗粮" -> images/prod-dogfood.jpg
        int count1 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-dogfood.jpg' WHERE name LIKE '%狗粮%'");
        out.println("<p>Updated '狗粮' images: " + count1 + "</p>");
        
        // "猫的玩具" -> images/prod-cat-stick.jpg
        int count2 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-cat-stick.jpg' WHERE name LIKE '%猫的玩具%'");
        out.println("<p>Updated '猫的玩具' images: " + count2 + "</p>");

        // "栓狗链" -> images/prod-leash.jpg
        int count3 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-leash.jpg' WHERE name LIKE '%栓狗链%'");
        out.println("<p>Updated '栓狗链' images: " + count3 + "</p>");
        
        // "猫粮" -> images/prod-catfood.jpg
        int count4 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-catfood.jpg' WHERE name LIKE '%猫粮%'");
        out.println("<p>Updated '猫粮' images: " + count4 + "</p>");

        // 2. Insert or Update "宠物窝"
        // Requirements: Name: "宠物窝", Price: 80.00, Image: "images/prod-leash.jpg" (User specified), Category: 3
        
        ResultSet rs = stmt.executeQuery("SELECT id FROM products WHERE name = '宠物窝'");
        if (!rs.next()) {
             // Insert
             String insertSql = "INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) " +
                                "VALUES (3, '宠物窝', '柔软舒适的宠物窝', 80.00, 50, 'images/prod-leash.jpg', TRUE)";
             stmt.executeUpdate(insertSql);
             out.println("<p style='color:green'>Inserted new product: 宠物窝 (Price: 80.00, Image: images/prod-leash.jpg)</p>");
        } else {
             // Update if exists to match new requirements
             String updateSql = "UPDATE products SET price=80.00, image_url='images/prod-leash.jpg', category_id=3 WHERE name='宠物窝'";
             stmt.executeUpdate(updateSql);
             out.println("<p style='color:blue'>Updated existing product: 宠物窝 (Price set to 80.00, Image set to images/prod-leash.jpg)</p>");
        }
        rs.close();

        out.println("<h2 style='color:green'>Database Updates Completed Successfully!</h2>");
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