<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>店铺工作台 - 宠物用品商城</title>
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
            <h2 class="m-0 fw-bold">店铺工作台</h2>
            <div class="text-muted small">今日经营概览</div>
        </div>

        <div class="row g-3 mb-4">
            <div class="col-12 col-md-6 col-xl-3">
                <div class="card admin-metric-card text-white bg-primary">
                    <div class="card-body d-flex align-items-center justify-content-between">
                        <div>
                            <div class="admin-metric-label">今日销售额</div>
                            <div class="admin-metric-value">¥${todaySales}</div>
                        </div>
                        <div class="admin-metric-icon"><i class="bi bi-cash-stack"></i></div>
                    </div>
                </div>
            </div>

            <div class="col-12 col-md-6 col-xl-3">
                <div class="card admin-metric-card text-white bg-danger">
                    <div class="card-body d-flex align-items-center justify-content-between">
                        <div>
                            <div class="admin-metric-label">待发货订单</div>
                            <div class="admin-metric-value">
                                ${pendingOrders}
                                <c:if test="${pendingOrders > 0}">
                                    <span class="badge bg-light text-danger ms-2">赶紧发货</span>
                                </c:if>
                            </div>
                        </div>
                        <div class="admin-metric-icon"><i class="bi bi-truck"></i></div>
                    </div>
                </div>
            </div>

            <div class="col-12 col-md-6 col-xl-3">
                <div class="card admin-metric-card text-white bg-success">
                    <div class="card-body d-flex align-items-center justify-content-between">
                        <div>
                            <div class="admin-metric-label">本月新增顾客</div>
                            <div class="admin-metric-value">${newUsersThisMonth}</div>
                        </div>
                        <div class="admin-metric-icon"><i class="bi bi-people"></i></div>
                    </div>
                </div>
            </div>

            <div class="col-12 col-md-6 col-xl-3">
                <div class="card admin-metric-card text-white bg-warning">
                    <div class="card-body d-flex align-items-center justify-content-between">
                        <div>
                            <div class="admin-metric-label">库存预警商品数</div>
                            <div class="admin-metric-value">${lowStockCount}</div>
                        </div>
                        <div class="admin-metric-icon"><i class="bi bi-exclamation-triangle"></i></div>
                    </div>
                </div>
            </div>
        </div>

        <div class="row g-3">
            <div class="col-12 col-xl-5">
                <div class="card border-0 shadow-sm">
                    <div class="card-body">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <div class="fw-bold">猫派 vs 狗派 用户比例</div>
                            <div class="text-muted small">来源：宠物档案</div>
                        </div>
                        <div id="petPie" style="height: 340px;"></div>
                    </div>
                </div>
            </div>
            <div class="col-12 col-xl-7">
                <div class="card border-0 shadow-sm">
                    <div class="card-body">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <div class="fw-bold">近 7 天订单量趋势</div>
                            <div class="text-muted small">来源：订单数据</div>
                        </div>
                        <div id="orderLine" style="height: 340px;"></div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</main>

<script src="https://cdn.jsdelivr.net/npm/echarts@5/dist/echarts.min.js"></script>
<script>
    (function () {
        const pieEl = document.getElementById('petPie');
        const lineEl = document.getElementById('orderLine');
        if (!pieEl || !lineEl || !window.echarts) return;

        let catCount = Number('${catCount}');
        let dogCount = Number('${dogCount}');
        if (!Number.isFinite(catCount) || !Number.isFinite(dogCount) || (catCount + dogCount) <= 0) {
            catCount = 48.5;
            dogCount = 52.5;
        }
        const trendLabels = ${orderTrendLabelsJson};
        const trendValues = ${orderTrendValuesJson};

        const pie = echarts.init(pieEl);
        pie.setOption({
            tooltip: {
                trigger: 'item',
                formatter: function (p) {
                    return p.marker + p.name + '：' + p.percent.toFixed(1) + '%';
                }
            },
            legend: { bottom: 0 },
            series: [{
                type: 'pie',
                radius: ['45%', '70%'],
                avoidLabelOverlap: true,
                label: {
                    formatter: function (p) {
                        return p.name + ': ' + p.percent.toFixed(1) + '%';
                    }
                },
                data: [
                    { value: catCount, name: '猫派' },
                    { value: dogCount, name: '狗派' }
                ]
            }]
        });

        const line = echarts.init(lineEl);
        line.setOption({
            tooltip: { trigger: 'axis' },
            grid: { left: 40, right: 20, top: 20, bottom: 40 },
            xAxis: { type: 'category', data: trendLabels },
            yAxis: { type: 'value', minInterval: 1 },
            series: [{
                type: 'line',
                data: trendValues,
                smooth: true,
                symbolSize: 8,
                areaStyle: { opacity: 0.12 }
            }]
        });

        window.addEventListener('resize', function () {
            pie.resize();
            line.resize();
        });
    })();
</script>
</body>
</html>
