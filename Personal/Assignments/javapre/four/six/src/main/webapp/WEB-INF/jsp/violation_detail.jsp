<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>违规详情</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 980px;">
    <div class="d-flex justify-content-between align-items-center mb-3">
        <h5 class="mb-0">违规详情（ID：${v.violationId}）</h5>
        <a class="btn btn-secondary" href="${ctx}/admin/violations">返回列表</a>
    </div>

    <div class="card mb-3">
        <div class="card-body">
            <div class="row">
                <div class="col-md-6">
                    <div class="mb-2"><span class="text-muted">用户：</span>${v.realName} (${v.username})</div>
                    <div class="mb-2"><span class="text-muted">设备：</span>${v.deviceName} ${v.deviceModel}</div>
                    <div class="mb-2"><span class="text-muted">借用记录ID：</span>${v.borrowRecordId}</div>
                </div>
                <div class="col-md-6">
                    <div class="mb-2"><span class="text-muted">计划归还日期：</span>${v.endDate}</div>
                    <div class="mb-2"><span class="text-muted">违规开始日期：</span>${v.violationStartDate}</div>
                    <div class="mb-2"><span class="text-muted">首次快照超时天数：</span>${v.violationDays}</div>
                    <div class="mb-2"><span class="text-muted">当前实时超时天数：</span>${v.currentOverdueDays}</div>
                </div>
            </div>
            <hr>
            <div class="mb-2"><span class="text-muted">状态：</span>${v.status}</div>
            <c:if test="${v.status == 'processed'}">
                <div class="mb-2"><span class="text-muted">处理时间：</span><fmt:formatDate value="${v.processDate}" pattern="yyyy-MM-dd HH:mm:ss"/></div>
                <div class="mb-2"><span class="text-muted">处理人ID：</span>${v.processUserId}</div>
                <div class="mb-2"><span class="text-muted">处理备注：</span>${v.processNote}</div>
            </c:if>
        </div>
    </div>

    <c:if test="${v.status == 'untreated'}">
        <div class="card">
            <div class="card-body">
                <h6 class="card-title mb-3">处理违规</h6>
                <form method="post" action="${ctx}/admin/violations/${v.violationId}/process">
                    <div class="mb-3">
                        <label class="form-label">处理备注</label>
                        <textarea class="form-control" name="processNote" rows="3" maxlength="500" required></textarea>
                        <div class="form-text">必填，最多500字符</div>
                    </div>
                    <button class="btn btn-primary" type="submit">确认处理</button>
                </form>
            </div>
        </div>
    </c:if>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
