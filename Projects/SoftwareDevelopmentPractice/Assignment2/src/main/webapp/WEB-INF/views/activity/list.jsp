<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>活动中心 - 校园生活服务系统</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/static/css/style.css">
    <style>
        .activity-banner {
            background: linear-gradient(135deg, #f39c12, #e67e22);
            color: white;
            padding: 40px 30px;
            border-radius: var(--border-radius);
            margin-bottom: 30px;
            text-align: center;
        }
        .activity-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(350px, 1fr));
            gap: 25px;
        }
        .activity-card {
            background: var(--white);
            border-radius: var(--border-radius);
            padding: 25px;
            box-shadow: var(--shadow);
            border-left: 6px solid var(--warning-color);
            transition: transform 0.3s;
        }
        .activity-card:hover { transform: translateX(5px); }
        .activity-header { display: flex; justify-content: space-between; align-items: flex-start; margin-bottom: 15px; }
        .activity-tag {
            background: #fff3e0;
            color: #ef6c00;
            padding: 3px 10px;
            border-radius: 20px;
            font-size: 0.8rem;
            font-weight: 600;
        }
        .activity-title { font-size: 1.3rem; font-weight: bold; color: var(--secondary-color); margin-bottom: 10px; }
        .activity-info { font-size: 0.9rem; color: var(--dark-gray); margin-bottom: 8px; display: flex; align-items: center; }
        .activity-info i { margin-right: 8px; width: 16px; text-align: center; }
        .activity-desc { background: #f9f9f9; padding: 12px; border-radius: 4px; margin: 15px 0; font-size: 0.9rem; color: #555; }
        .progress-container { margin: 15px 0; }
        .progress-bar { height: 8px; background: #eee; border-radius: 4px; overflow: hidden; margin-top: 5px; }
        .progress-fill { height: 100%; background: var(--warning-color); transition: width 0.5s; }
        .btn-join { width: 100%; margin-top: 10px; padding: 12px; font-weight: bold; }
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

    <main class="content-container">
        <div class="activity-banner">
            <h1 style="margin:0;">🎉 校园精彩活动</h1>
            <p style="margin-top:10px; opacity:0.9;">探索学术讲座、体育赛事与文艺演出</p>
        </div>

        <div class="activity-grid">
            <c:forEach items="${activities}" var="activity">
                <c:set var="typeClass" value="${activity.type == '学术' ? 'academic' : (activity.type == '体育' ? 'sports' : 'entertainment')}" />
                <c:set var="progress" value="${(activity.currentParticipants / activity.maxParticipants) * 100}" />
                <div class="activity-card activity-type-${typeClass}">
                    <div class="activity-header">
                        <div class="activity-tag tag-${typeClass}">
                            ${activity.type}
                        </div>
                        <span class="badge ${activity.status == '报名中' ? 'badge-success' : 'badge-warning'}">${activity.status}</span>
                    </div>
                    <div class="activity-title">${activity.title}</div>
                    <div class="activity-info">🏢 <span>${activity.organizer}</span></div>
                    <div class="activity-info">📍 <span>${activity.location}</span></div>
                    <div class="activity-info">⏰ <span><fmt:formatDate value="${activity.startTime}" pattern="MM-dd HH:mm"/></span></div>
                    
                    <div class="activity-desc">${activity.description}</div>
                    
                    <div class="progress-container">
                        <div style="display:flex; justify-content:space-between; font-size:0.8rem; color:var(--dark-gray);">
                            <span>已报名 ${activity.currentParticipants} 人</span>
                            <span>上限 ${activity.maxParticipants} 人</span>
                        </div>
                        <div class="progress-bar">
                            <c:set var="progressWidth" value="width: ${progress}%;" />
                            <div class="progress-fill fill-${typeClass}" style="${progressWidth}"></div>
                        </div>
                        </div>
                    </div>

                    <c:if test="${activity.status == '报名中'}">
                        <button class="btn btn-warning btn-join" onclick="joinActivity('${activity.activityId}')">立即报名</button>
                    </c:if>
                </div>
            </c:forEach>
        </div>
    </main>

    <footer class="main-footer">
        <p>&copy; 2026 校园生活服务系统 - 软件开发实践作业</p>
    </footer>

    <script>
        function joinActivity(id) {
            let studentId = '${sessionScope.currentUser.studentId}';
            if (!studentId) {
                studentId = prompt("您尚未登录，请输入您的学号进行报名:");
            }
            if (!studentId) return;

            fetch('${pageContext.request.contextPath}/api/activities/' + id + '/join', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ studentId: studentId })
            })
            .then(response => response.json())
            .then(data => {
                alert(data.message);
                if (data.code === 200) {
                    location.reload();
                }
            })
            .catch(error => {
                console.error('Error:', error);
                alert('报名失败');
            });
        }
    </script>
</body>
</html>
