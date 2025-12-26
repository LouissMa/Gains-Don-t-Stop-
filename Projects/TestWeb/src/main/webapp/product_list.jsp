<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>商品列表 - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .product-grid { display: flex; flex-wrap: wrap; padding: 20px; gap: 20px; }
        .product-card { border: 1px solid #ddd; border-radius: 8px; padding: 15px; width: 200px; text-align: center; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
        .product-card img { max-width: 100%; height: 150px; object-fit: cover; }
        .price { color: #d9534f; font-weight: bold; font-size: 1.2em; }
        .btn { background-color: #007bff; color: white; padding: 8px 15px; text-decoration: none; border-radius: 4px; display: inline-block; margin-top: 10px; }
        .search-bar { display: flex; gap: 10px; flex-wrap: wrap; align-items: center; margin: 10px 0 18px; }
        .search-input { flex: 1; min-width: 220px; padding: 10px 12px; border: 1px solid #ddd; border-radius: 8px; font-size: 14px; }
        .search-btn { background: #ff914d; border: none; color: #fff; padding: 10px 14px; border-radius: 8px; cursor: pointer; font-weight: 700; }
        .search-btn:hover { background: #e67e3c; }
        .search-clear { color: #666; text-decoration: none; padding: 10px 6px; }
        .empty-tip { padding: 30px 20px; color: #777; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div style="padding: 20px;">
    <form class="search-bar" action="products" method="get">
        <input class="search-input" type="text" name="q" value="${keyword}" placeholder="搜索商品关键词：例如 猫粮 / 逗猫棒 / 狗绳">
        <button class="search-btn" type="submit">搜索</button>
        <c:if test="${not empty keyword}">
            <a class="search-clear" href="products">清空</a>
        </c:if>
    </form>

    <c:choose>
        <c:when test="${not empty keyword}">
            <h2>搜索结果：${keyword}</h2>
        </c:when>
        <c:otherwise>
            <h2>全部商品</h2>
        </c:otherwise>
    </c:choose>

    <c:if test="${empty products}">
        <div class="empty-tip">没有找到相关商品，试试换个关键词。</div>
    </c:if>
    <div class="product-grid">
        <c:forEach var="p" items="${products}">
            <div class="product-card">
                <img src="${pageContext.request.contextPath}/${p.imageUrl != null ? p.imageUrl : 'images/product-placeholder.jpg'}" alt="${p.name}">
                <h3>${p.name}</h3>
                <p class="price">¥${p.price}</p>
                <a href="product?id=${p.id}" class="btn">查看详情</a>
            </div>
        </c:forEach>
    </div>
</div>

</body>
</html>
