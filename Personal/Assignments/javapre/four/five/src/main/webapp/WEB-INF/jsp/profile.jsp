<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>个人中心</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 920px;">
    <c:if test="${not empty message}">
        <div class="alert alert-danger">${message}</div>
    </c:if>
    <c:if test="${not empty success}">
        <div class="alert alert-success">${success}</div>
    </c:if>

    <div class="row">
        <div class="col-md-7">
            <div class="card mb-3">
                <div class="card-body">
                    <h5 class="card-title mb-3">个人信息</h5>
                    <form method="post" action="${ctx}/profile">
                        <div class="mb-3">
                            <label class="form-label">用户名</label>
                            <input class="form-control" value="${user.username}" disabled>
                        </div>
                        <div class="row">
                            <div class="col-md-6 mb-3">
                                <label class="form-label">真实姓名</label>
                                <input class="form-control" name="realName" value="${profileForm.realName}" required>
                            </div>
                            <div class="col-md-6 mb-3">
                                <label class="form-label">学号/工号</label>
                                <input class="form-control" name="studentNo" value="${profileForm.studentNo}" required>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-md-6 mb-3">
                                <label class="form-label">手机号</label>
                                <input class="form-control" name="phone" value="${profileForm.phone}">
                            </div>
                            <div class="col-md-6 mb-3">
                                <label class="form-label">邮箱</label>
                                <input class="form-control" name="email" value="${profileForm.email}">
                            </div>
                        </div>
                        <button class="btn btn-primary" type="submit">保存</button>
                    </form>
                </div>
            </div>
        </div>

        <div class="col-md-5">
            <div class="card">
                <div class="card-body">
                    <h5 class="card-title mb-3">修改密码</h5>
                    <form method="post" action="${ctx}/profile/password">
                        <div class="mb-3">
                            <label class="form-label">旧密码</label>
                            <input type="password" class="form-control" name="oldPassword" required>
                        </div>
                        <div class="mb-3">
                            <label class="form-label">新密码</label>
                            <input type="password" class="form-control" name="newPassword" required>
                        </div>
                        <button class="btn btn-warning" type="submit">修改</button>
                    </form>
                    <div class="mt-3 text-muted small">
                        最近登录时间：
                        <fmt:formatDate value="${user.lastLoginTime}" pattern="yyyy-MM-dd HH:mm:ss"/>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
