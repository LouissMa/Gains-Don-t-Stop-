-- 作业6新增表：违规记录（v3.0）
-- 使用前提：已执行 v2.0 的 user/device/category/borrow_apply 表结构与数据。

USE lab_borrow;

DROP TABLE IF EXISTS violation;

CREATE TABLE violation (
    violation_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT NOT NULL,
    device_id INT NOT NULL,
    borrow_record_id INT NOT NULL,
    violation_start_date DATE NOT NULL,
    violation_days INT NOT NULL,
    status VARCHAR(20) NOT NULL DEFAULT 'untreated',
    process_date DATETIME DEFAULT NULL,
    process_user_id INT DEFAULT NULL,
    process_note VARCHAR(500) DEFAULT NULL,
    UNIQUE KEY uk_violation_borrow_record (borrow_record_id),
    KEY idx_violation_user_status (user_id, status),
    KEY idx_violation_device_status (device_id, status),
    KEY idx_violation_process_user (process_user_id),
    CONSTRAINT fk_violation_user FOREIGN KEY (user_id) REFERENCES `user` (user_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_violation_device FOREIGN KEY (device_id) REFERENCES device (device_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_violation_borrow_apply FOREIGN KEY (borrow_record_id) REFERENCES borrow_apply (apply_id)
        ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_violation_process_user FOREIGN KEY (process_user_id) REFERENCES `user` (user_id)
        ON DELETE SET NULL ON UPDATE CASCADE,
    CHECK (violation_days >= 0),
    CHECK (status IN ('untreated', 'processed'))
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 初始化测试数据（可选）
-- 说明：违规记录通常由系统自动检测生成。为了便于验收，这里提供一组可执行的示例数据：
-- 1) 自动插入一条“已借出且已超期”的 borrow_apply
-- 2) 插入一条对应的 violation（status=untreated）
--
-- 若你的数据库已有借用申请数据，可不执行以下示例。

SET @u := (SELECT user_id FROM `user` WHERE username = 'user01' LIMIT 1);
SET @d := (SELECT device_id FROM device WHERE status = 'available' LIMIT 1);

INSERT INTO borrow_apply
(user_id, device_id, apply_date, start_date, end_date, borrow_days, purpose_type, purpose_note, status, audit_user_id, audit_time, audit_note, actual_borrow_time)
VALUES
(@u, @d, NOW(), DATE_SUB(CURDATE(), INTERVAL 10 DAY), DATE_SUB(CURDATE(), INTERVAL 1 DAY), 9, 'course', '超时测试数据', 'borrowed',
 (SELECT user_id FROM `user` WHERE username = 'admin' LIMIT 1), NOW(), '同意', NOW());

SET @a := LAST_INSERT_ID();

UPDATE device SET status = 'borrowed' WHERE device_id = @d;

INSERT INTO violation
(user_id, device_id, borrow_record_id, violation_start_date, violation_days, status)
VALUES
(@u, @d, @a, CURDATE(), 1, 'untreated');
