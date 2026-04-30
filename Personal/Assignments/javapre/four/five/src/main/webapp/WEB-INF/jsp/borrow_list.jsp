<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>${adminView ? '借用审批' : '我的申请'}</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <div class="d-flex justify-content-between align-items-center mb-3">
        <h4 class="mb-0">${adminView ? '借用审批' : '我的申请'}</h4>
        <c:set var="baseUrl" value="${ctx}/my/borrows"/>
        <c:if test="${adminView}">
            <c:set var="baseUrl" value="${ctx}/admin/borrows"/>
        </c:if>
        <form class="d-flex gap-2" method="get" action="${baseUrl}">
            <select class="form-select" name="status">
                <option value="">全部状态</option>
                <c:forEach items="${statuses}" var="s">
                    <option value="${s}" ${status == s ? 'selected' : ''}>${s}</option>
                </c:forEach>
            </select>
            <button class="btn btn-outline-primary" type="submit">筛选</button>
        </form>
    </div>
    <div class="table-responsive">
        <table class="table table-hover align-middle">
            <thead class="table-light">
            <tr>
                <th>ID</th>
                <c:if test="${adminView}"><th>申请人</th></c:if>
                <th>设备</th>
                <th>申请时间</th>
                <th>借用时间</th>
                <th>天数</th>
                <th>状态</th>
                <th style="width: 320px;">操作</th>
            </tr>
            </thead>
            <tbody>
            <c:forEach items="${applyPage.list}" var="a">
                <tr>
                    <td>${a.applyId}</td>
                    <c:if test="${adminView}"><td>${a.realName}<br><small class="text-muted">${a.username}</small></td></c:if>
                    <td>${a.deviceName}<br><small class="text-muted">${a.deviceModel}</small></td>
                    <td><fmt:formatDate value="${a.applyDate}" pattern="yyyy-MM-dd HH:mm"/></td>
                    <td>${a.startDate} 至 ${a.endDate}</td>
                    <td>${a.borrowDays}</td>
                    <td><span class="badge bg-secondary">${a.status}</span></td>
                    <td>
                        <a class="btn btn-sm btn-outline-secondary" href="${ctx}/borrows/${a.applyId}">详情</a>
                        <c:if test="${!adminView && a.status == 'pending'}">
                            <form class="d-inline" method="post" action="${ctx}/my/borrows/${a.applyId}/cancel">
                                <button class="btn btn-sm btn-outline-danger" type="submit">取消</button>
                            </form>
                        </c:if>
                        <c:if test="${adminView && a.status == 'pending'}">
                            <form class="d-inline" method="post" action="${ctx}/admin/borrows/${a.applyId}/approve">
                                <button class="btn btn-sm btn-success" type="submit">批准</button>
                            </form>
                            <form class="d-inline-flex gap-1" method="post" action="${ctx}/admin/borrows/${a.applyId}/reject">
                                <input class="form-control form-control-sm" style="width: 130px;" name="auditNote" placeholder="驳回原因" required>
                                <button class="btn btn-sm btn-outline-danger" type="submit">驳回</button>
                            </form>
                        </c:if>
                        <c:if test="${adminView && a.status == 'approved'}">
                            <form class="d-inline" method="post" action="${ctx}/admin/borrows/${a.applyId}/borrow">
                                <button class="btn btn-sm btn-primary" type="submit">确认借出</button>
                            </form>
                        </c:if>
                        <c:if test="${adminView && a.status == 'borrowed'}">
                            <form class="d-inline-flex gap-1" method="post" action="${ctx}/admin/borrows/${a.applyId}/return">
                                <input class="form-control form-control-sm" style="width: 150px;" name="returnNote" placeholder="归还备注" required>
                                <button class="btn btn-sm btn-warning" type="submit">确认归还</button>
                            </form>
                        </c:if>
                    </td>
                </tr>
            </c:forEach>
            <c:if test="${empty applyPage.list}">
                <tr><td colspan="8" class="text-center text-muted py-4">暂无记录</td></tr>
            </c:if>
            </tbody>
        </table>
    </div>
    <div class="d-flex justify-content-between align-items-center">
        <div class="text-muted">共 ${applyPage.total} 条，第 ${applyPage.page} / ${applyPage.totalPages} 页</div>
        <div class="btn-group">
            <a class="btn btn-outline-secondary ${applyPage.page <= 1 ? 'disabled' : ''}" href="${baseUrl}?status=${status}&page=${applyPage.page - 1}&size=${applyPage.size}">上一页</a>
            <a class="btn btn-outline-secondary ${applyPage.page >= applyPage.totalPages ? 'disabled' : ''}" href="${baseUrl}?status=${status}&page=${applyPage.page + 1}&size=${applyPage.size}">下一页</a>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
