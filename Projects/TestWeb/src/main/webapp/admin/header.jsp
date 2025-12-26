<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="fn" uri="jakarta.tags.functions" %>
<c:set var="adminUri" value="${pageContext.request.requestURI}" />
<div class="offcanvas-lg offcanvas-start text-bg-dark admin-sidebar" tabindex="-1" id="adminSidebar" aria-labelledby="adminSidebarLabel">
    <div class="offcanvas-header border-bottom border-secondary">
        <div class="fw-bold" id="adminSidebarLabel">
            <i class="bi bi-paw-fill me-2"></i>店铺工作台
        </div>
        <button type="button" class="btn-close btn-close-white d-lg-none" data-bs-dismiss="offcanvas" aria-label="Close"></button>
    </div>
    <div class="offcanvas-body p-3">
        <div class="small text-secondary mb-3">店铺导航</div>
        <div class="nav flex-column gap-1">
            <a class="text-white text-decoration-none admin-nav-link ${fn:contains(adminUri, '/admin/dashboard') ? 'active' : ''}" href="${pageContext.request.contextPath}/admin/dashboard">
                <i class="bi bi-house-heart me-2"></i>店铺概览
            </a>
            <a class="text-white text-decoration-none admin-nav-link ${fn:contains(adminUri, '/admin/products') ? 'active' : ''}" href="${pageContext.request.contextPath}/admin/products">
                <i class="bi bi-box-seam me-2"></i>商品与库存
            </a>
            <a class="text-white text-decoration-none admin-nav-link ${fn:contains(adminUri, '/admin/orders') ? 'active' : ''}" href="${pageContext.request.contextPath}/admin/orders">
                <i class="bi bi-truck me-2"></i>订单处理
            </a>
            <a class="text-white text-decoration-none admin-nav-link ${fn:contains(adminUri, '/admin/reviews') ? 'active' : ''}" href="${pageContext.request.contextPath}/admin/reviews">
                <i class="bi bi-chat-square-heart me-2"></i>口碑评价
            </a>
            <a class="text-white text-decoration-none admin-nav-link ${fn:contains(adminUri, '/admin/forum') ? 'active' : ''}" href="${pageContext.request.contextPath}/admin/forum">
                <i class="bi bi-megaphone me-2"></i>社区互动
            </a>
        </div>
    </div>
</div>

<nav class="admin-topbar navbar navbar-light border-bottom">
    <div class="container-fluid">
        <button class="btn btn-outline-secondary d-lg-none" type="button" data-bs-toggle="offcanvas" data-bs-target="#adminSidebar" aria-controls="adminSidebar">
            <i class="bi bi-list"></i>
        </button>

        <div class="d-none d-lg-flex align-items-center gap-2">
            <div class="admin-topbar-brand">
                <span class="admin-topbar-brand-dot"></span>
                <span class="fw-semibold">宠物用品店</span>
                <span class="text-muted small ms-1">日常经营助手</span>
            </div>
        </div>

        <div class="ms-auto d-flex align-items-center gap-2">
            <span class="text-muted small">店主</span>
            <span class="fw-semibold">${sessionScope.user.username}</span>
            <a class="btn btn-sm btn-outline-secondary" href="${pageContext.request.contextPath}/home" target="_blank">
                <i class="bi bi-bag-heart me-1"></i>去前台逛逛
            </a>
            <a class="btn btn-sm btn-outline-danger" href="${pageContext.request.contextPath}/logout">
                <i class="bi bi-box-arrow-right me-1"></i>退出
            </a>
        </div>
    </div>
</nav>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"></script>
