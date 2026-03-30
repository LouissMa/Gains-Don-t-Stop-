<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<!DOCTYPE html>
<html>
<head>
    <title>学生注册 - 校园生活服务系统</title>
    <style>
        body {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            align-items: center;
            justify-content: center;
            padding: 2rem 0;
        }
        .register-card {
            width: 100%;
            max-width: 600px;
            background: var(--white);
            padding: 3rem;
            border-radius: 1rem;
            box-shadow: 0 1rem 3rem rgba(0,0,0,0.2);
        }
        .register-header { text-align: center; margin-bottom: 2.5rem; }
        .register-header h2 { color: var(--heading-color); font-weight: 800; margin-bottom: 0.5rem; }
        .register-header p { color: #858796; font-size: 0.95rem; }
        
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
    <div class="register-card">
        <div class="register-header">
            <h2>✨ 开启你的校园之旅</h2>
            <p>创建一个账号，发现更多精彩服务</p>
        </div>
        
        <form:form modelAttribute="student" method="post" action="${pageContext.request.contextPath}/student/register">
            <div class="form-grid">
                <div class="form-group">
                    <label class="form-label">学号 (Login ID)</label>
                    <form:input path="studentId" class="form-control" placeholder="20240001" required="true"/>
                </div>
                <div class="form-group">
                    <label class="form-label">登录密码</label>
                    <form:password path="password" class="form-control" placeholder="******" required="true"/>
                </div>
            </div>

            <div class="form-grid">
                <div class="form-group">
                    <label class="form-label">真实姓名</label>
                    <form:input path="name" class="form-control" placeholder="张三" required="true"/>
                </div>
                <div class="form-group">
                    <label class="form-label">个性昵称</label>
                    <form:input path="nickname" class="form-control" placeholder="小明同学"/>
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
                    <form:input path="age" type="number" class="form-control" placeholder="18"/>
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
                <form:textarea path="introduction" class="form-control" rows="3" placeholder="介绍一下你自己吧..."/>
            </div>

            <div style="margin-top: 2.5rem;">
                <button type="submit" class="btn btn-primary" style="width: 100%; padding: 1rem; border-radius: 2rem; font-weight: 800; font-size: 1rem; text-transform: uppercase; letter-spacing: 0.1rem;">立即注册账号</button>
            </div>
            
            <div style="text-align: center; margin-top: 1.5rem; font-size: 0.9rem;">
                已有账号？ <a href="${pageContext.request.contextPath}/student/login" style="color: var(--primary-color); font-weight: 700; text-decoration: none;">直接登录</a>
                <span style="margin: 0 1rem; color: #d1d3e2;">|</span>
                <a href="${pageContext.request.contextPath}/index.jsp" style="color: #858796; text-decoration: none;">返回首页</a>
            </div>
        </form:form>
    </div>
</body>
</html>
