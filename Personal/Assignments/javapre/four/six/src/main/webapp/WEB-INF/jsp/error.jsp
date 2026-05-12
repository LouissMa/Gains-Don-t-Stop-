<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>错误</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <div class="alert alert-danger">
        <div class="fw-bold mb-1">操作失败</div>
        <div>${message}</div>
        <c:if test="${not empty path}">
            <div class="mt-2 text-muted small">${path}</div>
        </c:if>
    </div>
    <a class="btn btn-secondary" href="${ctx}/devices">返回设备列表</a>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
