-- 作业5新增表：借用申请与审批流程
-- 使用前提：已执行版本1.0的 user/device/category 表结构和初始化数据。

DROP TABLE IF EXISTS borrow_apply;

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
    CONSTRAINT fk_apply_user FOREIGN KEY (user_id) REFERENCES `user` (user_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_apply_device FOREIGN KEY (device_id) REFERENCES device (device_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_apply_audit_user FOREIGN KEY (audit_user_id) REFERENCES `user` (user_id)
        ON DELETE SET NULL ON UPDATE CASCADE,
    CHECK (borrow_days > 0),
    CHECK (end_date > start_date),
    CHECK (purpose_type IN ('course', 'research', 'competition', 'other')),
    CHECK (status IN ('pending', 'approved', 'rejected', 'borrowed', 'returned', 'cancelled'))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
