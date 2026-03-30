<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<html>
<head>
    <title>商品详情 - 校园生活服务系统</title>
    <style>
        .detail-container {
            max-width: 900px;
            margin: 2rem auto;
            display: grid;
            grid-template-columns: 1fr 1.2fr;
            background: white;
            border-radius: var(--border-radius);
            overflow: hidden;
            box-shadow: var(--shadow);
        }
        .detail-img-side {
            background: linear-gradient(45deg, #f8f9fc 0%, #eaecf4 100%);
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 8rem;
        }
        .detail-info-side {
            padding: 3rem;
        }
        .detail-category {
            text-transform: uppercase;
            font-weight: 800;
            color: var(--primary-color);
            font-size: 0.85rem;
            margin-bottom: 0.5rem;
            display: block;
        }
        .detail-title {
            font-size: 2.25rem;
            font-weight: 800;
            color: var(--heading-color);
            margin-bottom: 1rem;
            line-height: 1.2;
        }
        .detail-price {
            font-size: 2rem;
            font-weight: 700;
            color: var(--accent-color);
            margin-bottom: 2rem;
            padding-bottom: 1rem;
            border-bottom: 1px solid #e3e6f0;
        }
        .detail-desc {
            color: #858796;
            font-size: 1rem;
            margin-bottom: 2rem;
            line-height: 1.6;
        }
        .detail-meta-box {
            background: #f8f9fc;
            padding: 1.5rem;
            border-radius: var(--border-radius);
            margin-bottom: 2rem;
        }
        .meta-row {
            display: flex;
            margin-bottom: 0.75rem;
        }
        .meta-row:last-child { margin-bottom: 0; }
        .meta-label {
            width: 100px;
            font-weight: 700;
            color: #4e73df;
            font-size: 0.85rem;
        }
        .meta-value {
            font-weight: 600;
            color: var(--text-color);
        }
        .status-badge {
            display: inline-block;
            padding: 0.25rem 1rem;
            border-radius: 2rem;
            font-weight: 700;
            font-size: 0.75rem;
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
        <div class="detail-container">
            <div class="detail-img-side">
                <c:choose>
                    <c:when test="${item.category == '电子产品'}">💻</c:when>
                    <c:when test="${item.category == '书籍'}">📖</c:when>
                    <c:when test="${item.category == '服装'}">👕</c:when>
                    <c:otherwise>📦</c:otherwise>
                </c:choose>
            </div>
            <div class="detail-info-side">
                <span class="detail-category">${item.category}</span>
                <h1 class="detail-title">${item.name}</h1>
                <div class="detail-price">¥${item.price}</div>
                
                <p class="detail-desc">${item.description}</p>
                
                <div class="detail-meta-box">
                    <div class="meta-row">
                        <span class="meta-label">卖家昵称</span>
                        <span class="meta-value">${item.sellerName}</span>
                    </div>
                    <div class="meta-row">
                        <span class="meta-label">联系方式</span>
                        <span class="meta-value" style="color: #1cc88a;">${item.contact}</span>
                    </div>
                    <div class="meta-row">
                        <span class="meta-label">发布时间</span>
                        <span class="meta-value"><fmt:formatDate value="${item.publishTime}" pattern="yyyy-MM-dd HH:mm"/></span>
                    </div>
                    <div class="meta-row">
                        <span class="meta-label">当前状态</span>
                        <span class="status-badge ${item.status == '出售中' ? 'badge-success' : 'badge-danger'}">
                            ${item.status}
                        </span>
                    </div>
                </div>

                <div style="display: flex; gap: 1rem;">
                    <a href="javascript:history.back()" class="btn btn-secondary" style="flex: 1; text-align: center; border-radius: 2rem; padding: 0.75rem;">返回上一页</a>
                    <c:if test="${sessionScope.currentUser.name == item.sellerName && item.status == '出售中'}">
                        <form action="${pageContext.request.contextPath}/item/sold/${item.id}" method="post" style="flex: 1;">
                            <button type="submit" class="btn btn-success" style="width: 100%; border-radius: 2rem; padding: 0.75rem;">设为已售</button>
                        </form>
                    </c:if>
                </div>
            </div>
        </div>
    </main>
</body>
</html>
