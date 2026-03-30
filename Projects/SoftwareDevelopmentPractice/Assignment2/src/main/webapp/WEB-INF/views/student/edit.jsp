<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<!DOCTYPE html>
<html>
<head>
    <title>编辑资料 - 校园生活服务系统</title>
    <style>
        .edit-container {
            max-width: 700px;
            margin: 2rem auto;
            background: white;
            border-radius: var(--border-radius);
            box-shadow: var(--shadow);
            overflow: hidden;
        }
        .edit-header {
            background: var(--header-gradient);
            color: white;
            padding: 2rem;
            text-align: center;
        }
        .edit-body {
            padding: 2.5rem;
        }
        .form-grid {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 1.5rem;
        }
        .form-group { margin-bottom: 1.25rem; }
        .form-label { display: block; margin-bottom: 0.5rem; font-weight: 700; color: #4e73df; font-size: 0.85rem; }
        .form-control {
            width: 100%;
            padding: 0.75rem 1rem;
            border: 1px solid #d1d3e2;
            border-radius: var(--border-radius);
            box-sizing: border-box;
            transition: all 0.2s;
        }
        .form-control:focus {
            border-color: #bac8f3;
            outline: 0;
            box-shadow: 0 0 0 0.2rem rgba(78, 115, 223, 0.25);
        }
        .checkbox-group, .radio-group {
            display: flex;
            flex-wrap: wrap;
            gap: 1rem;
            background: #f8f9fc;
            padding: 1rem;
            border-radius: var(--border-radius);
            border: 1px solid #d1d3e2;
        }
        .checkbox-item, .radio-item {
            display: flex;
            align-items: center;
            gap: 0.4rem;
            font-size: 0.9rem;
            color: var(--text-color);
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
        <div class="edit-container">
            <div class="edit-header">
                <h2 style="margin:0;">📝 修改个人资料</h2>
            </div>
            <div class="edit-body">
                <form:form modelAttribute="student" method="post" action="${pageContext.request.contextPath}/student/update">
                    <form:hidden path="studentId"/>
                    <div class="form-group">
                        <label class="form-label">学号 (不可修改)</label>
                        <input type="text" class="form-control" value="${student.studentId}" readonly style="background: #f8f9fc; color: #b7b9cc;"/>
                    </div>
                    
                    <div class="form-grid">
                        <div class="form-group">
                            <label class="form-label">真实姓名</label>
                            <form:input path="name" class="form-control" required="true"/>
                        </div>
                        <div class="form-group">
                            <label class="form-label">个性昵称</label>
                            <form:input path="nickname" class="form-control"/>
                        </div>
                    </div>

                    <div class="form-grid">
                        <div class="form-group">
                            <label class="form-label">性别</label>
                            <div class="radio-group">
                                <form:radiobuttons path="gender" items="${genderItems}" element="span class='radio-item'"/>
                            </div>
                        </div>
                        <div class="form-group">
                            <label class="form-label">年龄</label>
                            <form:input path="age" type="number" class="form-control"/>
                        </div>
                    </div>

                    <div class="form-grid">
                        <div class="form-group">
                            <label class="form-label">专业方向</label>
                            <form:select path="major" items="${majorItems}" class="form-control"/>
                        </div>
                        <div class="form-group">
                            <label class="form-label">所属年级</label>
                            <form:select path="grade" items="${gradeItems}" class="form-control"/>
                        </div>
                    </div>

                    <div class="form-group">
                        <label class="form-label">个人爱好</label>
                        <div class="checkbox-group">
                            <form:checkboxes path="hobbies" items="${hobbyItems}" element="span class='checkbox-item'"/>
                        </div>
                    </div>

                    <div class="form-group">
                        <label class="form-label">个人简介</label>
                        <form:textarea path="introduction" class="form-control" rows="3"/>
                    </div>

                    <div style="display: flex; gap: 1rem; margin-top: 2rem;">
                        <button type="submit" class="btn btn-primary" style="flex: 1; padding: 0.75rem; border-radius: 2rem; font-weight: 800;">保存所有修改</button>
                        <a href="${pageContext.request.contextPath}/student/profile/${student.studentId}" class="btn btn-secondary" style="flex: 0.5; padding: 0.75rem; border-radius: 2rem; display: flex; align-items: center; justify-content: center;">取消返回</a>
                    </div>
                </form:form>
            </div>
        </div>
    </main>
</body>
</html>
