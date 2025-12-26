<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
<link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">

<header class="main-header">
    <div class="nav-container">
        <a href="home" class="logo">
            <img src="${pageContext.request.contextPath}/images/logo.png" alt="宠物商城" onerror="this.src='https://via.placeholder.com/150x50?text=PetStore'">
        </a>
        
        <nav class="nav-links">
            <a href="home">首页</a>
            <a href="products">全部商品</a>
            <a href="cart">购物车</a>
            <a href="forum">论坛</a>
        </nav>

        <div class="nav-user">
            <c:choose>
                <c:when test="${not empty sessionScope.user}">
                    <a href="orders">我的订单</a>
                    <a href="pet?action=list">我的宠物</a>
                    <a href="account">个人中心</a>
                    <div style="display: flex; align-items: center;">
                        <span style="color: #666; margin-right: 8px;">您好，${sessionScope.user.username}</span>
                        <img src="${pageContext.request.contextPath}/${empty sessionScope.user.avatarUrl ? 'images/user-avatar-default.png' : sessionScope.user.avatarUrl}" alt="Avatar" style="width: 32px; height: 32px; border-radius: 50%; border: 1px solid #e0e0e0; object-fit: cover;">
                    </div>
                    <a href="logout" class="btn btn-danger" style="padding: 5px 15px; font-size: 14px;">退出</a>
                </c:when>
                <c:otherwise>
                    <a href="login">登录</a>
                    <a href="register" class="btn btn-primary" style="padding: 5px 15px; font-size: 14px;">注册</a>
                </c:otherwise>
            </c:choose>
        </div>
    </div>
</header>
<br>
