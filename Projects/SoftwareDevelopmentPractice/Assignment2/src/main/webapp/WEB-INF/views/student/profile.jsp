<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE html>
<html>
<head>
    <title>个人信息 - 校园生活服务系统</title>
    <style>
        .profile-container {
            max-width: 800px;
            margin: 2rem auto;
        }
        .profile-header {
            background: var(--header-gradient);
            color: white;
            padding: 3rem 2rem;
            border-radius: var(--border-radius) var(--border-radius) 0 0;
            text-align: center;
            position: relative;
        }
        .avatar-circle {
            width: 100px;
            height: 100px;
            background: white;
            border-radius: 50%;
            margin: 0 auto 1rem;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 3rem;
            color: var(--primary-color);
            box-shadow: var(--shadow);
        }
        .profile-body {
            background: white;
            padding: 2rem;
            border-radius: 0 0 var(--border-radius) var(--border-radius);
            box-shadow: var(--shadow);
        }
        .info-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 1.5rem;
            margin-bottom: 2rem;
        }
        .info-item {
            border-bottom: 1px solid #e3e6f0;
            padding-bottom: 0.75rem;
        }
        .info-label {
            font-size: 0.75rem;
            text-transform: uppercase;
            font-weight: 800;
            color: #b7b9cc;
            margin-bottom: 0.25rem;
            display: block;
        }
        .info-value {
            font-size: 1.1rem;
            font-weight: 700;
            color: var(--text-color);
        }
        .hobby-tags {
            display: flex;
            gap: 0.5rem;
            flex-wrap: wrap;
            margin-top: 0.5rem;
        }
        .hobby-tag {
            background: #f8f9fc;
            color: #4e73df;
            padding: 0.25rem 0.75rem;
            border-radius: 1rem;
            font-size: 0.8rem;
            font-weight: 700;
            border: 1px solid #e3e6f0;
        }
        .action-bar {
            margin-top: 2rem;
            display: flex;
            gap: 1rem;
            justify-content: center;
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
                        <a href="${pageContext.request.contextPath}/student/profile/${sessionScope.currentUser.studentId}" class="active">Hi, ${sessionScope.currentUser.name}</a>
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
        <div class="profile-container">
            <c:if test="${not empty student}">
                <div class="profile-header">
                    <div class="avatar-circle">👤</div>
                    <h2 style="margin:0;">${student.name}</h2>
                    <p style="opacity:0.8; margin-top:0.5rem;">${student.nickname != null ? student.nickname : "活跃的小城用户"}</p>
                </div>
                <div class="profile-body">
                    <div class="info-grid">
                        <div class="info-item">
                            <span class="info-label">学号 (Student ID)</span>
                            <span class="info-value">${student.studentId}</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">性别 (Gender)</span>
                            <span class="info-value">${student.gender}</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">年龄 (Age)</span>
                            <span class="info-value">${student.age} 岁</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">专业 (Major)</span>
                            <span class="info-value">${student.major}</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">年级 (Grade)</span>
                            <span class="info-value">${student.grade}</span>
                        </div>
                        <div class="info-item">
                            <span class="info-label">注册时间 (Join Date)</span>
                            <span class="info-value"><fmt:formatDate value="${student.registerTime}" pattern="yyyy-MM-dd"/></span>
                        </div>
                    </div>

                    <div class="info-item" style="margin-bottom: 1.5rem; border:none;">
                        <span class="info-label">我的爱好 (Hobbies)</span>
                        <div class="hobby-tags">
                            <c:forEach items="${student.hobbies}" var="hobby">
                                <span class="hobby-tag">${hobby}</span>
                            </c:forEach>
                        </div>
                    </div>

                    <div class="info-item" style="border:none;">
                        <span class="info-label">个人简介 (Bio)</span>
                        <p style="color: #858796; font-style: italic;">"${student.introduction != null && student.introduction != '' ? student.introduction : '这个用户很懒，什么都没有写~'}"</p>
                    </div>

                    <div class="action-bar">
                        <a href="${pageContext.request.contextPath}/student/edit/${student.studentId}" class="btn btn-primary">编辑资料</a>
                        <a href="${pageContext.request.contextPath}/student/courses" class="btn btn-success">去选课</a>
                        <a href="${pageContext.request.contextPath}/student/myCourses?studentId=${student.studentId}" class="btn btn-info" style="color: white;">我的课表</a>
                    </div>
                </div>
            </c:if>
            <c:if test="${empty student}">
                <div class="card" style="text-align: center;">
                    <p>学生信息不存在。</p>
                    <a href="${pageContext.request.contextPath}/student/toRegister" class="btn btn-primary">去注册</a>
                </div>
            </c:if>
        </div>
    </main>
</body>
</html>
