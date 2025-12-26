DROP DATABASE IF EXISTS petstore;
CREATE DATABASE petstore CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE petstore;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    email VARCHAR(100),
    phone VARCHAR(20),
    address VARCHAR(255),
    bio TEXT,
    avatar_url VARCHAR(255),
    role VARCHAR(20) DEFAULT 'USER', -- USER, MERCHANT, ADMIN
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE pet_profiles (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    name VARCHAR(50) NOT NULL,
    type VARCHAR(10) NOT NULL,
    breed VARCHAR(50),
    age INT NOT NULL,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE categories (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    description VARCHAR(255)
);

CREATE TABLE products (
    id INT AUTO_INCREMENT PRIMARY KEY,
    category_id INT,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2) NOT NULL,
    stock INT DEFAULT 0,
    image_url VARCHAR(255),
    is_hot BOOLEAN DEFAULT FALSE,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

CREATE TABLE reviews (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    product_id INT NOT NULL,
    rating INT NOT NULL,
    content TEXT NOT NULL,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE CASCADE
);

CREATE TABLE review_images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    review_id INT NOT NULL,
    image_url VARCHAR(255) NOT NULL,
    FOREIGN KEY (review_id) REFERENCES reviews(id) ON DELETE CASCADE
);

CREATE TABLE forum_posts (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    product_id INT,
    title VARCHAR(100) NOT NULL,
    content TEXT NOT NULL,
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products(id) ON DELETE SET NULL
);

CREATE TABLE forum_post_images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    post_id INT NOT NULL,
    image_url VARCHAR(255) NOT NULL,
    FOREIGN KEY (post_id) REFERENCES forum_posts(id) ON DELETE CASCADE
);

CREATE TABLE orders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    total_amount DECIMAL(10, 2) NOT NULL,
    status VARCHAR(20) DEFAULT 'PENDING', -- PENDING, SHIPPED, DELIVERED, CANCELLED
    shipping_address VARCHAR(255),
    shipping_phone VARCHAR(20),
    create_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE order_items (
    id INT AUTO_INCREMENT PRIMARY KEY,
    order_id INT,
    product_id INT,
    quantity INT NOT NULL,
    price DECIMAL(10, 2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(id),
    FOREIGN KEY (product_id) REFERENCES products(id)
);

-- Initial Data
INSERT INTO users (username, password, role) VALUES ('admin', 'admin123', 'ADMIN');
INSERT INTO users (username, password, role, bio) VALUES ('testuser', '123456', 'USER', '喜欢给毛孩子买好物～');
INSERT INTO users (username, password, role, bio) VALUES ('alice', '123456', 'USER', '养猫日常分享');
INSERT INTO users (username, password, role, bio) VALUES ('bob', '123456', 'USER', '养狗经验交流');
INSERT INTO users (username, password, role, bio) VALUES ('mimi', '123456', 'USER', '虚拟用户：猫粮测评小能手');
INSERT INTO users (username, password, role, bio) VALUES ('rocky', '123456', 'USER', '虚拟用户：遛狗装备控');
INSERT INTO users (username, password, role, bio) VALUES ('lulu', '123456', 'USER', '虚拟用户：新手养猫记录');
INSERT INTO users (username, password, role, bio) VALUES ('doudou', '123456', 'USER', '虚拟用户：狗狗磨牙玩具研究员');

INSERT INTO categories (name, description) VALUES ('主粮', 'Pet Food');
INSERT INTO categories (name, description) VALUES ('玩具', 'Pet Toys');
INSERT INTO categories (name, description) VALUES ('用品', 'General Supplies');

-- Products with Images
INSERT INTO products (category_id, name, description, price, stock, image_url, is_hot) VALUES 
(1, '优质狗粮', '营养均衡的优质狗粮 5kg', 128.00, 100, 'images/prod-dogfood.jpg', TRUE),
(1, '全价猫粮', '美味营养猫粮/猫罐头组合', 88.00, 100, 'images/prod-catfood.jpg', TRUE),
(2, '互动逗猫棒', '色彩鲜艳的互动逗猫棒，猫咪最爱', 19.90, 200, 'images/prod-cat-stick.jpg', TRUE),
(2, '耐咬磨牙球', '环保材质磨牙球，结实耐玩', 25.00, 150, 'images/prod-toy-ball.jpg', FALSE),
(3, '坚固狗链', '防爆冲结实耐用的狗绳项圈', 39.00, 50, 'images/prod-leash.jpg', FALSE),
(3, '舒适宠物窝', '四季通用柔软舒适宠物窝垫', 158.00, 30, 'images/prod-bed.jpg', TRUE);

INSERT INTO reviews (user_id, product_id, rating, content) VALUES
(2, 2, 5, '猫粮香味不错，主子吃得很开心，颗粒大小也合适。'),
(3, 1, 4, '狗粮性价比高，便便正常，适口性不错。'),
(4, 3, 5, '逗猫棒做工很好，羽毛很耐咬，猫咪玩疯了！');

INSERT INTO forum_posts (user_id, product_id, title, content) VALUES
(3, 1, '优质狗粮试吃反馈', '我家金毛吃了一周，精神状态很好，掉毛也没变多，推荐给大家。'),
(4, 3, '逗猫棒真的很上头', '每天十分钟，猫咪运动量拉满，羽毛不容易掉，体验不错。'),
(2, 6, '宠物窝值不值？', '摸起来很软，冬天放在沙发边，猫咪每天都去睡。');

INSERT INTO forum_posts (user_id, product_id, title, content) VALUES
((SELECT id FROM users WHERE username='mimi' LIMIT 1), (SELECT id FROM products WHERE name LIKE '%猫粮%' ORDER BY id ASC LIMIT 1), '猫粮适口性真的不错', '这款猫粮颗粒大小合适，香味不冲，挑食猫也愿意吃。吃了两周精神状态不错，便便也正常。'),
((SELECT id FROM users WHERE username='rocky' LIMIT 1), (SELECT id FROM products WHERE name LIKE '%狗链%' ORDER BY id ASC LIMIT 1), '栓狗链上手体验', '材质结实，扣子顺滑，拉扯的时候也不勒手。带狗狗出门更安心了。'),
((SELECT id FROM users WHERE username='lulu' LIMIT 1), NULL, '新手养猫必备清单', '猫砂盆、猫抓板、逗猫棒、化毛膏、指甲剪，建议一步到位，不然后面补买更花钱。'),
((SELECT id FROM users WHERE username='doudou' LIMIT 1), NULL, '狗狗磨牙玩具怎么选？', '优先选耐咬、无异味、边缘不锋利的。太软的几下就咬烂，容易误吞。');

INSERT INTO forum_post_images (post_id, image_url)
SELECT id, 'images/论坛猫粮.png' FROM forum_posts WHERE title='猫粮适口性真的不错' ORDER BY id DESC LIMIT 1;
INSERT INTO forum_post_images (post_id, image_url)
SELECT id, 'images/论坛栓狗链.png' FROM forum_posts WHERE title='栓狗链上手体验' ORDER BY id DESC LIMIT 1;
