<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>设备详情</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 920px;">
    <div class="card">
        <div class="card-body">
            <div class="d-flex justify-content-between align-items-start">
                <div>
                    <h4 class="mb-1">${device.deviceName}</h4>
                    <div class="text-muted">${device.deviceModel}</div>
                </div>
                <div>
                    <a class="btn btn-outline-secondary" href="${ctx}/devices">返回列表</a>
                    <c:if test="${sessionScope.SESSION_USER.role == 'user' && device.status == 'available'}">
                        <a class="btn btn-success" href="${ctx}/devices/${device.deviceId}/apply">申请借用</a>
                    </c:if>
                    <c:if test="${sessionScope.SESSION_USER.role == 'admin'}">
                        <a class="btn btn-primary" href="${ctx}/admin/devices/${device.deviceId}/edit">编辑</a>
                    </c:if>
                </div>
            </div>
            <hr>
            <div class="row">
                <div class="col-md-6">
                    <div class="mb-2"><span class="text-muted">设备ID：</span>${device.deviceId}</div>
                    <div class="mb-2"><span class="text-muted">分类：</span>${categoryMap[device.categoryId]}</div>
                    <div class="mb-2"><span class="text-muted">存放位置：</span>${device.location}</div>
                    <div class="mb-2"><span class="text-muted">状态：</span>${device.status}</div>
                </div>
                <div class="col-md-6">
                    <div class="mb-2"><span class="text-muted">购入日期：</span><fmt:formatDate value="${device.purchaseDate}" pattern="yyyy-MM-dd"/></div>
                    <div class="mb-2"><span class="text-muted">最长借用天数：</span>${device.maxBorrowDays}</div>
                </div>
            </div>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
