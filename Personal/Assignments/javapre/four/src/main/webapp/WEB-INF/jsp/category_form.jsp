<%@ include file="/WEB-INF/jsp/_base.jspf" %>
<!DOCTYPE html>
<html>
<head>
    <title>分类表单</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
<%@ include file="/WEB-INF/jsp/_nav.jspf" %>
<div class="container mt-4" style="max-width: 820px;">
    <c:if test="${not empty message}">
        <div class="alert alert-danger">${message}</div>
    </c:if>
    <div class="card">
        <div class="card-body">
            <h5 class="card-title mb-3">分类信息</h5>
            <form method="post" action="${ctx}${action}">
                <div class="row">
                    <div class="col-md-6 mb-3">
                        <label class="form-label">分类名称</label>
                        <input class="form-control" name="categoryName" value="${form.categoryName}" required>
                    </div>
                    <div class="col-md-6 mb-3">
                        <label class="form-label">父分类</label>
                        <select class="form-select" name="parentId">
                            <option value="">顶级分类</option>
                            <c:forEach items="${parents}" var="p">
                                <option value="${p.categoryId}" <c:if test="${form.parentId != null && form.parentId == p.categoryId}">selected</c:if>>${p.categoryName}</option>
                            </c:forEach>
                        </select>
                        <div class="form-text">只允许二级结构，二级分类的父分类必须是顶级分类</div>
                    </div>
                </div>
                <div class="mb-3">
                    <label class="form-label">描述</label>
                    <textarea class="form-control" name="description" rows="3">${form.description}</textarea>
                </div>
                <div class="d-flex gap-2">
                    <button class="btn btn-primary" type="submit">保存</button>
                    <a class="btn btn-secondary" href="${ctx}/admin/categories">返回</a>
                </div>
            </form>
        </div>
    </div>
</div>
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>
