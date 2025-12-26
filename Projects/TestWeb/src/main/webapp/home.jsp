<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>首页 - 宠物商城</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <script>
        let currentSlide = 0;
        function showSlide(index) {
            const slides = document.querySelector('.slides');
            const dots = document.querySelectorAll('.slider-dot');
            const totalSlides = document.querySelectorAll('.slide').length;
            
            if (index >= totalSlides) currentSlide = 0;
            else if (index < 0) currentSlide = totalSlides - 1;
            else currentSlide = index;
            
            slides.style.transform = 'translateX(-' + (currentSlide * 100) + '%)';
            
            dots.forEach(dot => dot.classList.remove('active'));
            dots[currentSlide].classList.add('active');
        }
        
        setInterval(() => showSlide(currentSlide + 1), 5000);
    </script>
</head>
<body>

<jsp:include page="header.jsp"/>

<!-- Banner Slider -->
<div class="slider">
    <div class="slides">
        <div class="slide"><img src="${pageContext.request.contextPath}/images/banner-home1.jpg" alt="Banner 1" onerror="this.src='https://via.placeholder.com/1200x400?text=Banner1'"></div>
        <div class="slide"><img src="${pageContext.request.contextPath}/images/banner-home2.jpg" alt="Banner 2" onerror="this.src='https://via.placeholder.com/1200x400?text=Banner2'"></div>
        <div class="slide"><img src="${pageContext.request.contextPath}/images/banner-home3.jpg" alt="Banner 3" onerror="this.src='https://via.placeholder.com/1200x400?text=Banner3'"></div>
    </div>
    <div class="slider-nav">
        <div class="slider-dot active" onclick="showSlide(0)"></div>
        <div class="slider-dot" onclick="showSlide(1)"></div>
        <div class="slider-dot" onclick="showSlide(2)"></div>
    </div>
</div>

<c:if test="${not empty sessionScope.user}">
    <div class="container">
        <h2 style="text-align: center; margin: 40px 0 20px; color: #555;">✨ 猜您喜欢</h2>
        <div class="product-grid">
            <c:forEach var="p" items="${recommendedProducts}">
                <div class="product-card">
                    <a href="product?id=${p.id}">
                        <img src="${pageContext.request.contextPath}/${p.imageUrl != null && p.imageUrl != '' ? p.imageUrl : 'images/product-placeholder.jpg'}" alt="${p.name}">
                    </a>
                    <div class="product-info">
                        <h3 class="product-title" title="${p.name}">${p.name}</h3>
                        <div style="display: flex; justify-content: space-between; align-items: center; margin-top: 10px;">
                            <span class="product-price">¥${p.price}</span>
                            <a href="product?id=${p.id}" class="btn btn-primary" style="padding: 5px 12px; font-size: 13px;">查看</a>
                        </div>
                    </div>
                </div>
            </c:forEach>
        </div>
    </div>
</c:if>

<div class="container">
    <h2 style="text-align: center; margin: 40px 0 20px; color: #555;">🔥 热门好物推荐</h2>
    <div class="product-grid">
        <c:forEach var="p" items="${hotProducts}">
            <div class="product-card">
                <a href="product?id=${p.id}">
                    <img src="${pageContext.request.contextPath}/${p.imageUrl != null && p.imageUrl != '' ? p.imageUrl : 'images/product-placeholder.jpg'}" alt="${p.name}">
                </a>
                <div class="product-info">
                    <h3 class="product-title" title="${p.name}">${p.name}</h3>
                    <div style="display: flex; justify-content: space-between; align-items: center; margin-top: 10px;">
                        <span class="product-price">¥${p.price}</span>
                        <a href="product?id=${p.id}" class="btn btn-primary" style="padding: 5px 12px; font-size: 13px;">查看</a>
                    </div>
                </div>
            </div>
        </c:forEach>
    </div>
    
    <c:if test="${empty hotProducts}">
        <div style="text-align: center; padding: 40px; color: #888;">
            <p>暂无热门商品，敬请期待！</p>
        </div>
    </c:if>
</div>

</body>
</html>
