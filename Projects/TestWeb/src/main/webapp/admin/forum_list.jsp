<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>社区互动 - 店铺工作台</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css" rel="stylesheet">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body class="admin-shell">

<jsp:include page="header.jsp"/>

<main class="admin-content">
    <div class="container-fluid">
        <div class="d-flex align-items-center justify-content-between mb-3">
            <h2 class="m-0 fw-bold">社区互动</h2>
            <div class="text-muted small">看看大家都在聊什么</div>
        </div>

    <c:choose>
        <c:when test="${empty posts}">
            <div class="text-muted">暂无帖子</div>
        </c:when>
        <c:otherwise>
            <div class="card border-0 shadow-sm">
                <div class="card-body p-0">
            <table class="table table-hover align-middle m-0">
                <thead>
                <tr>
                    <th>时间</th>
                    <th>用户</th>
                    <th>关联商品</th>
                    <th>标题</th>
                    <th>内容</th>
                    <th>图片</th>
                </tr>
                </thead>
                <tbody>
                <c:forEach items="${posts}" var="p">
                    <tr>
                        <td class="muted">${p.createTime}</td>
                        <td>${p.username}</td>
                        <td>
                            <c:choose>
                                <c:when test="${not empty p.productName}">${p.productName}</c:when>
                                <c:otherwise><span class="muted">无</span></c:otherwise>
                            </c:choose>
                        </td>
                        <td class="admin-title-cell">${p.title}</td>
                        <td><div class="admin-text">${p.content}</div></td>
                        <td>
                            <c:if test="${not empty p.imageUrls}">
                                <div class="admin-images">
                                    <c:forEach items="${p.imageUrls}" var="img">
                                        <img src="${pageContext.request.contextPath}/${img}" alt="post-image">
                                    </c:forEach>
                                </div>
                            </c:if>
                        </td>
                    </tr>
                </c:forEach>
                </tbody>
            </table>
                </div>
            </div>
        </c:otherwise>
    </c:choose>
    </div>
</main>

</body>
</html>
