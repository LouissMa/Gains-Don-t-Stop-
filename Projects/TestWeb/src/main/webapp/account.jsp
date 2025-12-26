<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>个人中心 - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .page { max-width: 1100px; margin: 0 auto; padding: 20px; display: grid; grid-template-columns: 360px 1fr; gap: 20px; }
        .card { background: white; border: 1px solid #eee; border-radius: 12px; box-shadow: 0 2px 6px rgba(0,0,0,0.04); padding: 20px; }
        .row { display: flex; gap: 12px; align-items: center; }
        .avatar { width: 72px; height: 72px; border-radius: 50%; border: 1px solid #eee; object-fit: cover; background: #fafafa; }
        .muted { color: #888; font-size: 13px; }
        .pill { display: inline-block; padding: 6px 10px; border-radius: 999px; background: #fff3e8; color: #ff914d; font-size: 12px; }
        .review-item { border-top: 1px solid #f0f0f0; padding-top: 14px; margin-top: 14px; }
        .review-meta { display: flex; justify-content: space-between; gap: 10px; color: #666; font-size: 13px; }
        .review-content { margin-top: 8px; white-space: pre-wrap; line-height: 1.6; }
        .images { margin-top: 10px; display: flex; flex-wrap: wrap; gap: 10px; }
        .images img { width: 96px; height: 96px; object-fit: cover; border-radius: 10px; border: 1px solid #eee; }
        textarea { resize: vertical; }
        .msg { padding: 10px 12px; border-radius: 10px; margin-bottom: 14px; }
        .msg-ok { background: #f6ffed; border: 1px solid #b7eb8f; color: #389e0d; }
        .msg-err { background: #fff2f0; border: 1px solid #ffccc7; color: #cf1322; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="page">
    <div class="card">
        <c:if test="${param.success == '1'}">
            <div class="msg msg-ok">保存成功</div>
        </c:if>
        <c:if test="${param.error == 'save_failed'}">
            <div class="msg msg-err">保存失败，请稍后重试</div>
        </c:if>

        <div class="row">
            <img class="avatar" src="${pageContext.request.contextPath}/${empty profile.avatarUrl ? 'images/user-avatar-default.png' : profile.avatarUrl}" alt="avatar">
            <div>
                <div style="font-size: 18px; font-weight: 600;">${profile.username}</div>
                <div class="muted">注册时间：${profile.createTime}</div>
                <div style="margin-top: 8px;"><span class="pill">${profile.role}</span></div>
            </div>
        </div>

        <div style="margin-top: 18px;">
            <h3 style="margin: 0 0 10px;">个人资料</h3>
            <form action="account" method="post" enctype="multipart/form-data">
                <div class="form-group">
                    <label>头像</label>
                    <input type="file" name="avatar" accept="image/*">
                </div>
                <div class="form-group">
                    <label>邮箱</label>
                    <input type="email" name="email" value="${profile.email}">
                </div>
                <div class="form-group">
                    <label>电话</label>
                    <input type="text" name="phone" value="${profile.phone}">
                </div>
                <div class="form-group">
                    <label>收货地址</label>
                    <input type="text" name="address" value="${profile.address}">
                </div>
                <div class="form-group">
                    <label>个人简介</label>
                    <textarea name="bio" rows="4" placeholder="写点关于你和毛孩子的小故事～">${profile.bio}</textarea>
                </div>
                <button type="submit" class="btn btn-primary">保存</button>
            </form>
        </div>
    </div>

    <div class="card">
        <h2 style="margin-top: 0;">我的评价</h2>
        <c:choose>
            <c:when test="${empty myReviews}">
                <div class="muted">你还没有发表过评价，去商品详情页写一条吧～</div>
            </c:when>
            <c:otherwise>
                <c:forEach items="${myReviews}" var="r">
                    <div class="review-item">
                        <div class="review-meta">
                            <div>
                                <strong>${r.productName}</strong>
                                <span style="margin-left: 10px;">评分：${r.rating}/5</span>
                            </div>
                            <div style="color: #999;">${r.createTime}</div>
                        </div>
                        <div class="review-content">${r.content}</div>
                        <c:if test="${not empty r.imageUrls}">
                            <div class="images">
                                <c:forEach items="${r.imageUrls}" var="img">
                                    <img src="${pageContext.request.contextPath}/${img}" alt="review-image">
                                </c:forEach>
                            </div>
                        </c:if>
                    </div>
                </c:forEach>
            </c:otherwise>
        </c:choose>
    </div>
</div>

</body>
</html>

