<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>管理员工作台</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <h4 class="mb-3">管理员工作台</h4>
    <div class="row g-3">
        <div class="col-md-4">
            <div class="card"><div class="card-body"><div class="text-muted">待审批申请数</div><div class="display-6">${stats.pendingApplyCount}</div></div></div>
        </div>
        <div class="col-md-4">
            <div class="card"><div class="card-body"><div class="text-muted">借出中设备数</div><div class="display-6">${stats.borrowedApplyCount}</div></div></div>
        </div>
        <div class="col-md-4">
            <div class="card"><div class="card-body"><div class="text-muted">今日新增申请数</div><div class="display-6">${stats.todayApplyCount}</div></div></div>
        </div>
    </div>
    <div class="card mt-3">
        <div class="card-body">
            <h5 class="mb-3">设备状态汇总</h5>
            <div class="row">
                <c:forEach items="${stats.deviceStatusCounts}" var="entry">
                    <div class="col-md-3 mb-2">
                        <div class="border rounded p-3">
                            <div class="text-muted">${entry.key}</div>
                            <div class="fs-3">${entry.value}</div>
                        </div>
                    </div>
                </c:forEach>
            </div>
            <a class="btn btn-primary mt-2" href="${ctx}/admin/borrows?status=pending">处理待审批</a>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
