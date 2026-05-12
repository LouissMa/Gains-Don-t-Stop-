<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>超时设备</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <div class="d-flex justify-content-between align-items-center mb-3">
        <h5 class="mb-0">超时未还列表（borrowed 且 end_date &lt; today）</h5>
        <a class="btn btn-outline-secondary btn-sm" href="${ctx}/admin/violations?status=untreated">查看未处理违规</a>
    </div>

    <div class="card">
        <div class="card-body">
            <div class="table-responsive">
                <table class="table table-hover align-middle">
                    <thead>
                    <tr>
                        <th>借用记录ID</th>
                        <th>用户</th>
                        <th>设备</th>
                        <th>计划归还日期</th>
                        <th>当前超时(天)</th>
                        <th style="width: 140px;">违规记录</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${items}" var="it">
                        <tr>
                            <td>${it.apply.applyId}</td>
                            <td>${it.apply.realName} (${it.apply.username})</td>
                            <td>${it.apply.deviceName}</td>
                            <td>${it.apply.endDate}</td>
                            <td>${it.overdueDays}</td>
                            <td>
                                <c:choose>
                                    <c:when test="${it.violationId != null}">
                                        <a class="btn btn-sm btn-outline-primary" href="${ctx}/admin/violations/${it.violationId}">查看</a>
                                    </c:when>
                                    <c:otherwise>
                                        <span class="text-muted">已生成中</span>
                                    </c:otherwise>
                                </c:choose>
                            </td>
                        </tr>
                    </c:forEach>
                    <c:if test="${empty items}">
                        <tr>
                            <td colspan="6" class="text-center text-muted py-4">暂无超时未还记录</td>
                        </tr>
                    </c:if>
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
