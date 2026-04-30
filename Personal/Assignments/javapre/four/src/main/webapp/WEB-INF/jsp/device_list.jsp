<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>设备列表</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <form class="row g-2 align-items-end mb-3" method="get" action="${ctx}/devices">
        <div class="col-md-4">
            <label class="form-label">关键字</label>
            <input class="form-control" name="keyword" value="${keyword}" placeholder="名称/型号/位置">
        </div>
        <div class="col-md-4">
            <label class="form-label">分类</label>
            <select class="form-select" name="categoryId">
                <option value="">全部</option>
                <c:forEach items="${categories}" var="c">
                    <option value="${c.categoryId}" <c:if test="${categoryId != null && categoryId == c.categoryId}">selected</c:if>>
                        ${c.categoryName}
                    </option>
                </c:forEach>
            </select>
        </div>
        <div class="col-md-2">
            <label class="form-label">每页</label>
            <select class="form-select" name="size">
                <option value="5" <c:if test="${devicePage.size == 5}">selected</c:if>>5</option>
                <option value="10" <c:if test="${devicePage.size == 10}">selected</c:if>>10</option>
                <option value="20" <c:if test="${devicePage.size == 20}">selected</c:if>>20</option>
                <option value="50" <c:if test="${devicePage.size == 50}">selected</c:if>>50</option>
            </select>
        </div>
        <div class="col-md-2 d-grid">
            <button class="btn btn-primary" type="submit">查询</button>
        </div>
    </form>

    <div class="card">
        <div class="card-body">
            <div class="d-flex justify-content-between align-items-center mb-2">
                <div class="fw-bold">设备列表</div>
                <c:if test="${sessionScope.SESSION_USER.role == 'admin'}">
                    <a class="btn btn-sm btn-success" href="${ctx}/admin/devices/new">新增设备</a>
                </c:if>
            </div>
            <div class="table-responsive">
                <table class="table table-hover align-middle">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>名称</th>
                        <th>型号</th>
                        <th>分类</th>
                        <th>位置</th>
                        <th>购入日期</th>
                        <th>状态</th>
                        <th>最长借用天数</th>
                        <th style="width: 220px;">操作</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${devicePage.list}" var="d">
                        <tr>
                            <td>${d.deviceId}</td>
                            <td><a href="${ctx}/devices/${d.deviceId}">${d.deviceName}</a></td>
                            <td>${d.deviceModel}</td>
                            <td>${categoryMap[d.categoryId]}</td>
                            <td>${d.location}</td>
                            <td><fmt:formatDate value="${d.purchaseDate}" pattern="yyyy-MM-dd"/></td>
                            <td>${d.status}</td>
                            <td>${d.maxBorrowDays}</td>
                            <td>
                                <a class="btn btn-sm btn-outline-primary" href="${ctx}/devices/${d.deviceId}">详情</a>
                                <c:if test="${sessionScope.SESSION_USER.role == 'admin'}">
                                    <a class="btn btn-sm btn-outline-secondary" href="${ctx}/admin/devices/${d.deviceId}/edit">编辑</a>
                                    <form method="post" action="${ctx}/admin/devices/${d.deviceId}/delete" style="display:inline;">
                                        <button class="btn btn-sm btn-outline-danger" type="submit">删除</button>
                                    </form>
                                </c:if>
                            </td>
                        </tr>
                    </c:forEach>
                    <c:if test="${empty devicePage.list}">
                        <tr>
                            <td colspan="9" class="text-center text-muted py-4">暂无数据</td>
                        </tr>
                    </c:if>
                    </tbody>
                </table>
            </div>

            <c:set var="totalPages" value="${devicePage.totalPages}"/>
            <c:if test="${totalPages > 1}">
                <nav>
                    <ul class="pagination">
                        <li class="page-item ${devicePage.page <= 1 ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/devices?page=${devicePage.page-1}&size=${devicePage.size}&keyword=${keyword}&categoryId=${categoryId}">上一页</a>
                        </li>
                        <c:forEach begin="1" end="${totalPages}" var="p">
                            <li class="page-item ${devicePage.page == p ? 'active' : ''}">
                                <a class="page-link" href="${ctx}/devices?page=${p}&size=${devicePage.size}&keyword=${keyword}&categoryId=${categoryId}">${p}</a>
                            </li>
                        </c:forEach>
                        <li class="page-item ${devicePage.page >= totalPages ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/devices?page=${devicePage.page+1}&size=${devicePage.size}&keyword=${keyword}&categoryId=${categoryId}">下一页</a>
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
