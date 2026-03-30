<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
    <title>我的课表 - 校园生活服务系统</title>
    <style>
        .schedule-container {
            background: white;
            padding: 2.5rem;
            border-radius: var(--border-radius);
            box-shadow: var(--shadow);
            margin-top: 2rem;
        }
        .schedule-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 2rem;
            padding-bottom: 1rem;
            border-bottom: 2px solid #f8f9fc;
        }
        .course-card-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 1.5rem;
        }
        .course-mini-card {
            border: 1px solid #e3e6f0;
            border-radius: var(--border-radius);
            padding: 1.5rem;
            border-left: 5px solid var(--primary-color);
            transition: transform 0.2s;
        }
        .course-mini-card:hover {
            transform: scale(1.02);
            box-shadow: 0 0.5rem 1rem rgba(0,0,0,0.1);
        }
        .mini-card-title {
            font-weight: 800;
            color: var(--heading-color);
            margin-bottom: 0.5rem;
            font-size: 1.1rem;
        }
        .mini-card-teacher {
            font-size: 0.85rem;
            color: #858796;
            margin-bottom: 1rem;
        }
        .mini-card-info {
            font-size: 0.9rem;
            margin-bottom: 0.5rem;
            display: flex;
            align-items: center;
            gap: 0.5rem;
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
                    <a href="${pageContext.request.contextPath}/student/logout" style="color: #fff; background: rgba(255,255,255,0.2); padding: 0.25rem 0.75rem; border-radius: 1rem; margin-left: 1rem;">退出</a>
                </c:when>
                <c:otherwise>
                    <a href="${pageContext.request.contextPath}/student/login" style="background: var(--white); color: var(--primary-color); padding: 0.4rem 1.25rem; border-radius: 2rem;">登录</a>
                </c:otherwise>
            </c:choose>
        </nav>
    </header>

    <main class="content-container">
        <div class="schedule-container">
            <div class="schedule-header">
                <h2 style="margin:0; color: var(--heading-color); font-weight: 800;">🗓️ 我的个性课表</h2>
                <a href="${pageContext.request.contextPath}/student/courses" class="btn btn-primary" style="border-radius: 2rem;">+ 继续选课</a>
            </div>

            <c:if test="${not empty courseList}">
                <div class="course-card-grid">
                    <c:forEach items="${courseList}" var="course">
                        <div class="course-mini-card">
                            <div class="mini-card-title">${course.courseName}</div>
                            <div class="mini-card-teacher">👨‍🏫 ${course.teacher} | ${course.credits} 学分</div>
                            <div class="mini-card-info">🕒 ${course.timeSlot}</div>
                            <div class="mini-card-info">📍 ${course.location}</div>
                        </div>
                    </c:forEach>
                </div>
            </c:if>
            <c:if test="${empty courseList}">
                <div style="text-align: center; padding: 4rem;">
                    <p style="font-size: 1.2rem; color: #858796;">您目前还没有选修任何课程。</p>
                    <a href="${pageContext.request.contextPath}/student/courses" class="btn btn-primary" style="margin-top: 1rem;">立即去选课</a>
                </div>
            </c:if>

            <div style="margin-top: 3rem; display: flex; justify-content: center; gap: 1rem;">
                <a href="${pageContext.request.contextPath}/student/profile/${studentId}" class="btn btn-secondary" style="border-radius: 2rem; padding: 0.75rem 2rem;">返回个人中心</a>
                <a href="${pageContext.request.contextPath}/index.jsp" class="btn btn-info" style="border-radius: 2rem; padding: 0.75rem 2rem; color: white;">返回首页</a>
            </div>
        </div>
    </main>
</body>
</html>
