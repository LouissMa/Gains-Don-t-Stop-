<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>用户管理</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <form class="row g-2 align-items-end mb-3" method="get" action="${ctx}/admin/users">
        <div class="col-md-8">
            <label class="form-label">关键字</label>
            <input class="form-control" name="keyword" value="${keyword}" placeholder="用户名/姓名/学号(工号)">
        </div>
        <div class="col-md-2">
            <label class="form-label">每页</label>
            <select class="form-select" name="size">
                <option value="5" <c:if test="${userPage.size == 5}">selected</c:if>>5</option>
                <option value="10" <c:if test="${userPage.size == 10}">selected</c:if>>10</option>
                <option value="20" <c:if test="${userPage.size == 20}">selected</c:if>>20</option>
                <option value="50" <c:if test="${userPage.size == 50}">selected</c:if>>50</option>
            </select>
        </div>
        <div class="col-md-2 d-grid">
            <button class="btn btn-primary" type="submit">查询</button>
        </div>
    </form>

    <div class="d-flex justify-content-between align-items-center mb-2">
        <h5 class="mb-0">用户管理</h5>
        <a class="btn btn-success" href="${ctx}/admin/users/new">新增用户</a>
    </div>

    <div class="card">
        <div class="card-body">
            <div class="table-responsive">
                <table class="table table-hover align-middle">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>用户名</th>
                        <th>姓名</th>
                        <th>学号/工号</th>
                        <th>角色</th>
                        <th>状态</th>
                        <th>最近登录</th>
                        <th style="width: 260px;">操作</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${userPage.list}" var="u">
                        <tr>
                            <td>${u.userId}</td>
                            <td>${u.username}</td>
                            <td>${u.realName}</td>
                            <td>${u.studentNo}</td>
                            <td>${u.role}</td>
                            <td>${u.status}</td>
                            <td><fmt:formatDate value="${u.lastLoginTime}" pattern="yyyy-MM-dd HH:mm:ss"/></td>
                            <td>
                                <a class="btn btn-sm btn-outline-secondary" href="${ctx}/admin/users/${u.userId}/edit">编辑</a>
                                <c:if test="${u.status == 'active'}">
                                    <form method="post" action="${ctx}/admin/users/${u.userId}/disable" style="display:inline;">
                                        <button class="btn btn-sm btn-outline-warning" type="submit">禁用</button>
                                    </form>
                                </c:if>
                                <c:if test="${u.status == 'inactive'}">
                                    <form method="post" action="${ctx}/admin/users/${u.userId}/enable" style="display:inline;">
                                        <button class="btn btn-sm btn-outline-success" type="submit">启用</button>
                                    </form>
                                </c:if>
                                <form method="post" action="${ctx}/admin/users/${u.userId}/delete" style="display:inline;">
                                    <button class="btn btn-sm btn-outline-danger" type="submit">删除</button>
                                </form>
                            </td>
                        </tr>
                    </c:forEach>
                    <c:if test="${empty userPage.list}">
                        <tr>
                            <td colspan="8" class="text-center text-muted py-4">暂无数据</td>
                        </tr>
                    </c:if>
                    </tbody>
                </table>
            </div>

            <c:set var="totalPages" value="${userPage.totalPages}"/>
            <c:if test="${totalPages > 1}">
                <nav>
                    <ul class="pagination">
                        <li class="page-item ${userPage.page <= 1 ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/admin/users?page=${userPage.page-1}&size=${userPage.size}&keyword=${keyword}">上一页</a>
                        </li>
                        <c:forEach begin="1" end="${totalPages}" var="p">
                            <li class="page-item ${userPage.page == p ? 'active' : ''}">
                                <a class="page-link" href="${ctx}/admin/users?page=${p}&size=${userPage.size}&keyword=${keyword}">${p}</a>
                            </li>
                        </c:forEach>
                        <li class="page-item ${userPage.page >= totalPages ? 'disabled' : ''}">
                            <a class="page-link" href="${ctx}/admin/users?page=${userPage.page+1}&size=${userPage.size}&keyword=${keyword}">下一页</a>
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
