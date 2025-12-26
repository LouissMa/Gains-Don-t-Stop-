<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>注册 - 宠物商城</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body class="auth-body">

<div class="auth-container" style="max-width: 450px;">
    <div style="text-align: center; margin-bottom: 20px;">
        <a href="home">
            <img src="${pageContext.request.contextPath}/images/logo.png" alt="宠物商城" style="height: 60px;">
        </a>
    </div>
    <h2 class="auth-title">创建新账号</h2>
    
    <c:if test="${not empty error}">
        <div style="color: #ff4d4f; text-align: center; margin-bottom: 20px; background: #fff1f0; padding: 10px; border-radius: 4px; border: 1px solid #ffccc7;">
            ${error}
        </div>
    </c:if>
    
    <form action="register" method="post">
        <div class="form-group">
            <label>注册身份</label>
            <div class="role-picker">
                <label class="role-option">
                    <input type="radio" name="role" value="USER" checked>
                    <div class="role-card">
                        <div class="role-title">
                            <span>买家</span>
                            <span class="role-state">已选择</span>
                        </div>
                        <div class="role-desc">逛商城、下单、评价</div>
                    </div>
                </label>
                <label class="role-option">
                    <input type="radio" name="role" value="MERCHANT">
                    <div class="role-card">
                        <div class="role-title">
                            <span>店主</span>
                            <span class="role-state">已选择</span>
                        </div>
                        <div class="role-desc">管理商品、处理订单</div>
                    </div>
                </label>
            </div>
        </div>
        <div class="form-group">
            <label>用户名</label>
            <input type="text" name="username" required placeholder="请输入用户名">
        </div>
        <div class="form-group">
            <label>密码</label>
            <input type="password" name="password" required placeholder="请输入密码">
        </div>
        <div style="display: flex; gap: 15px;">
            <div class="form-group" style="flex: 1;">
                <label>邮箱</label>
                <input type="email" name="email" placeholder="example@email.com">
            </div>
            <div class="form-group" style="flex: 1;">
                <label>电话</label>
                <input type="text" name="phone" placeholder="您的联系电话">
            </div>
        </div>
        <div class="form-group">
            <label>地址</label>
            <textarea name="address" rows="2" placeholder="收货地址" style="width: 100%; padding: 12px; border: 1px solid var(--border-color); border-radius: 8px; box-sizing: border-box; font-family: inherit;"></textarea>
        </div>
        <button type="submit" class="btn btn-primary" style="width: 100%; margin-top: 10px; padding: 12px;">立即注册</button>
    </form>
    
    <div style="text-align: center; margin-top: 20px; font-size: 14px;">
        已有账号？ <a href="login" style="color: var(--primary-color); font-weight: bold;">去登录</a>
    </div>
</div>

</body>
</html>
