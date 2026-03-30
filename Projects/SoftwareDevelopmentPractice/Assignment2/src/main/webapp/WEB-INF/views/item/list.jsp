<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>商品列表 - 校园生活服务系统</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/static/css/style.css">
    <style>
        .page-header {
            background: var(--white);
            padding: 2rem;
            border-radius: var(--border-radius);
            margin-bottom: 2rem;
            box-shadow: var(--shadow);
            display: flex;
            flex-direction: column;
            gap: 1.5rem;
        }
        .page-title-section {
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .page-title-section h1 {
            margin: 0;
            font-size: 1.75rem;
            font-weight: 800;
            color: var(--heading-color);
        }
        .filter-bar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding-top: 1rem;
            border-top: 1px solid #e3e6f0;
        }
        .filter-links {
            display: flex;
            gap: 0.5rem;
            flex-wrap: wrap;
        }
        .filter-links a {
            padding: 0.5rem 1.25rem;
            border-radius: 2rem;
            background: #f8f9fc;
            color: #4e73df;
            text-decoration: none;
            font-weight: 700;
            font-size: 0.85rem;
            border: 1px solid #e3e6f0;
            transition: all 0.2s;
        }
        .filter-links a:hover, .filter-links a.active {
            background: var(--primary-color);
            color: var(--white);
            border-color: var(--primary-color);
            box-shadow: 0 0.125rem 0.25rem 0 rgba(0, 0, 0, 0.075);
        }
        
        .item-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 1.5rem;
        }
        .item-card {
            background: var(--white);
            border-radius: var(--border-radius);
            overflow: hidden;
            box-shadow: var(--shadow);
            transition: all 0.3s cubic-bezier(0.25, 0.8, 0.25, 1);
            position: relative;
            border: 1px solid #e3e6f0;
        }
        .item-card:hover { 
            transform: translateY(-5px); 
            box-shadow: 0 0.5rem 2rem 0 rgba(0, 0, 0, 0.1);
        }
        .item-img {
            height: 200px;
            background: linear-gradient(45deg, #f8f9fc 0%, #eaecf4 100%);
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 4rem;
            transition: all 0.3s;
        }
        .item-card:hover .item-img {
            background: linear-gradient(45deg, #eaecf4 0%, #dddfeb 100%);
        }
        .item-content { padding: 1.5rem; }
        .item-price { 
            color: var(--accent-color); 
            font-size: 1.5rem; 
            font-weight: 800; 
            margin-bottom: 0.5rem; 
        }
        .item-name { 
            font-size: 1.2rem; 
            font-weight: 700; 
            margin-bottom: 0.75rem; 
            display: block; 
            color: var(--heading-color); 
            text-decoration: none; 
        }
        .item-name:hover { color: var(--primary-hover); }
        .item-meta { 
            font-size: 0.85rem; 
            color: #858796; 
            margin-bottom: 1rem;
            display: flex;
            flex-wrap: wrap;
            gap: 0.75rem;
        }
        .item-meta span {
            display: flex;
            align-items: center;
            gap: 0.25rem;
        }
        .item-footer { 
            background: #f8f9fc;
            border-top: 1px solid #e3e6f0; 
            padding: 1rem 1.5rem; 
            display: flex; 
            justify-content: space-between; 
            align-items: center; 
        }
        .status-sold { filter: grayscale(0.8); opacity: 0.8; }
        .sold-badge {
            position: absolute;
            top: 1rem;
            right: -2rem;
            background: #e74a3b;
            color: white;
            padding: 0.25rem 3rem;
            transform: rotate(45deg);
            font-weight: 800;
            font-size: 0.75rem;
            text-transform: uppercase;
            box-shadow: 0 0.15rem 1.75rem 0 rgba(0,0,0,0.15);
            z-index: 5;
        }
    </style>
</head>
<body>
    <header class="main-header">
        <div class="logo">
            <h2>校园生活服务系统</h2>
        </div>
        <nav class="nav-menu">
            <a href="${pageContext.request.contextPath}/index.jsp">首页</a>
            <a href="${pageContext.request.contextPath}/item/list" class="active">二手交易</a>
            <a href="${pageContext.request.contextPath}/activity/list">活动中心</a>
            <c:choose>
                <c:when test="${not empty sessionScope.currentUser}">
                    <span class="user-info">
                        <a href="${pageContext.request.contextPath}/student/profile/${sessionScope.currentUser.studentId}">Hi, ${sessionScope.currentUser.name}</a>
                    </span>
                    <a href="${pageContext.request.contextPath}/student/logout" style="color: #fff; background: rgba(255,255,255,0.2); padding: 0.25rem 0.75rem; border-radius: 1rem; margin-left: 1rem;">退出</a>
                </c:when>
                <c:otherwise>
                    <a href="${pageContext.request.contextPath}/student/login" style="background: var(--white); color: var(--primary-color); padding: 0.4rem 1.25rem; border-radius: 2rem;">登录</a>
                </c:otherwise>
            </c:choose>
        </nav>
    </header>

    <main class="content-container">
        <div class="page-header">
            <div class="page-title-section">
                <h1>🛒 二手市场</h1>
                <div class="action-btns">
                    <a href="${pageContext.request.contextPath}/item/my" class="btn btn-secondary" style="margin-right: 0.5rem;">我的发布</a>
                    <a href="${pageContext.request.contextPath}/item/toAdd" class="btn btn-primary">+ 发布商品</a>
                </div>
            </div>
            
            <div class="filter-bar">
                <div class="filter-links">
                    <a href="${pageContext.request.contextPath}/item/list" class="${empty category ? 'active' : ''}">全部物品</a>
                    <a href="${pageContext.request.contextPath}/item/category/电子产品" class="${category == '电子产品' ? 'active' : ''}">电子产品</a>
                    <a href="${pageContext.request.contextPath}/item/category/书籍" class="${category == '书籍' ? 'active' : ''}">学习书籍</a>
                    <a href="${pageContext.request.contextPath}/item/category/生活用品" class="${category == '生活用品' ? 'active' : ''}">生活用品</a>
                    <a href="${pageContext.request.contextPath}/item/category/服装" class="${category == '服装' ? 'active' : ''}">潮流服装</a>
                </div>
            </div>
        </div>

        <div class="item-grid">
            <c:forEach items="${items}" var="item">
                <div class="item-card ${item.status == '已售出' ? 'status-sold' : ''}">
                    <c:if test="${item.status == '已售出'}">
                        <div class="sold-badge">SOLD OUT</div>
                    </c:if>
                    <div class="item-img">
                        <c:choose>
                            <c:when test="${item.category == '电子产品'}">💻</c:when>
                            <c:when test="${item.category == '书籍'}">📖</c:when>
                            <c:when test="${item.category == '服装'}">👕</c:when>
                            <c:otherwise>📦</c:otherwise>
                        </c:choose>
                    </div>
                    <div class="item-content">
                        <div class="item-price">¥${item.price}</div>
                        <a href="${pageContext.request.contextPath}/item/detail/${item.id}" class="item-name">${item.name}</a>
                        <div class="item-meta">
                            <span>📂 ${item.category}</span>
                            <span>👤 ${item.sellerName}</span>
                        </div>
                        <div style="font-size: 0.75rem; color: #b7b9cc; display: flex; align-items: center; gap: 0.25rem;">
                            🕒 <fmt:formatDate value="${item.publishTime}" pattern="MM-dd HH:mm"/> 发布
                        </div>
                    </div>
                    <div class="item-footer">
                        <a href="${pageContext.request.contextPath}/item/detail/${item.id}" class="btn btn-primary" style="font-size: 0.75rem; padding: 0.4rem 1rem;">查看详情</a>
                        <c:if test="${sessionScope.currentUser.name == item.sellerName}">
                            <div style="display: flex; gap: 0.25rem;">
                                <c:if test="${item.status == '出售中'}">
                                    <form action="${pageContext.request.contextPath}/item/sold/${item.id}" method="post" style="display:inline;">
                                        <button type="submit" class="btn btn-success" style="font-size: 0.75rem; padding: 0.4rem 0.75rem;">标记已售</button>
                                    </form>
                                </c:if>
                                <form action="${pageContext.request.contextPath}/item/delete/${item.id}" method="post" style="display:inline;">
                                    <button type="submit" class="btn btn-danger" style="font-size: 0.75rem; padding: 0.4rem 0.75rem;" onclick="return confirm('确定要删除这件心爱的宝贝吗？')">删除</button>
                                </form>
                            </div>
                        </c:if>
                    </div>
                </div>
            </c:forEach>
        </div>

        <c:if test="${empty items}">
            <div class="card" style="text-align: center; padding: 100px;">
                <p style="font-size: 1.2rem; color: var(--dark-gray);">暂无相关商品</p>
                <a href="${pageContext.request.contextPath}/item/toAdd" class="btn btn-primary">去发布一个吧</a>
            </div>
        </c:if>
    </main>

    <footer class="main-footer">
        <p>&copy; 2026 校园生活服务系统 - 软件开发实践作业</p>
    </footer>
</body>
</html>
