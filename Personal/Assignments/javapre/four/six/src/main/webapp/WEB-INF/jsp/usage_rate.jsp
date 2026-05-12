<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>设备使用率</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 980px;">
    <h5 class="mb-3">设备使用率统计</h5>

    <form class="row g-2 align-items-end mb-3" method="get" action="${ctx}/admin/usage">
        <div class="col-md-5">
            <label class="form-label">设备</label>
            <select class="form-select" name="deviceId" required>
                <option value="">请选择</option>
                <c:forEach items="${devices}" var="d">
                    <option value="${d.deviceId}" <c:if test="${deviceId != null && deviceId == d.deviceId}">selected</c:if>>${d.deviceName}</option>
                </c:forEach>
            </select>
        </div>
        <div class="col-md-3">
            <label class="form-label">开始日期</label>
            <input type="date" class="form-control" name="startDate" value="${startDate}" required>
        </div>
        <div class="col-md-3">
            <label class="form-label">结束日期</label>
            <input type="date" class="form-control" name="endDate" value="${endDate}" required>
        </div>
        <div class="col-md-1 d-grid">
            <button class="btn btn-primary" type="submit">查</button>
        </div>
        <div class="col-12">
            <div class="form-text">查询区间不超过365天；采用区间重叠天数求和 / 区间总天数</div>
        </div>
    </form>

    <c:if test="${not empty rate}">
        <div class="card">
            <div class="card-body">
                <div class="fw-bold mb-2">统计结果</div>
                <div class="row">
                    <div class="col-md-6 mb-2"><span class="text-muted">设备：</span>${rate.deviceName}（ID：${rate.deviceId}）</div>
                    <div class="col-md-6 mb-2"><span class="text-muted">区间：</span>${startDate} ~ ${endDate}</div>
                    <div class="col-md-6 mb-2"><span class="text-muted">借用天数：</span>${rate.borrowedDays}</div>
                    <div class="col-md-6 mb-2"><span class="text-muted">区间总天数：</span>${rate.totalDays}</div>
                    <div class="col-md-6 mb-2"><span class="text-muted">使用率：</span><fmt:formatNumber value="${rate.ratio * 100}" pattern="0.00"/>%</div>
                </div>
            </div>
        </div>
    </c:if>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
