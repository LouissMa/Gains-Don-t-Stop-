# 实验室设备借用管理系统 v3.0

本项目为作业 6 提交版本（v3.0：超时违规与信用管理），在 v2.0 的借用审批流程基础上新增：超时自动检测、违规记录、权限影响、违规管理与统计、设备使用率统计，并保留 v1.0 的基础数据管理能力。

## 技术栈

- Spring Boot 2.7.18
- MyBatis + MyBatis Spring Boot Starter
- JSP + JSTL
- MySQL
- Maven

## 运行方式

1. 执行数据库脚本：
   - 初始化全量数据：`src/main/resources/sql/lab_borrow.sql`
   - 如果你已经有 v2.0 的数据库：只需执行 `src/main/resources/sql/violation.sql`
2. 修改 `src/main/resources/application.yml` 中的数据库账号密码。
3. 在 `six` 目录执行：

```bash
mvn spring-boot:run
```

4. 浏览器访问：`http://localhost:8080/lab-borrow`

## 测试账号

来自 `lab_borrow.sql` 的初始化数据：

- 管理员：`admin` / `123456`
- 普通用户：`user01` / `123456`

## 本次新增/修改模块（v3.0）

- 新增 `violation` 表（违规记录）：`src/main/resources/sql/violation.sql`
- 新增超时自动检测：定时任务每小时扫描 `borrow_apply(status=borrowed 且 today > end_date)`，自动生成违规记录且不重复生成（借用记录唯一约束）。
- 新增权限影响：用户存在 `untreated` 违规记录时禁止发起借用申请，并在页面顶部提示。
- 新增违规管理：管理员可分页查看/筛选/详情/处理违规记录，记录处理人ID、处理时间、处理备注。
- 新增违规统计：各用户违规次数、设备被超时次数统计页面。
- 新增设备使用率统计：计算指定设备在指定日期区间内的借用天数占比（区间不超过365天）。

## 关键业务规则（v3.0）

- 超时定义：`today > end_date` 且借用申请状态仍为 `borrowed`。
- 违规记录生成规则：
  - `borrow_record_id` 唯一：同一借用记录只生成一条违规记录
  - `violation_start_date = end_date + 1`
  - `violation_days` 为首次生成时的快照值；页面展示“当前超时天数”按 `today - end_date` 实时计算
- 归还与违规联动方案：选择方案B
  - 允许管理员直接归还
  - 若该借用记录存在未处理违规，归还后系统自动将其标记为 `processed`，处理备注为“设备已归还，系统自动处理”
