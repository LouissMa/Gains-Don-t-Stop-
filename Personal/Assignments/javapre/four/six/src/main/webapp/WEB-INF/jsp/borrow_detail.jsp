<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>申请详情</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 920px;">
    <div class="card">
        <div class="card-body">
            <div class="d-flex justify-content-between">
                <h4 class="mb-3">申请详情 #${apply.applyId}</h4>
                <span class="badge bg-secondary align-self-start">${apply.status}</span>
            </div>
            <div class="row">
                <div class="col-md-6 mb-2"><span class="text-muted">申请人：</span>${apply.realName} (${apply.username})</div>
                <div class="col-md-6 mb-2"><span class="text-muted">设备：</span>${apply.deviceName} / ${apply.deviceModel}</div>
                <div class="col-md-6 mb-2"><span class="text-muted">申请时间：</span><fmt:formatDate value="${apply.applyDate}" pattern="yyyy-MM-dd HH:mm:ss"/></div>
                <div class="col-md-6 mb-2"><span class="text-muted">计划时间：</span>${apply.startDate} 至 ${apply.endDate}，${apply.borrowDays} 天</div>
                <div class="col-md-6 mb-2"><span class="text-muted">用途：</span>${apply.purposeType}</div>
                <div class="col-md-6 mb-2"><span class="text-muted">用途说明：</span>${empty apply.purposeNote ? '无' : apply.purposeNote}</div>
                <div class="col-md-6 mb-2"><span class="text-muted">审批人ID：</span>${empty apply.auditUserId ? '未审批' : apply.auditUserId}</div>
                <div class="col-md-6 mb-2"><span class="text-muted">审批时间：</span><fmt:formatDate value="${apply.auditTime}" pattern="yyyy-MM-dd HH:mm:ss"/></div>
                <div class="col-md-6 mb-2"><span class="text-muted">审批备注：</span>${empty apply.auditNote ? '无' : apply.auditNote}</div>
                <div class="col-md-6 mb-2"><span class="text-muted">实际借出：</span><fmt:formatDate value="${apply.actualBorrowTime}" pattern="yyyy-MM-dd HH:mm:ss"/></div>
                <div class="col-md-6 mb-2"><span class="text-muted">实际归还：</span><fmt:formatDate value="${apply.actualReturnTime}" pattern="yyyy-MM-dd HH:mm:ss"/></div>
                <div class="col-md-6 mb-2"><span class="text-muted">归还备注：</span>${empty apply.returnNote ? '无' : apply.returnNote}</div>
            </div>
            <c:set var="backUrl" value="${ctx}/my/borrows"/>
            <c:if test="${sessionScope.SESSION_USER.role == 'admin'}">
                <c:set var="backUrl" value="${ctx}/admin/borrows"/>
            </c:if>
            <a class="btn btn-outline-secondary mt-3" href="${backUrl}">返回列表</a>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
