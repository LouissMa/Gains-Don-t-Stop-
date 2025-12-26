<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>论坛 - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .wrap { max-width: 1100px; margin: 0 auto; padding: 20px; display: grid; grid-template-columns: 420px 1fr; gap: 20px; }
        .card { background: #fff; border: 1px solid #eee; border-radius: 12px; box-shadow: 0 2px 6px rgba(0,0,0,0.04); padding: 18px; }
        .post { border-top: 1px solid #f0f0f0; padding-top: 14px; margin-top: 14px; }
        .meta { color: #666; font-size: 13px; display: flex; justify-content: space-between; gap: 10px; }
        .title { font-size: 16px; font-weight: 700; margin-top: 6px; }
        .content { margin-top: 10px; white-space: pre-wrap; line-height: 1.6; }
        .images { margin-top: 10px; display: flex; flex-wrap: wrap; gap: 10px; }
        .images img { width: 120px; height: 120px; object-fit: cover; border-radius: 10px; border: 1px solid #eee; }
        .msg { padding: 10px 12px; border-radius: 10px; margin-bottom: 14px; background: #fff2f0; border: 1px solid #ffccc7; color: #cf1322; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="wrap">
    <div class="card">
        <h2 style="margin-top: 0;">分享体验</h2>
        <c:if test="${param.error == 'invalid'}">
            <div class="msg">请填写标题和内容</div>
        </c:if>
        <c:if test="${param.error == 'save_failed'}">
            <div class="msg">发帖失败，请稍后重试</div>
        </c:if>
        <c:choose>
            <c:when test="${not empty sessionScope.user}">
                <form action="forum" method="post" enctype="multipart/form-data">
                    <div class="form-group">
                        <label>关联商品（可选）</label>
                        <select name="productId" style="width: 100%; padding: 12px; border: 1px solid #e0e0e0; border-radius: 8px; box-sizing: border-box;">
                            <option value="">不关联</option>
                            <c:forEach items="${products}" var="p">
                                <option value="${p.id}">${p.name}</option>
                            </c:forEach>
                        </select>
                    </div>
                    <div class="form-group">
                        <label>标题</label>
                        <input type="text" name="title" required placeholder="例如：这款狗粮掉毛多不多？">
                    </div>
                    <div class="form-group">
                        <label>内容</label>
                        <textarea name="content" rows="6" required placeholder="聊聊质量、包装、口味、耐用度等真实体验～"></textarea>
                    </div>
                    <div class="form-group">
                        <label>图片（可多选）</label>
                        <input type="file" name="images" accept="image/*" multiple>
                    </div>
                    <button type="submit" class="btn btn-primary">发布</button>
                </form>
            </c:when>
            <c:otherwise>
                <div>登录后才能发帖：<a href="login" style="color: #ff914d; text-decoration: underline;">去登录</a></div>
            </c:otherwise>
        </c:choose>
    </div>

    <div class="card">
        <h2 style="margin-top: 0;">大家都在聊</h2>
        <c:choose>
            <c:when test="${empty posts}">
                <div style="color: #888;">暂无帖子</div>
            </c:when>
            <c:otherwise>
                <c:forEach items="${posts}" var="post">
                    <div class="post">
                        <div class="meta">
                            <div>
                                <strong>${post.username}</strong>
                                <c:if test="${not empty post.productName}">
                                    <span style="margin-left: 8px; color: #999;">#${post.productName}</span>
                                </c:if>
                            </div>
                            <div style="color: #999;">${post.createTime}</div>
                        </div>
                        <div class="title">${post.title}</div>
                        <div class="content">${post.content}</div>
                        <c:if test="${not empty post.imageUrls}">
                            <div class="images">
                                <c:forEach items="${post.imageUrls}" var="img">
                                    <img src="${pageContext.request.contextPath}/${img}" alt="post-image">
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
