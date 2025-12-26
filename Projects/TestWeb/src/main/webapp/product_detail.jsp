<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>${product.name} - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .container { padding: 40px; display: flex; justify-content: center; gap: 40px; }
        .product-image img { max-width: 400px; border-radius: 8px; }
        .product-info { max-width: 400px; }
        .price { color: #d9534f; font-size: 2em; font-weight: bold; margin: 20px 0; }
        .description { color: #666; line-height: 1.6; }
        .btn { background-color: #28a745; color: white; padding: 15px 30px; border: none; border-radius: 4px; font-size: 1.1em; cursor: pointer; }
        .btn:hover { background-color: #218838; }
        input[type="number"] { padding: 10px; width: 60px; font-size: 1.1em; margin-right: 10px; }
        .review-wrap { max-width: 880px; margin: 0 auto; padding: 0 40px 40px; }
        .review-card { background: #fff; border: 1px solid #eee; border-radius: 10px; padding: 16px; margin-bottom: 12px; box-shadow: 0 2px 4px rgba(0,0,0,0.04); }
        .review-meta { color: #666; font-size: 13px; display: flex; justify-content: space-between; gap: 10px; }
        .review-content { margin-top: 10px; white-space: pre-wrap; line-height: 1.6; }
        .review-images { margin-top: 10px; display: flex; gap: 10px; flex-wrap: wrap; }
        .review-images img { width: 96px; height: 96px; object-fit: cover; border-radius: 8px; border: 1px solid #eee; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="container">
    <div class="product-image">
        <img src="${pageContext.request.contextPath}/${product.imageUrl != null ? product.imageUrl : 'images/product-placeholder.jpg'}" alt="${product.name}">
    </div>
    <div class="product-info">
        <h1>${product.name}</h1>
        <div class="price">¥${product.price}</div>
        <p class="description">${product.description}</p>
        <p>库存: ${product.stock}</p>
        
        <form action="add-to-cart" method="post">
            <input type="hidden" name="productId" value="${product.id}">
            <input type="number" name="quantity" value="1" min="1" max="${product.stock}">
            <button type="submit" class="btn">加入购物车</button>
        </form>
    </div>
</div>

<div class="review-wrap">
    <h2 style="margin-top: 0;">商品评价</h2>
    <c:if test="${param.error == 'review_failed'}">
        <div class="review-card" style="border-color:#ffccc7; background:#fff2f0; color:#cf1322;">提交评价失败，请稍后重试</div>
    </c:if>

    <c:choose>
        <c:when test="${empty reviews}">
            <div class="review-card">暂无评价，快来写下第一条评价吧～</div>
        </c:when>
        <c:otherwise>
            <c:forEach items="${reviews}" var="r">
                <div class="review-card">
                    <div class="review-meta">
                        <div>
                            <strong>${r.username}</strong>
                            <span style="margin-left: 10px;">评分：${r.rating}/5</span>
                            <span style="margin-left: 10px; color: #999;">${r.productName}</span>
                        </div>
                        <div style="color: #999;">${r.createTime}</div>
                    </div>
                    <div class="review-content">${r.content}</div>
                    <c:if test="${not empty r.imageUrls}">
                        <div class="review-images">
                            <c:forEach items="${r.imageUrls}" var="img">
                                <img src="${pageContext.request.contextPath}/${img}" alt="review-image">
                            </c:forEach>
                        </div>
                    </c:if>
                </div>
            </c:forEach>
        </c:otherwise>
    </c:choose>

    <c:choose>
        <c:when test="${not empty sessionScope.user}">
            <div class="review-card" style="margin-top: 18px;">
                <h3 style="margin-top: 0;">发布评价</h3>
                <form action="review" method="post" enctype="multipart/form-data">
                    <input type="hidden" name="productId" value="${product.id}">
                    <div style="display: flex; gap: 12px; align-items: center; flex-wrap: wrap;">
                        <label>评分：</label>
                        <select name="rating" required style="padding: 10px; border: 1px solid #e0e0e0; border-radius: 8px;">
                            <option value="5">5 - 好评</option>
                            <option value="4">4</option>
                            <option value="3">3</option>
                            <option value="2">2</option>
                            <option value="1">1 - 差评</option>
                        </select>
                        <input type="file" name="images" accept="image/*" multiple>
                    </div>
                    <div style="margin-top: 12px;">
                        <textarea name="content" required rows="4" placeholder="分享下你对商品质量、包装、适口性等方面的真实感受～" style="width: 100%; padding: 12px; border: 1px solid #e0e0e0; border-radius: 8px; box-sizing: border-box;"></textarea>
                    </div>
                    <div style="margin-top: 12px;">
                        <button type="submit" class="btn">提交评价</button>
                    </div>
                </form>
            </div>
        </c:when>
        <c:otherwise>
            <div class="review-card" style="margin-top: 18px;">
                登录后才能发布评价：<a href="login" style="color: #28a745; text-decoration: underline;">去登录</a>
            </div>
        </c:otherwise>
    </c:choose>
</div>

</body>
</html>
