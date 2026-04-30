# 实验室设备借用管理系统 v2.0

本项目为作业 5 提交版本，在 v1.0 的用户、设备、分类管理基础上迁移为 Spring Boot 2.7，并新增设备借用申请、审批、借出、归还、取消、冲突检测和管理员工作台。

## 技术栈

- Spring Boot 2.7.18
- MyBatis + MyBatis Spring Boot Starter
- JSP + JSTL
- MySQL
- Maven

## 运行方式

1. 创建 MySQL 数据库并执行 `src/main/resources/sql/lab_borrow.sql`。如果已存在 v1.0 数据库，只需执行 `src/main/resources/sql/borrow_apply.sql`。
2. 修改 `src/main/resources/application.yml` 中的数据库账号密码。
3. 在 `five` 目录执行：

```bash
mvn spring-boot:run
```

4. 浏览器访问：`http://localhost:8080/lab-borrow`

默认账号来自 v1.0 初始化数据：

- 管理员：`admin`
- 普通用户：`user01`

## 本次新增/修改模块

- 新增 `borrow_apply` 表，包含申请、审批、实际借出、实际归还和备注字段。
- 新增 `BorrowApply` 实体、`BorrowApplyMapper`、`BorrowApplyService` 和 Web/API Controller。
- 新增申请表单、我的申请、管理员审批列表、申请详情和管理员工作台 JSP 页面。
- 迁移到 Spring Boot：新增启动类、`application.yml`、Java 版 MVC 拦截器配置。
- 设备状态与申请状态同步：确认借出时设备设为 `borrowed`，确认归还时恢复 `available`。

## 核心业务规则

- `borrow_days` 由后端使用 `end_date - start_date` 计算，不接收客户端传入值。
- 提交申请时检查设备存在、状态为 `available`、未退役、日期合法、用途合法、用途为 `other` 时说明必填。
- 同一设备时间冲突判断使用：

```sql
start_date < #{endDate} AND #{startDate} < end_date
```

该规则覆盖完全包含、被包含和局部重叠；当两个时间段首尾相接时不算冲突。

- 审批状态机：

```text
pending -> approved -> borrowed -> returned
pending -> rejected
pending -> cancelled
```

- 驳回必须填写审批备注，归还必须填写归还备注。
- 审批、借出、归还操作记录审批人 ID、审批时间，并写入应用日志。
