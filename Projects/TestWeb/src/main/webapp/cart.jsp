<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>购物车 - 宠物商城</title>
    <style>
        body { font-family: "Microsoft YaHei", Arial, sans-serif; margin: 0; }
        .container { padding: 20px; max-width: 800px; margin: 0 auto; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th, td { padding: 12px; border-bottom: 1px solid #ddd; text-align: left; }
        th { background-color: #f8f9fa; }
        .total { font-size: 1.2em; font-weight: bold; text-align: right; margin-top: 20px; }
        .actions { text-align: right; margin-top: 20px; }
        .btn { padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer; text-decoration: none; color: white; display: inline-block; }
        .btn-primary { background-color: #007bff; }
        .btn-success { background-color: #28a745; }
        .btn-danger { background-color: #dc3545; padding: 5px 10px; font-size: 0.9em; }
        .btn-warning { background-color: #ffc107; color: black; padding: 5px 10px; font-size: 0.9em; }
        input[type="number"] { width: 50px; padding: 5px; }
    </style>
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="container">
    <h2>购物车</h2>
    
    <c:choose>
        <c:when test="${empty sessionScope.cart or empty sessionScope.cart.items}">
            <p>您的购物车是空的。</p>
            <a href="products" class="btn btn-primary">去购物</a>
        </c:when>
        <c:otherwise>
            <table>
                <thead>
                    <tr>
                        <th>商品</th>
                        <th>单价</th>
                        <th>数量</th>
                        <th>小计</th>
                        <th>操作</th>
                    </tr>
                </thead>
                <tbody>
                    <c:forEach var="item" items="${sessionScope.cart.items}">
                        <tr>
                            <td>
                                <a href="product?id=${item.product.id}">${item.product.name}</a>
                            </td>
                            <td>¥${item.product.price}</td>
                            <td>
                                <form action="update-cart" method="post" style="display: inline;">
                                    <input type="hidden" name="action" value="update">
                                    <input type="hidden" name="productId" value="${item.product.id}">
                                    <input type="number" name="quantity" value="${item.quantity}" min="1" max="${item.product.stock}">
                                    <button type="submit" class="btn btn-warning">更新</button>
                                </form>
                            </td>
                            <td>¥${item.totalPrice}</td>
                            <td>
                                <form action="update-cart" method="post" style="display: inline;">
                                    <input type="hidden" name="action" value="remove">
                                    <input type="hidden" name="productId" value="${item.product.id}">
                                    <button type="submit" class="btn btn-danger">移除</button>
                                </form>
                            </td>
                        </tr>
                    </c:forEach>
                </tbody>
            </table>
            
            <div class="total">
                总计金额: ¥${sessionScope.cart.totalAmount}
            </div>
            
            <div class="actions">
                <a href="products" class="btn btn-primary">继续购物</a>
                <c:choose>
                    <c:when test="${not empty sessionScope.user}">
                        <form action="place-order" method="post" style="display: inline;">
                            <button type="submit" class="btn btn-success">去结算</button>
                        </form>
                    </c:when>
                    <c:otherwise>
                        <a href="login" class="btn btn-success">登录后结算</a>
                    </c:otherwise>
                </c:choose>
            </div>
        </c:otherwise>
    </c:choose>
</div>

</body>
</html>
