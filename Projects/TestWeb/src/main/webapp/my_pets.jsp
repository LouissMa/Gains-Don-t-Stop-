<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<!DOCTYPE html>
<html>
<head>
    <title>我的宠物 - 宠物商城</title>
    <link rel="stylesheet" href="${pageContext.request.contextPath}/css/style.css">
    <link rel="icon" href="${pageContext.request.contextPath}/images/favicon.ico" type="image/x-icon">
</head>
<body>

<jsp:include page="header.jsp"/>

<div class="container">
    <div style="display: flex; justify-content: space-between; align-items: center; gap: 20px; margin: 10px 0 20px;">
        <h2 style="margin: 0; color: #555;">我的宠物</h2>
        <a href="home" class="btn btn-primary" style="padding: 8px 16px; border-radius: 20px;">返回首页</a>
    </div>

    <c:if test="${param.error == 'invalid'}">
        <div style="color: #ff4d4f; margin-bottom: 15px; background: #fff1f0; padding: 10px; border-radius: 8px; border: 1px solid #ffccc7;">
            请填写正确的宠物信息（昵称不能为空，类型与品种需选择，年龄需大于 0）。
        </div>
    </c:if>
    <c:if test="${param.error == 'save_failed'}">
        <div style="color: #ff4d4f; margin-bottom: 15px; background: #fff1f0; padding: 10px; border-radius: 8px; border: 1px solid #ffccc7;">
            添加失败：请确认数据库已执行新增字段 SQL，并刷新后重试。
        </div>
    </c:if>

    <div style="display: grid; grid-template-columns: 1fr 360px; gap: 25px; align-items: start;">
        <div>
            <div class="product-grid" style="grid-template-columns: repeat(auto-fill, minmax(220px, 1fr));">
                <c:forEach var="pet" items="${pets}">
                    <div class="product-card">
                        <div class="product-info">
                            <h3 class="product-title" title="${pet.name}">${pet.name}</h3>
                            <div style="display: flex; justify-content: space-between; align-items: center; margin-top: 10px;">
                                <span style="color: #666;">
                                    <c:choose>
                                        <c:when test="${pet.type == 'DOG'}">狗狗</c:when>
                                        <c:when test="${pet.type == 'CAT'}">猫猫</c:when>
                                        <c:when test="${pet.type == 'PIG'}">宠物猪</c:when>
                                        <c:when test="${pet.type == 'TURTLE'}">乌龟</c:when>
                                        <c:when test="${pet.type == 'RABBIT'}">兔兔</c:when>
                                        <c:when test="${pet.type == 'HAMSTER'}">仓鼠</c:when>
                                        <c:when test="${pet.type == 'BIRD'}">鸟类</c:when>
                                        <c:when test="${pet.type == 'FISH'}">鱼类</c:when>
                                        <c:otherwise>${pet.type}</c:otherwise>
                                    </c:choose>
                                    · ${pet.breed}
                                    · ${pet.age} 岁
                                </span>
                                <a href="pet?action=delete&id=${pet.id}" class="btn btn-danger" style="padding: 6px 12px; border-radius: 16px; font-size: 12px;">删除</a>
                            </div>
                        </div>
                    </div>
                </c:forEach>
            </div>

            <c:if test="${empty pets}">
                <div style="text-align: center; padding: 30px; color: #888; background: #fff; border-radius: 12px; box-shadow: var(--shadow);">
                    暂无宠物档案，先添加一只吧～
                </div>
            </c:if>
        </div>

        <div style="background: rgba(255, 255, 255, 0.95); padding: 20px; border-radius: 12px; box-shadow: var(--shadow);">
            <h3 style="margin-top: 0; color: var(--primary-color);">添加新宠物</h3>
            <form action="pet?action=add" method="post">
                <div class="form-group">
                    <label>类型</label>
                    <select id="pet-type" name="type" required style="width: 100%; padding: 12px; border: 1px solid var(--border-color); border-radius: 8px; box-sizing: border-box; font-size: 14px;">
                        <option value="DOG">狗狗</option>
                        <option value="CAT">猫猫</option>
                        <option value="PIG">宠物猪</option>
                        <option value="TURTLE">乌龟</option>
                        <option value="RABBIT">兔兔</option>
                        <option value="HAMSTER">仓鼠</option>
                        <option value="BIRD">鸟类</option>
                        <option value="FISH">鱼类</option>
                        <option value="OTHER">其他</option>
                    </select>
                </div>
                <div class="form-group">
                    <label>品种</label>
                    <select id="pet-breed" name="breed" required style="width: 100%; padding: 12px; border: 1px solid var(--border-color); border-radius: 8px; box-sizing: border-box; font-size: 14px;"></select>
                </div>
                <div class="form-group">
                    <label>昵称</label>
                    <input type="text" name="name" required placeholder="请输入宠物昵称">
                </div>
                <div class="form-group">
                    <label>年龄</label>
                    <input type="number" name="age" required min="1" placeholder="例如：3">
                </div>
                <button type="submit" class="btn btn-primary" style="width: 100%;">添加</button>
            </form>
        </div>
    </div>
</div>

<script>
    const breedMap = {
        DOG: ['泰迪', '拉布拉多', '金毛', '柯基', '柴犬', '边境牧羊犬', '哈士奇', '萨摩耶', '比熊', '博美', '德国牧羊犬', '秋田犬'],
        CAT: ['英短', '美短', '布偶', '暹罗', '橘猫', '蓝猫', '波斯', '缅因', '斯芬克斯', '加菲', '孟加拉', '苏格兰折耳'],
        PIG: ['迷你猪', '越南大肚猪', '巴马香猪', '茶杯猪', '德国小香猪', '家猪'],
        TURTLE: ['巴西龟', '草龟', '黄缘闭壳龟', '鳄龟', '剃刀龟', '地图龟', '星龟', '陆龟'],
        RABBIT: ['垂耳兔', '荷兰侏儒兔', '安哥拉兔', '狮子兔', '雷克斯兔', '哈瓦那兔', '喜马拉雅兔'],
        HAMSTER: ['金丝熊', '三线', '一线', '布丁', '银狐', '罗伯罗夫斯基', '坎贝尔'],
        BIRD: ['虎皮鹦鹉', '玄凤鹦鹉', '牡丹鹦鹉', '文鸟', '金丝雀', '八哥', '画眉'],
        FISH: ['金鱼', '孔雀鱼', '斗鱼', '锦鲤', '神仙鱼', '红绿灯鱼', '清道夫'],
        OTHER: ['其他']
    };

    function renderBreeds() {
        const typeSelect = document.getElementById('pet-type');
        const breedSelect = document.getElementById('pet-breed');
        const type = typeSelect.value;
        const breeds = breedMap[type] || ['其他'];
        breedSelect.innerHTML = '';
        for (const b of breeds) {
            const opt = document.createElement('option');
            opt.value = b;
            opt.textContent = b;
            breedSelect.appendChild(opt);
        }
    }

    document.getElementById('pet-type').addEventListener('change', renderBreeds);
    renderBreeds();
</script>

</body>
</html>
