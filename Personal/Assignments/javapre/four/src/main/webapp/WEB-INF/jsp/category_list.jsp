<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>分类管理</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4">
    <div class="d-flex justify-content-between align-items-center mb-3">
        <h5 class="mb-0">分类管理（支持二级）</h5>
        <a class="btn btn-success" href="${ctx}/admin/categories/new">新增分类</a>
    </div>

    <div class="card">
        <div class="card-body">
            <div class="table-responsive">
                <table class="table table-hover align-middle">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>名称</th>
                        <th>父分类</th>
                        <th>描述</th>
                        <th style="width: 200px;">操作</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${categories}" var="c">
                        <tr>
                            <td>${c.categoryId}</td>
                            <td>
                                <c:if test="${c.parentId != null}">└ </c:if>
                                ${c.categoryName}
                            </td>
                            <td>
                                <c:choose>
                                    <c:when test="${c.parentId == null}">顶级</c:when>
                                    <c:otherwise>${categoryMap[c.parentId]}</c:otherwise>
                                </c:choose>
                            </td>
                            <td>${c.description}</td>
                            <td>
                                <a class="btn btn-sm btn-outline-secondary" href="${ctx}/admin/categories/${c.categoryId}/edit">编辑</a>
                                <form method="post" action="${ctx}/admin/categories/${c.categoryId}/delete" style="display:inline;">
                                    <button class="btn btn-sm btn-outline-danger" type="submit">删除</button>
                                </form>
                            </td>
                        </tr>
                    </c:forEach>
                    <c:if test="${empty categories}">
                        <tr>
                            <td colspan="5" class="text-center text-muted py-4">暂无数据</td>
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
