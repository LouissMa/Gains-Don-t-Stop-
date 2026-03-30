<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>首页 - 校园生活服务系统</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/static/css/style.css">
    <style>
        .hero-section {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: var(--white);
            padding: 120px 20px;
            text-align: center;
            border-radius: 0;
            margin-bottom: 50px;
            box-shadow: inset 0 0 100px rgba(0,0,0,0.1);
        }
        .hero-section h1 { 
            font-size: 3.5rem; 
            margin-bottom: 20px; 
            font-weight: 800;
            text-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .hero-section p { 
            font-size: 1.25rem; 
            max-width: 700px; 
            margin: 0 auto 40px; 
            opacity: 0.9;
            font-weight: 300;
        }
        
        .module-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
            gap: 30px;
            margin-top: -100px;
            padding-bottom: 50px;
        }
        .module-card {
            background: var(--white);
            padding: 45px 35px;
            border-radius: 1rem;
            box-shadow: 0 1rem 3rem rgba(0,0,0,0.175);
            text-align: center;
            transition: all 0.3s ease;
            border: none;
            border-bottom: 5px solid transparent;
        }
        .module-card:hover { 
            transform: translateY(-15px); 
            box-shadow: 0 1.5rem 4rem rgba(0,0,0,0.2);
        }
        .module-card.border-primary { border-bottom-color: var(--primary-color); border-top: none; }
        .module-card.border-success { border-bottom-color: var(--success-color); border-top: none; }
        .module-card.border-warning { border-bottom-color: var(--warning-color); border-top: none; }
        
        .module-card h3 { 
            font-size: 1.75rem; 
            margin-bottom: 20px; 
            font-weight: 700;
            color: var(--heading-color);
        }
        .module-card p { 
            color: #858796; 
            margin-bottom: 30px; 
            height: 70px;
            font-size: 0.95rem;
        }
        .module-card .icon { 
            font-size: 3.5rem; 
            margin-bottom: 25px; 
            display: inline-block;
            transition: transform 0.3s ease;
        }
        .module-card:hover .icon { transform: scale(1.2) rotate(5deg); }
        
        .btn-large { 
            padding: 0.75rem 2rem; 
            font-size: 1rem; 
            border-radius: 2rem; 
            font-weight: 700;
            text-transform: uppercase;
            letter-spacing: 0.1rem;
            box-shadow: 0 4px 15px rgba(0,0,0,0.1);
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
            <a href="${pageContext.request.contextPath}/item/list">二手交易</a>
            <a href="${pageContext.request.contextPath}/activity/list">活动中心</a>
            <c:choose>
                <c:when test="${not empty sessionScope.currentUser}">
                    <span class="user-info">
                        <a href="${pageContext.request.contextPath}/student/profile/${sessionScope.currentUser.studentId}">Hi, ${sessionScope.currentUser.name}</a>
                    </span>
                    <a href="${pageContext.request.contextPath}/student/logout" style="color: var(--accent-color);">退出</a>
                </c:when>
                <c:otherwise>
                    <a href="${pageContext.request.contextPath}/student/login" class="btn btn-primary" style="color: white; padding: 5px 15px; border-radius: 20px;">登录</a>
                </c:otherwise>
            </c:choose>
        </nav>
    </header>

    <section class="hero-section">
        <h1>智慧校园 · 连接你我</h1>
        <p>集二手交易、课程管理、校园活动于一体的一站式生活服务平台，让大学生活更高效、更精彩。</p>
        <c:if test="${empty sessionScope.currentUser}">
            <a href="${pageContext.request.contextPath}/student/toRegister" class="btn btn-primary btn-large">立即开启校园生活</a>
        </c:if>
    </section>

    <main class="content-container">
        <div class="module-grid">
            <div class="module-card border-primary">
                <div class="icon">🛒</div>
                <h3>二手交易</h3>
                <p>宿舍好物，低价转让。在这里找到你需要的学习生活用品，变废为宝。</p>
                <a href="${pageContext.request.contextPath}/item/list" class="btn btn-primary btn-large">进入市场</a>
            </div>
            <div class="module-card border-success">
                <div class="icon">🎓</div>
                <h3>学生中心</h3>
                <p>管理个人资料，查看课表，选修心仪的课程。属于你的私人教务助手。</p>
                <c:choose>
                    <c:when test="${not empty sessionScope.currentUser}">
                        <a href="${pageContext.request.contextPath}/student/profile/${sessionScope.currentUser.studentId}" class="btn btn-success btn-large">个人中心</a>
                    </c:when>
                    <c:otherwise>
                        <a href="${pageContext.request.contextPath}/student/toRegister" class="btn btn-success btn-large">立即注册</a>
                    </c:otherwise>
                </c:choose>
            </div>
            <div class="module-card border-warning">
                <div class="icon">📅</div>
                <h3>活动 API</h3>
                <p>获取校园最新活动资讯，支持 RESTful JSON 接口接入，赋能开发者。</p>
                <a href="${pageContext.request.contextPath}/activity/list" class="btn btn-warning btn-large">浏览活动</a>
            </div>
        </div>
    </main>

    <footer class="main-footer">
        <p>&copy; 2026 校园生活服务系统 - 软件开发实践作业 | 助力美好校园生活</p>
    </footer>
</body>
</html>
