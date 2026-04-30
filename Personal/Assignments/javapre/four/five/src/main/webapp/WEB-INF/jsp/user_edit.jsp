<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>编辑用户</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 920px;">
    <c:if test="${not empty message}">
        <div class="alert alert-danger">${message}</div>
    </c:if>
    <div class="card">
        <div class="card-body">
            <h5 class="card-title mb-3">编辑用户（ID：${userId}）</h5>
            <form method="post" action="${ctx}${action}">
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">真实姓名</label>
                        <input class="form-control" name="realName" value="${form.realName}" required>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">学号/工号</label>
                        <input class="form-control" name="studentNo" value="${form.studentNo}" required>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-4 mb-3">
                        <label class="form-label">角色</label>
                        <select class="form-select" name="role" required>
                            <c:forEach items="${roles}" var="r">
                                <option value="${r}" <c:if test="${form.role == r}">selected</c:if>>${r}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <div class="col-md-4 mb-3">
                        <label class="form-label">手机号</label>
                        <input class="form-control" name="phone" value="${form.phone}">
                    </div>
                    <div class="col-md-4 mb-3">
                        <label class="form-label">邮箱</label>
                        <input class="form-control" name="email" value="${form.email}">
                    </div>
                </div>
                <div class="d-flex gap-2">
                    <button class="btn btn-primary" type="submit">保存</button>
                    <a class="btn btn-secondary" href="${ctx}/admin/users">返回</a>
                </div>
            </form>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
