<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>设备表单</title>
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
            <h5 class="card-title mb-3">设备信息</h5>
            <fmt:formatDate value="${form.purchaseDate}" pattern="yyyy-MM-dd" var="purchaseDateStr"/>
            <form method="post" action="${ctx}${action}">
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">设备名称</label>
                        <input class="form-control" name="deviceName" value="${form.deviceName}" required>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">型号</label>
                        <input class="form-control" name="deviceModel" value="${form.deviceModel}" required>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">分类</label>
                        <select class="form-select" name="categoryId" required>
                            <c:forEach items="${categories}" var="c">
                                <option value="${c.categoryId}" <c:if test="${form.categoryId != null && form.categoryId == c.categoryId}">selected</c:if>>${c.categoryName}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">存放位置</label>
                        <input class="form-control" name="location" value="${form.location}" required>
                    </div>
                </div>
                <div class="row">
                    <div class="col-md-4 mb-3">
                        <label class="form-label">购入日期</label>
                        <input type="date" class="form-control" name="purchaseDate" value="${purchaseDateStr}" required>
                    </div>
                    <div class="col-md-4 mb-3">
                        <label class="form-label">状态</label>
                        <select class="form-select" name="status" required>
                            <c:forEach items="${statuses}" var="s">
                                <option value="${s}" <c:if test="${form.status == s}">selected</c:if>>${s}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <div class="col-md-4 mb-3">
                        <label class="form-label">最长借用天数</label>
                        <input type="number" class="form-control" name="maxBorrowDays" value="${form.maxBorrowDays}" min="1" required>
                    </div>
                </div>
                <div class="d-flex gap-2">
                    <button class="btn btn-primary" type="submit">保存</button>
                    <a class="btn btn-secondary" href="${ctx}/devices">返回</a>
                </div>
            </form>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
