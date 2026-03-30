<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<html>
<head>
    <title>发布商品 - 校园生活服务系统</title>
    <style>
        .form-container {
            max-width: 700px;
            margin: 2rem auto;
        }
        .form-header {
            background: var(--header-gradient);
            color: white;
            padding: 2rem;
            border-radius: var(--border-radius) var(--border-radius) 0 0;
            text-align: center;
        }
        .form-body {
            background: white;
            padding: 2.5rem;
            border-radius: 0 0 var(--border-radius) var(--border-radius);
            box-shadow: var(--shadow);
        }
        .form-group {
            margin-bottom: 1.5rem;
        }
        .form-label {
            font-weight: 700;
            color: var(--heading-color);
            margin-bottom: 0.5rem;
            display: block;
            font-size: 0.9rem;
        }
        .form-control {
            border: 1px solid #d1d3e2;
            border-radius: var(--border-radius);
            padding: 0.75rem 1rem;
            width: 100%;
            box-sizing: border-box;
            transition: border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
        }
        .form-control:focus {
            border-color: #bac8f3;
            outline: 0;
            box-shadow: 0 0 0 0.2rem rgba(78, 115, 223, 0.25);
        }
        .submit-btn {
            background: var(--primary-color);
            color: white;
            padding: 0.75rem 2rem;
            border: none;
            border-radius: 2rem;
            font-weight: 700;
            width: 100%;
            margin-top: 1rem;
            cursor: pointer;
            transition: all 0.2s;
        }
        .submit-btn:hover {
            background: var(--primary-hover);
            transform: translateY(-2px);
            box-shadow: 0 0.5rem 1rem rgba(0,0,0,0.15);
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
        <div class="form-container">
            <div class="form-header">
                <h2 style="margin:0;">📢 发布新商品</h2>
                <p style="margin: 0.5rem 0 0; opacity: 0.8;">让你的闲置物品焕发新生</p>
            </div>
            <div class="form-body">
                <form:form modelAttribute="item" method="post" action="${pageContext.request.contextPath}/item/add">
                    <div class="form-group">
                        <label class="form-label">商品名称</label>
                        <form:input path="name" class="form-control" placeholder="例如：九成新机械键盘" required="true"/>
                    </div>
                    <div class="form-group">
                        <label class="form-label">详细描述</label>
                        <form:textarea path="description" class="form-control" rows="4" placeholder="请描述商品的成色、购买时间等信息..." required="true"/>
                    </div>
                    <div class="form-grid" style="display: grid; grid-template-columns: 1fr 1fr; gap: 1rem;">
                        <div class="form-group">
                            <label class="form-label">期望价格 (元)</label>
                            <form:input path="price" type="number" step="0.01" class="form-control" placeholder="0.00" required="true"/>
                        </div>
                        <div class="form-group">
                            <label class="form-label">所属分类</label>
                            <form:select path="category" class="form-control">
                                <form:option value="电子产品">📱 电子产品</form:option>
                                <form:option value="书籍">📚 学习书籍</form:option>
                                <form:option value="生活用品">🏠 生活用品</form:option>
                                <form:option value="服装">👕 潮流服装</form:option>
                                <form:option value="其他">🎁 其他</form:option>
                            </form:select>
                        </div>
                    </div>
                    <div class="form-group">
                        <label class="form-label">联系方式</label>
                        <form:input path="contact" class="form-control" required="true" placeholder="微信、手机号或QQ"/>
                    </div>
                    <div class="form-group">
                        <label class="form-label">卖家信息</label>
                        <input type="text" name="sellerName" value="${not empty sessionScope.currentUser ? sessionScope.currentUser.name : '匿名校友'}" class="form-control" readonly style="background: #f8f9fc; cursor: not-allowed;"/>
                    </div>
                    
                    <div style="display: flex; gap: 1rem; margin-top: 2rem;">
                        <button type="submit" class="submit-btn">立即发布</button>
                        <a href="${pageContext.request.contextPath}/item/list" class="btn btn-secondary" style="flex: 0.4; display: flex; align-items: center; justify-content: center; border-radius: 2rem;">返回市场</a>
                    </div>
                </form:form>
            </div>
        </div>
    </main>
</body>
</html>
