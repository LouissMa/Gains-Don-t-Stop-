<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>我的违规</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <form class="row g-2 align-items-end mb-3" method="get" action="${ctx}/violations">
        <div class="col-md-4">
            <label class="form-label">状态</label>
            <select class="form-select" name="status">
                <option value="">全部</option>
                <c:forEach items="${statuses}" var="s">
                    <option value="${s}" <c:if test="${status == s}">selected</c:if>>${s}</option>
                </c:forEach>
            </select>
        </div>
        <div class="col-md-2">
            <label class="form-label">每页</label>
            <select class="form-select" name="size">
                <option value="5" <c:if test="${violationPage.size == 5}">selected</c:if>>5</option>
                <option value="10" <c:if test="${violationPage.size == 10}">selected</c:if>>10</option>
                <option value="20" <c:if test="${violationPage.size == 20}">selected</c:if>>20</option>
                <option value="50" <c:if test="${violationPage.size == 50}">selected</c:if>>50</option>
            </select>
        </div>
        <div class="col-md-2 d-grid">
            <button class="btn btn-primary" type="submit">查询</button>
        </div>
    </form>

    <div class="card">
        <div class="card-body">
            <div class="fw-bold mb-2">我的违规记录</div>
            <div class="table-responsive">
                <table class="table table-hover align-middle">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>设备</th>
                        <th>计划归还日期</th>
                        <th>违规开始日期</th>
                        <th>首次快照(天)</th>
                        <th>当前超时(天)</th>
                        <th>状态</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${violationPage.list}" var="v">
                        <tr>
                            <td>${v.violationId}</td>
                            <td>${v.deviceName}</td>
                            <td>${v.endDate}</td>
                            <td>${v.violationStartDate}</td>
                            <td>${v.violationDays}</td>
                            <td>${v.currentOverdueDays}</td>
                            <td>${v.status}</td>
                        </tr>
                    </c:forEach>
                    <c:if test="${empty violationPage.list}">
                        <tr>
                            <td colspan="7" class="text-center text-muted py-4">暂无数据</td>
                        </tr>
                    </c:if>
                    </tbody>
                </table>
            </div>

            <c:set var="totalPages" value="${violationPage.totalPages}"/>
            <c:if test="${totalPages > 1}">
                <nav>
                    <ul class="pagination">
                        <li class="page-item ${violationPage.page <= 1 ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/violations?page=${violationPage.page-1}&size=${violationPage.size}&status=${status}">上一页</a>
                        </li>
                        <c:forEach begin="1" end="${totalPages}" var="p">
                            <li class="page-item ${violationPage.page == p ? 'active' : ''}">
                                <a class="page-link" href="${ctx}/violations?page=${p}&size=${violationPage.size}&status=${status}">${p}</a>
                            </li>
                        </c:forEach>
                        <li class="page-item ${violationPage.page >= totalPages ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/violations?page=${violationPage.page+1}&size=${violationPage.size}&status=${status}">下一页</a>
                        </li>
                    </ul>
                </nav>
            </c:if>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
