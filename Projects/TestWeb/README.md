# Pet Store Online

A simple Java Web application for a pet store, built with Servlet, JSP, and MySQL.

## Features

### User Features
- **Account**: Register, Login, Logout.
- **Products**: Browse hot products, view all products, view product details.
- **Shopping**: Add to cart, update cart, place order.
- **Orders**: View order history.

### Admin Features
- **Dashboard**: View total products and orders count.
- **Product Management**: Add, Edit, Delete products. Set hot recommendations.
- **Order Management**: View all orders, update order status (e.g., Ship, Deliver).

## Setup

1.  **Database**:
    -   Create a MySQL database named `petstore`.
    -   Run the SQL script `src/main/resources/init.sql` to create tables and initial data.
    -   Update `src/main/resources/db.properties` with your MySQL username and password.

2.  **Build**:
    -   This is a Maven project. Use `mvn clean package` to build the WAR file.

3.  **Run**:
    -   Deploy the WAR file to a Servlet container like Tomcat.
    -   Or use a Maven plugin if configured (e.g., `mvn jetty:run` or configure Tomcat in IDE).

## Default Accounts

-   **Admin**: username: `admin`, password: `admin123`
-   **User**: username: `testuser`, password: `123456`
