<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>${not empty product ? '编辑' : '上新'} 商品 - 店铺工作台</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css" rel="stylesheet">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body class="admin-shell">

<jsp:include page="header.jsp"/>

<main class="admin-content">
    <div class="container-fluid" style="max-width: 980px;">
        <div class="d-flex align-items-center justify-content-between mb-3">
            <h2 class="m-0 fw-bold">${not empty product ? '编辑' : '上新'} 商品</h2>
            <a class="btn btn-outline-secondary" href="products">
                <i class="bi bi-arrow-left me-1"></i>回到商品列表
            </a>
        </div>

        <div class="card border-0 shadow-sm">
            <div class="card-body p-4">
        <form action="products" method="post" enctype="multipart/form-data">
            <input type="hidden" name="id" value="${product.id}">
        
            <div class="mb-3">
                <label class="form-label">商品名称</label>
                <input class="form-control" type="text" name="name" value="${product.name}" required>
            </div>
        
            <div class="mb-3">
                <label class="form-label">分类</label>
                <select class="form-select" name="categoryId">
                    <option value="1" ${product.categoryId == 1 ? 'selected' : ''}>食品</option>
                    <option value="2" ${product.categoryId == 2 ? 'selected' : ''}>玩具</option>
                    <option value="3" ${product.categoryId == 3 ? 'selected' : ''}>用品</option>
                </select>
            </div>
        
            <div class="row g-3">
                <div class="col-12 col-md-6">
                    <div class="mb-3">
                        <label class="form-label">价格</label>
                        <input class="form-control" type="number" step="0.01" name="price" value="${product.price}" required>
                    </div>
                </div>
                <div class="col-12 col-md-6">
                    <div class="mb-3">
                        <label class="form-label">库存</label>
                        <input class="form-control" type="number" name="stock" value="${product.stock}" required>
                    </div>
                </div>
            </div>
        
            <div class="mb-3">
                <label class="form-label">商品图片</label>
                <input class="form-control" type="file" name="image" accept="image/*">
                <c:if test="${not empty product.imageUrl}">
                    <div class="form-text">当前：${product.imageUrl}</div>
                </c:if>
            </div>

            <div class="mb-3">
                <label class="form-label">图片链接（可选）</label>
                <input class="form-control" type="text" name="imageUrl" value="${product.imageUrl}">
            </div>
        
            <div class="mb-3">
                <label class="form-label">描述</label>
                <textarea class="form-control" name="description" rows="5">${product.description}</textarea>
            </div>
        
            <div class="form-check mb-4">
                <input class="form-check-input" type="checkbox" id="isHot" name="isHot" value="true" ${product.isHot ? 'checked' : ''}>
                <label class="form-check-label" for="isHot">热卖推荐</label>
            </div>
        
            <button type="submit" class="btn btn-primary">
                <i class="bi bi-save me-1"></i>保存商品
            </button>
        </form>
            </div>
        </div>
    </div>
</main>

</body>
</html>
