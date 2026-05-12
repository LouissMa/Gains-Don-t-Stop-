<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>违规统计</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 1100px;">
    <div class="d-flex justify-content-between align-items-center mb-3">
        <h5 class="mb-0">违规统计</h5>
        <a class="btn btn-secondary" href="${ctx}/admin/violations">返回列表</a>
    </div>

    <div class="row">
        <div class="col-md-6">
            <div class="card">
                <div class="card-body">
                    <div class="fw-bold mb-2">各用户违规次数</div>
                    <div class="table-responsive">
                        <table class="table table-sm table-hover align-middle">
                            <thead>
                            <tr>
                                <th>用户</th>
                                <th>次数</th>
                            </tr>
                            </thead>
                            <tbody>
                            <c:forEach items="${userStats}" var="s">
                                <tr>
                                    <td>${s.name}</td>
                                    <td>${s.count}</td>
                                </tr>
                            </c:forEach>
                            <c:if test="${empty userStats}">
                                <tr><td colspan="2" class="text-center text-muted py-3">暂无数据</td></tr>
                            </c:if>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
        <div class="col-md-6">
            <div class="card">
                <div class="card-body">
                    <div class="fw-bold mb-2">设备被超时次数</div>
                    <div class="table-responsive">
                        <table class="table table-sm table-hover align-middle">
                            <thead>
                            <tr>
                                <th>设备</th>
                                <th>次数</th>
                            </tr>
                            </thead>
                            <tbody>
                            <c:forEach items="${deviceStats}" var="s">
                                <tr>
                                    <td>${s.name}</td>
                                    <td>${s.count}</td>
                                </tr>
                            </c:forEach>
                            <c:if test="${empty deviceStats}">
                                <tr><td colspan="2" class="text-center text-muted py-3">暂无数据</td></tr>
                            </c:if>
                            </tbody>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
