<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>我的订单 - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .container { padding: 20px; max-width: 800px; margin: 0 auto; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 12px; border-bottom: 1px solid #ddd; text-align: left; }
        th { background-color: #f8f9fa; }
        .success { color: green; margin-bottom: 20px; text-align: center; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="container">
    <h2>我的订单</h2>

    <c:if test="${param.success}">
        <div class="success">下单成功！</div>
    </c:if>

    <c:choose>
        <c:when test="${empty orders}">
            <p>您还没有订单。</p>
        </c:when>
        <c:otherwise>
            <table>
                <thead>
                <tr>
                    <th>订单号</th>
                    <th>下单时间</th>
                    <th>状态</th>
                    <th>总金额</th>
                </tr>
                </thead>
                <tbody>
                <c:forEach var="order" items="${orders}">
                    <tr>
                        <td>#${order.id}</td>
                        <td>${order.createTime}</td>
                        <td>${order.status}</td>
                        <td>¥${order.totalAmount}</td>
                    </tr>
                </c:forEach>
                </tbody>
            </table>
        </c:otherwise>
    </c:choose>
</div>

</body>
</html>
