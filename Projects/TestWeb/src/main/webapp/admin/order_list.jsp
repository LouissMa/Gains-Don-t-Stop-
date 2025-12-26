<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>订单处理 - 店铺工作台</title>
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
            <h2 class="m-0 fw-bold">订单处理</h2>
            <div class="text-muted small">发货与配送状态</div>
        </div>

        <div class="card border-0 shadow-sm">
            <div class="card-body p-0">
                <table class="table table-hover align-middle m-0">
        <thead>
            <tr>
                <th>订单号</th>
                <th>用户ID</th>
                <th>总金额</th>
                <th>下单时间</th>
                <th>状态</th>
                <th>操作</th>
            </tr>
        </thead>
        <tbody>
            <c:forEach var="order" items="${orders}">
                <tr>
                    <td>${order.id}</td>
                    <td>${order.userId}</td>
                    <td>¥${order.totalAmount}</td>
                    <td>${order.createTime}</td>
                    <td>${order.status}</td>
                    <td>
                        <form action="orders" method="post">
                            <input type="hidden" name="orderId" value="${order.id}">
                            <select class="form-select form-select-sm" name="status" style="width: auto;">
                                <option value="PENDING" ${order.status == 'PENDING' ? 'selected' : ''}>待发货</option>
                                <option value="SHIPPED" ${order.status == 'SHIPPED' ? 'selected' : ''}>已发货</option>
                                <option value="DELIVERED" ${order.status == 'DELIVERED' ? 'selected' : ''}>已送达</option>
                                <option value="CANCELLED" ${order.status == 'CANCELLED' ? 'selected' : ''}>已取消</option>
                            </select>
                            <button type="submit" class="btn btn-primary btn-sm">
                                <i class="bi bi-check2-circle me-1"></i>更新
                            </button>
                        </form>
                    </td>
                </tr>
            </c:forEach>
        </tbody>
                </table>
            </div>
        </div>
    </div>
</main>

</body>
</html>
