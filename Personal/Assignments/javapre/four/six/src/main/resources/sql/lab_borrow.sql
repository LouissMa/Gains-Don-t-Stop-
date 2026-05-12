-- 1. 暂时关闭外键检查
SET FOREIGN_KEY_CHECKS = 0;

DROP DATABASE IF EXISTS lab_borrow;
CREATE DATABASE lab_borrow DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE lab_borrow;

DROP TABLE IF EXISTS borrow_record;
DROP TABLE IF EXISTS borrow_apply;
DROP TABLE IF EXISTS device;
DROP TABLE IF EXISTS category;
DROP TABLE IF EXISTS `user`;

-- 创建 user 表
CREATE TABLE `user` (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL,
    password VARCHAR(100) NOT NULL,
    real_name VARCHAR(50) NOT NULL,
    student_no VARCHAR(20) NOT NULL,
    role VARCHAR(20) NOT NULL,
    phone VARCHAR(20) DEFAULT NULL,
    email VARCHAR(100) DEFAULT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'active',
    last_login_time DATETIME DEFAULT NULL,
    UNIQUE KEY uk_user_username (username),
    UNIQUE KEY uk_user_student_no (student_no),
    CHECK (role IN ('admin', 'user')),
    CHECK (status IN ('active', 'inactive'))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建 category 表（⚠️ 这里去掉了低版本不支持的计算列语法）
CREATE TABLE category (
    category_id INT PRIMARY KEY AUTO_INCREMENT,
    category_name VARCHAR(50) NOT NULL,
    parent_id INT DEFAULT NULL,
    description VARCHAR(255) DEFAULT NULL,
    KEY idx_category_parent (parent_id),
    CONSTRAINT fk_category_parent FOREIGN KEY (parent_id) REFERENCES category (category_id)
        ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建 device 表
CREATE TABLE device (
    device_id INT PRIMARY KEY AUTO_INCREMENT,
    device_name VARCHAR(100) NOT NULL,
    device_model VARCHAR(100) NOT NULL,
    category_id INT NOT NULL,
    location VARCHAR(100) NOT NULL,
    purchase_date DATE NOT NULL,
    status VARCHAR(20) NOT NULL,
    max_borrow_days INT NOT NULL,
    UNIQUE KEY uk_device_name (device_name),
    KEY idx_device_category (category_id),
    CHECK (status IN ('available', 'borrowed', 'maintenance', 'retired')),
    CONSTRAINT fk_device_category FOREIGN KEY (category_id) REFERENCES category (category_id)
        ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建 borrow_record 表
CREATE TABLE borrow_record (
    record_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    device_id INT NOT NULL,
    borrow_time DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    return_time DATETIME DEFAULT NULL,
    status VARCHAR(20) NOT NULL,
    KEY idx_borrow_user_status (user_id, status),
    KEY idx_borrow_device_status (device_id, status),
    CHECK (status IN ('borrowed', 'returned')),
    CONSTRAINT fk_borrow_user FOREIGN KEY (user_id) REFERENCES `user` (user_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_borrow_device FOREIGN KEY (device_id) REFERENCES device (device_id)
        ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 作业5新增：借用申请审批表
CREATE TABLE borrow_apply (
    apply_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    device_id INT NOT NULL,
    apply_date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    start_date DATE NOT NULL,
    end_date DATE NOT NULL,
    borrow_days INT NOT NULL,
    purpose_type VARCHAR(20) NOT NULL,
    purpose_note VARCHAR(500) DEFAULT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'pending',
    audit_user_id INT DEFAULT NULL,
    audit_time DATETIME DEFAULT NULL,
    audit_note VARCHAR(500) DEFAULT NULL,
    actual_borrow_time DATETIME DEFAULT NULL,
    actual_return_time DATETIME DEFAULT NULL,
    return_note VARCHAR(500) DEFAULT NULL,
    KEY idx_apply_user_status (user_id, status),
    KEY idx_apply_device_period_status (device_id, start_date, end_date, status),
    KEY idx_apply_audit_user (audit_user_id),
    CHECK (borrow_days > 0),
    CHECK (end_date > start_date),
    CHECK (purpose_type IN ('course', 'research', 'competition', 'other')),
    CHECK (status IN ('pending', 'approved', 'rejected', 'borrowed', 'returned', 'cancelled')),
    CONSTRAINT fk_apply_user FOREIGN KEY (user_id) REFERENCES `user` (user_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_apply_device FOREIGN KEY (device_id) REFERENCES device (device_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_apply_audit_user FOREIGN KEY (audit_user_id) REFERENCES `user` (user_id)
        ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 插入测试数据
INSERT INTO `user` (username, password, real_name, student_no, role, phone, email, status, last_login_time)
VALUES
('admin', 'd4ee29671e66681f1925b38e65b4b788', '管理员', 'A0000001', 'admin', NULL, NULL, 'active', NULL),
('user01', 'd4ee29671e66681f1925b38e65b4b788', '张三', 'U20240001', 'user', '13800000000', 'user01@example.com', 'active', NULL);

INSERT INTO category (category_name, parent_id, description) VALUES
('电子仪器', NULL, '电子测量与分析设备'),
('机械设备', NULL, '常用机械类设备');

INSERT INTO category (category_name, parent_id, description) VALUES
('示波器类', 1, '示波器及配件'),
('信号源类', 1, '信号发生器等');

INSERT INTO device (device_name, device_model, category_id, location, purchase_date, status, max_borrow_days) VALUES
('泰克示波器', 'Tektronix TBS1102B', 3, 'A楼301-柜3', '2023-09-01', 'available', 14),
('信号发生器', 'RIGOL DSG3060', 4, 'A楼301-柜2', '2022-03-15', 'maintenance', 7);

-- 2. 恢复外键检查
SET FOREIGN_KEY_CHECKS = 1;
