# 实验室设备借用管理系统 v1.0

## 1. 项目简介
本项目为基于 SSM（Spring + Spring MVC + MyBatis）框架和 JSP 技术开发的实验室设备借用管理系统（版本1.0：基础数据管理）。主要实现设备、分类、用户的基础数据管理。

## 2. 环境要求
- **JDK**: 1.8 及以上
- **数据库**: MySQL 8.0+
- **构建工具**: Maven 3.6+
- **Web 容器**: Tomcat 9+ (支持 Servlet 4.0)

## 3. 运行方式

### 3.1 数据库初始化
1. 在 MySQL 中执行源码 `src/main/resources/sql/lab_borrow.sql` 脚本，该脚本会自动创建 `lab_borrow` 数据库、四张表（user、category、device、borrow_record）并插入初始数据。

### 3.2 配置文件修改
打开 `src/main/resources/jdbc.properties`，修改以下信息为你本地的 MySQL 连接配置：
```properties
jdbc.url=jdbc:mysql://localhost:3306/lab_borrow?useUnicode=true&characterEncoding=utf8&useSSL=false&serverTimezone=Asia/Shanghai&allowPublicKeyRetrieval=true
jdbc.username=你的数据库账号 (如: root)
jdbc.password=你的数据库密码
```

### 3.3 编译与部署
1. 使用 Maven 打包项目：`mvn clean package`，生成 WAR 包。
2. 将项目部署到 Tomcat 容器中运行。
3. 启动后，在浏览器访问：`http://localhost:8080/four_war_exploded/auth/login` （具体路径视 Tomcat 配置的 Application Context 而定）。

## 4. 测试账号
数据库脚本中默认初始化了两个测试账号：
- **管理员账号**：
  - 用户名：`admin`
  - 密码：`admin123`
- **普通用户账号**：
  - 用户名：`user01`
  - 密码：`user123`

## 5. 核心技术说明
- **密码加密**：使用 MD5 加盐的方式对用户密码进行加密存储。
- **全局异常处理**：通过 `@ControllerAdvice` 实现统一的异常拦截，返回规范的 `Result` 结构或友好的错误页面。
- **业务校验**：在 Service 层实现了所有的业务规则校验，不满足条件时统一抛出 `BizException`。
