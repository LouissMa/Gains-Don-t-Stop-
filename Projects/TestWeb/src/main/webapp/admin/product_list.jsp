<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>商品与库存 - 店铺工作台</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css" rel="stylesheet">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body class="admin-shell">

<jsp:include page="header.jsp"/>

<main class="admin-content">
    <div class="container-fluid">
        <div class="d-flex align-items-center justify-content-between mb-3">
            <h2 class="m-0 fw-bold">商品与库存</h2>
            <a href="products?action=new" class="btn btn-primary">
                <i class="bi bi-plus-lg me-1"></i>上新商品
            </a>
        </div>

        <div class="card border-0 shadow-sm">
            <div class="card-body p-0">
                <table class="table table-hover align-middle m-0">
        <thead>
            <tr>
                <th>ID</th>
                <th>名称</th>
                <th>价格</th>
                <th>库存</th>
                <th>热卖</th>
                <th>操作</th>
            </tr>
        </thead>
        <tbody>
            <c:forEach var="p" items="${products}">
                <tr>
                    <td>${p.id}</td>
                    <td>${p.name}</td>
                    <td>¥${p.price}</td>
                    <td>${p.stock}</td>
                    <td>${p.isHot ? '是' : '否'}</td>
                    <td>
                        <a href="products?action=edit&id=${p.id}" class="btn btn-outline-primary btn-sm">
                            <i class="bi bi-pencil-square me-1"></i>编辑
                        </a>
                        <a href="products?action=delete&id=${p.id}" class="btn btn-outline-danger btn-sm" onclick="return confirm('确定要删除吗？')">
                            <i class="bi bi-trash3 me-1"></i>删除
                        </a>
                    </td>
                </tr>
            </c:forEach>
        </tbody>
                </table>
            </div>
        </div>
    </div>
</main>

</body>
</html>
