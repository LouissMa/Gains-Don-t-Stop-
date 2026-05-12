<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>提交借用申请</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 760px;">
    <div class="card">
        <div class="card-body">
            <h4 class="mb-3">提交借用申请</h4>
            <c:if test="${not empty message}">
                <div class="alert alert-danger">${message}</div>
            </c:if>
            <div class="alert alert-light border">
                <strong>${device.deviceName}</strong>
                <span class="text-muted ms-2">${device.deviceModel}</span>
                <span class="badge bg-secondary ms-2">最长 ${device.maxBorrowDays} 天</span>
            </div>
            <form method="post" action="${ctx}/borrows">
                <input type="hidden" name="deviceId" value="${form.deviceId}">
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">开始日期</label>
                        <input class="form-control" type="date" name="startDate" value="${form.startDate}" required>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">归还日期</label>
                        <input class="form-control" type="date" name="endDate" value="${form.endDate}" required>
                    </div>
                </div>
                <div class="mb-3">
                    <label class="form-label">用途类型</label>
                    <select class="form-select" name="purposeType" required>
                        <option value="">请选择</option>
                        <option value="course" ${form.purposeType == 'course' ? 'selected' : ''}>课程实验</option>
                        <option value="research" ${form.purposeType == 'research' ? 'selected' : ''}>科研</option>
                        <option value="competition" ${form.purposeType == 'competition' ? 'selected' : ''}>竞赛</option>
                        <option value="other" ${form.purposeType == 'other' ? 'selected' : ''}>其他</option>
                    </select>
                </div>
                <div class="mb-3">
                    <label class="form-label">用途说明</label>
                    <textarea class="form-control" name="purposeNote" maxlength="500" rows="4" placeholder="用途为其他时必填">${form.purposeNote}</textarea>
                </div>
                <div class="d-flex gap-2">
                    <button class="btn btn-success" type="submit">提交申请</button>
                    <a class="btn btn-outline-secondary" href="${ctx}/devices/${device.deviceId}">返回详情</a>
                </div>
            </form>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
