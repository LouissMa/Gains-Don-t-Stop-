<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>口碑评价 - 店铺工作台</title>
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
            <h2 class="m-0 fw-bold">口碑评价</h2>
            <div class="text-muted small">看看顾客怎么说</div>
        </div>

    <c:choose>
        <c:when test="${empty reviews}">
            <div class="text-muted">暂无评价</div>
        </c:when>
        <c:otherwise>
            <div class="card border-0 shadow-sm">
                <div class="card-body p-0">
            <table class="table table-hover align-middle m-0">
                <thead>
                <tr>
                    <th>时间</th>
                    <th>用户</th>
                    <th>商品</th>
                    <th>评分</th>
                    <th>内容</th>
                    <th>图片</th>
                    <th>类型</th>
                </tr>
                </thead>
                <tbody>
                <c:forEach items="${reviews}" var="r">
                    <tr>
                        <td class="muted">${r.createTime}</td>
                        <td>${r.username}</td>
                        <td>${r.productName}</td>
                        <td>${r.rating}/5</td>
                        <td><div class="admin-text">${r.content}</div></td>
                        <td>
                            <c:if test="${not empty r.imageUrls}">
                                <div class="admin-images">
                                    <c:forEach items="${r.imageUrls}" var="img">
                                        <img src="${pageContext.request.contextPath}/${img}" alt="review-image">
                                    </c:forEach>
                                </div>
                            </c:if>
                        </td>
                        <td>
                            <c:choose>
                                <c:when test="${r.rating >= 4}">
                                    <span class="admin-tag admin-tag-good">好评</span>
                                </c:when>
                                <c:when test="${r.rating <= 2}">
                                    <span class="admin-tag admin-tag-bad">差评</span>
                                </c:when>
                                <c:otherwise>
                                    <span class="admin-tag admin-tag-mid">中评</span>
                                </c:otherwise>
                            </c:choose>
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
