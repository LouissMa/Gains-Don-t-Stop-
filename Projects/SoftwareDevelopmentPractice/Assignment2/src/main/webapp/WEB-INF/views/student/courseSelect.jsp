<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
    <title>选择课程 - 校园生活服务系统</title>
    <style>
        .course-container {
            background: white;
            padding: 2.5rem;
            border-radius: var(--border-radius);
            box-shadow: var(--shadow);
            margin-top: 2rem;
        }
        .course-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 2rem;
            padding-bottom: 1rem;
            border-bottom: 2px solid #f8f9fc;
        }
        .course-table {
            width: 100%;
            border-collapse: separate;
            border-spacing: 0 0.75rem;
        }
        .course-table th {
            background: #f8f9fc;
            color: #4e73df;
            text-transform: uppercase;
            font-size: 0.75rem;
            font-weight: 800;
            padding: 1rem;
            border: none;
        }
        .course-row {
            background: white;
            box-shadow: 0 0.15rem 1.75rem 0 rgba(58, 59, 69, 0.05);
            transition: all 0.2s;
        }
        .course-row:hover {
            background: #f8f9fc;
            transform: scale(1.01);
        }
        .course-row td {
            padding: 1rem;
            border-top: 1px solid #e3e6f0;
            border-bottom: 1px solid #e3e6f0;
        }
        .course-row td:first-child { border-left: 1px solid #e3e6f0; border-radius: var(--border-radius) 0 0 var(--border-radius); }
        .course-row td:last-child { border-right: 1px solid #e3e6f0; border-radius: 0 var(--border-radius) var(--border-radius) 0; }
        
        .checkbox-custom {
            width: 1.25rem;
            height: 1.25rem;
            cursor: pointer;
        }
        .badge-credits {
            background: #e3f2fd;
            color: #4e73df;
            padding: 0.25rem 0.5rem;
            border-radius: 0.25rem;
            font-weight: 700;
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
        <div class="course-container">
            <div class="course-header">
                <h2 style="margin:0; color: var(--heading-color); font-weight: 800;">📚 选课中心</h2>
                <div style="font-size: 0.9rem; color: #858796;">
                    当前登录：<strong style="color: var(--primary-color);">${sessionScope.currentUser.name} (${sessionScope.currentUser.studentId})</strong>
                </div>
            </div>

            <form:form modelAttribute="courseSelection" method="post" action="${pageContext.request.contextPath}/student/selectCourse">
                <form:hidden path="studentId" value="${sessionScope.currentUser.studentId}"/>
                <table class="course-table">
                    <thead>
                        <tr>
                            <th style="width: 50px;">选择</th>
                            <th>课程代码</th>
                            <th>课程名称</th>
                            <th>授课教师</th>
                            <th>学分</th>
                            <th>人数进度</th>
                            <th>上课时间</th>
                            <th>地点</th>
                        </tr>
                    </thead>
                    <tbody>
                        <c:forEach items="${courseList}" var="course">
                            <tr class="course-row">
                                <td style="text-align: center;">
                                    <form:checkbox path="courseIds" value="${course.courseId}" class="checkbox-custom"/>
                                </td>
                                <td style="font-weight: 700; color: #4e73df;">${course.courseId}</td>
                                <td style="font-weight: 700;">${course.courseName}</td>
                                <td>${course.teacher}</td>
                                <td><span class="badge-credits">${course.credits}</span></td>
                                <td>
                                    <div style="font-size: 0.8rem; margin-bottom: 0.25rem;">${course.selectedCount} / ${course.maxStudents}</div>
                                    <div style="height: 4px; background: #eaecf4; border-radius: 2px; width: 60px;">
                                        <div style="height: 100%; background: var(--success-color); border-radius: 2px; width: ${(course.selectedCount / course.maxStudents) * 100}%;"></div>
                                    </div>
                                </td>
                                <td style="font-size: 0.85rem;">${course.timeSlot}</td>
                                <td style="font-size: 0.85rem; color: #858796;">📍 ${course.location}</td>
                            </tr>
                        </c:forEach>
                    </tbody>
                </table>

                <div style="display: flex; gap: 1rem; margin-top: 3rem; justify-content: flex-end;">
                    <a href="javascript:history.back()" class="btn btn-secondary" style="padding: 0.75rem 2rem; border-radius: 2rem;">取消</a>
                    <button type="submit" class="btn btn-primary" style="padding: 0.75rem 3rem; border-radius: 2rem; font-weight: 800;">确认提交选课结果</button>
                </div>
            </form:form>
        </div>
    </main>
</body>
</html>
