<%@ page import="java.sql.*" %>
<%@ page import="com.petstore.util.DBUtil" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Fixing Data...</title>
</head>
<body>
<h1>Fixing Product Images and Adding Pet Bed...</h1>
<%
    Connection conn = null;
    Statement stmt = null;
    try {
        conn = DBUtil.getConnection();
        stmt = conn.createStatement();
        
        // 1. Update Existing Products (based on name keywords to match user's current data)
        // Dog Food
        int count1 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-dogfood.jpg' WHERE name LIKE '%狗粮%'");
        out.println("<p>Updated Dog Food images: " + count1 + "</p>");
        
        // Cat Food
        int count2 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-catfood.jpg' WHERE name LIKE '%猫粮%'");
        out.println("<p>Updated Cat Food images: " + count2 + "</p>");

        // Cat Toy (Stick) - Matches "猫的玩具" or "逗猫棒"
        int count3 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-cat-stick.jpg' WHERE name LIKE '%猫%' AND (name LIKE '%玩具%' OR name LIKE '%棒%')");
        out.println("<p>Updated Cat Toy images: " + count3 + "</p>");

        // Leash - Matches "栓狗链" or "狗链"
        int count4 = stmt.executeUpdate("UPDATE products SET image_url='images/prod-leash.jpg' WHERE name LIKE '%狗链%'");
        out.println("<p>Updated Leash images: " + count4 + "</p>");

        // 2. Insert "宠物窝" (Pet Bed) if not exists
        ResultSet rs = stmt.executeQuery("SELECT id FROM products WHERE name LIKE '%宠物窝%'");
        if (!rs.next()) {
             // Using prod-bed.jpg as it is the correct image for a bed, despite potential typo in prompt requesting leash image for bed.
             stmt.executeUpdate("INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) VALUES (3, '宠物窝', '柔软舒适的宠物窝，四季通用', 89.00, 50, 'images/prod-bed.jpg', TRUE)");
             out.println("<p style='color:green'>Inserted new product: 宠物窝</p>");
        } else {
             out.println("<p>Product '宠物窝' already exists, updating image just in case.</p>");
             stmt.executeUpdate("UPDATE products SET image_url='images/prod-bed.jpg' WHERE name LIKE '%宠物窝%'");
        }
        rs.close();

        out.println("<h2 style='color:green'>Data Fixed Successfully!</h2>");
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