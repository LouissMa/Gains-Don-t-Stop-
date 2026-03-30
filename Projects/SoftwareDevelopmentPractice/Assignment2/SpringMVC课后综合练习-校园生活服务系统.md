# Spring MVC 课后综合练习：「校园生活服务系统」

> 适用章节：基于注解的控制器、表单标签库与数据绑定、JSON数据交互
> 适用对象：软件开发与实践课程学生
> 预计完成时间：2-3小时

---

## 📖 项目背景

临近期末，大学生小城决定用所学知识，开发一个集「二手交易」「学生信息管理」「校园活动查询」于一体的校园生活服务系统。这个系统将作为他的毕业设计项目。

---

## 🏗️ 系统功能模块

```
┌─────────────────────────────────────────────────────────┐
│                   校园生活服务系统                         │
├─────────────────┬─────────────────┬───────────────────┤
│   二手交易模块     │   学生中心模块     │   活动API模块      │
│  (基于注解的控制器) │ (表单标签库+数据绑定) │  (JSON数据交互)   │
└─────────────────┴─────────────────┴───────────────────┘
```

---

## 📝 练习一：二手交易模块（基于注解的控制器）

### 场景描述
在宿舍楼群里，小城看到很多同学在转让闲置物品，于是决定开发这个模块。

### 知识点
- `@Controller` 注解
- `@RequestMapping` 及其衍生注解（`@GetMapping`, `@PostMapping` 等）
- `@PathVariable` 接收URL路径变量
- `@RequestParam` 接收请求参数

### 题目要求

**1. 创建商品实体类 `Item.java`**

```java
public class Item {
    private Integer id;           // 商品ID（自增）
    private String name;          // 商品名称
    private String description;   // 商品描述
    private Double price;         // 价格（元）
    private String category;      // 分类：电子产品/书籍/生活用品/服装/其他
    private String contact;       // 联系方式（微信/手机）
    private String sellerName;    // 卖家昵称
    private Date publishTime;     // 发布时间
    private String status;        // 状态：出售中/已售出
    // 省略getter/setter/toString
}
```

**2. 创建控制器 `ItemController.java`**

实现以下功能：

| 功能 | 请求方式 | 请求路径 | 说明 |
|------|---------|---------|------|
| 首页列表 | GET | `/item/list` | 展示所有在售商品 |
| 商品详情 | GET | `/item/detail/{id}` | 查看某个商品的详细信息 |
| 发布商品 | GET | `/item/toAdd` | 跳转发布页面 |
| 发布商品 | POST | `/item/add` | 处理发布表单，保存商品 |
| 我的商品 | GET | `/item/my` | 查看自己发布的所有商品 |
| 设为已售 | POST | `/item/sold/{id}` | 将商品状态改为已售出 |
| 删除商品 | POST | `/item/delete/{id}` | 删除自己发布的商品 |
| 按分类查询 | GET | `/item/category/{category}` | 按分类筛选商品 |

**3. 使用到的注解示例**

```java
@Controller
@RequestMapping("/item")
public class ItemController {

    @GetMapping("/list")
    public String list(Model model) {
        List<Item> items = itemService.findAll();
        model.addAttribute("items", items);
        return "item/list";
    }

    @GetMapping("/detail/{id}")
    public String detail(@PathVariable Integer id, Model model) {
        Item item = itemService.findById(id);
        model.addAttribute("item", item);
        return "item/detail";
    }

    @GetMapping("/toAdd")
    public String toAdd(Model model) {
        model.addAttribute("item", new Item());
        return "item/add";
    }

    @PostMapping("/add")
    public String add(@ModelAttribute Item item, 
                      @RequestParam String sellerName,
                      HttpSession session) {
        item.setSellerName(sellerName); // 模拟从session获取登录用户
        item.setPublishTime(new Date());
        item.setStatus("出售中");
        itemService.save(item);
        return "redirect:/item/my";
    }

    @GetMapping("/category/{category}")
    public String category(@PathVariable String category, Model model) {
        List<Item> items = itemService.findByCategory(category);
        model.addAttribute("items", items);
        model.addAttribute("category", category);
        return "item/list";
    }
}
```

### 附加挑战
> 1. 添加分页功能：使用 `@RequestParam(defaultValue = "1") Integer page` 和 `@RequestParam(defaultValue = "10") Integer size`
> 2. 添加排序功能：使用 `@RequestParam(required = false) String sortBy` 参数

---

## 📝 练习二：学生中心模块（表单标签库与数据绑定）

### 场景描述
为了更好地服务同学，系统需要学生注册登录功能，管理个人信息，并支持选课。

### 知识点
- Spring表单标签库：`<form:form>`, `<form:input>`, `<form:password>`, `<form:radiobuttons>`, `<form:select>`, `<form:checkboxes>`, `<form:textarea>`
- `@ModelAttribute` 注解（绑定表单数据到POJO）
- 模型数据的传递与展示

### 题目要求

**1. 创建学生实体类 `Student.java`**

```java
public class Student {
    private String studentId;      // 学号（登录账号）
    private String password;       // 密码
    private String name;           // 姓名
    private String nickname;       // 昵称
    private String gender;         // 性别：男/女
    private Integer age;           // 年龄
    private String major;          // 专业
    private String grade;          // 年级：大一/大二/大三/大四
    private List<String> hobbies; // 爱好：游戏/运动/音乐/追剧/学习/其他
    private String introduction;   // 个人简介
    private String avatarUrl;       // 头像URL
    private Date registerTime;     // 注册时间
    // 省略getter/setter
}
```

**2. 创建课程实体类 `Course.java`**

```java
public class Course {
    private String courseId;       // 课程ID
    private String courseName;     // 课程名称
    private String teacher;        // 教师
    private Integer credits;       // 学分
    private Integer maxStudents;   // 最大选课人数
    private Integer selectedCount; // 已选人数
    private String timeSlot;       // 上课时间
    private String location;       // 上课地点
    // 省略getter/setter
}
```

**3. 创建控制器 `StudentController.java`**

实现以下功能：

| 功能 | 请求方式 | 请求路径 | 说明 |
|------|---------|---------|------|
| 注册页面 | GET | `/student/toRegister` | 跳转注册表单页 |
| 注册处理 | POST | `/student/register` | 处理注册，绑定表单数据 |
| 个人信息 | GET | `/student/profile/{studentId}` | 查看个人信息 |
| 编辑资料 | GET | `/student/edit/{studentId}` | 跳转编辑页面 |
| 编辑处理 | POST | `/student/update` | 更新个人信息 |
| 选课页面 | GET | `/student/courses` | 查看可选课程 |
| 选课处理 | POST | `/student/selectCourse` | 提交选课 |
| 我的课表 | GET | `/student/myCourses` | 查看已选课程 |

**4. 创建注册表单页面 `register.jsp`**

使用Spring表单标签库实现注册表单：

```jsp
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<!DOCTYPE html>
<html>
<head>
    <title>学生注册</title>
</head>
<body>
    <h2>欢迎注册校园生活服务系统</h2>
    
    <form:form modelAttribute="student" method="post" action="/student/register">
        <table>
            <tr>
                <td>学号：</td>
                <td><form:input path="studentId"/></td>
                <td><form:errors path="studentId" cssStyle="color:red"/></td>
            </tr>
            <tr>
                <td>密码：</td>
                <td><form:password path="password"/></td>
            </tr>
            <tr>
                <td>姓名：</td>
                <td><form:input path="name"/></td>
            </tr>
            <tr>
                <td>昵称：</td>
                <td><form:input path="nickname"/></td>
            </tr>
            <tr>
                <td>性别：</td>
                <td>
                    <form:radiobuttons path="gender" items="${genderItems}"/>
                </td>
            </tr>
            <tr>
                <td>年龄：</td>
                <td><form:input path="age"/></td>
            </tr>
            <tr>
                <td>专业：</td>
                <td>
                    <form:select path="major" items="${majorItems}"/>
                </td>
            </tr>
            <tr>
                <td>年级：</td>
                <td>
                    <form:select path="grade" items="${gradeItems}"/>
                </td>
            </tr>
            <tr>
                <td>爱好：</td>
                <td>
                    <form:checkboxes path="hobbies" items="${hobbyItems}"/>
                </td>
            </tr>
            <tr>
                <td>个人简介：</td>
                <td><form:textarea path="introduction" rows="3" cols="20"/></td>
            </tr>
            <tr>
                <td colspan="2">
                    <input type="submit" value="注册"/>
                </td>
            </tr>
        </table>
    </form:form>
</body>
</html>
```

**5. 创建课程选择表单页面 `courseSelect.jsp`**

```jsp
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<h2>选择你要选修的课程</h2>

<form:form modelAttribute="selectedCourses" method="post" action="/student/selectCourse">
    <table border="1">
        <tr>
            <th>选择</th>
            <th>课程ID</th>
            <th>课程名称</th>
            <th>教师</th>
            <th>学分</th>
            <th>已选/上限</th>
            <th>时间</th>
            <th>地点</th>
        </tr>
        <c:forEach items="${courseList}" var="course" varStatus="status">
            <tr>
                <td>
                    <form:checkbox path="courseIds" value="${course.courseId}"/>
                </td>
                <td>${course.courseId}</td>
                <td>${course.courseName}</td>
                <td>${course.teacher}</td>
                <td>${course.credits}</td>
                <td>${course.selectedCount}/${course.maxStudents}</td>
                <td>${course.timeSlot}</td>
                <td>${course.location}</td>
            </tr>
        </c:forEach>
    </table>
    <br>
    <form:label path="studentId">请确认学号：</form:label>
    <form:input path="studentId"/>
    <br><br>
    <input type="submit" value="确认选课"/>
</form:form>
```

**6. 控制器中准备下拉框数据**

```java
@GetMapping("/toRegister")
public String toRegister(Model model) {
    model.addAttribute("student", new Student());
    
    // 准备下拉框选项
    Map<String, String> genderItems = new LinkedHashMap<>();
    genderItems.put("男", "男");
    genderItems.put("女", "女");
    model.addAttribute("genderItems", genderItems);
    
    List<String> majorItems = Arrays.asList("计算机科学与技术", "软件工程", "网络工程", 
                                              "信息安全", "数据科学与大数据技术");
    model.addAttribute("majorItems", majorItems);
    
    Map<String, String> gradeItems = new LinkedHashMap<>();
    gradeItems.put("大一", "大一");
    gradeItems.put("大二", "大二");
    gradeItems.put("大三", "大三");
    gradeItems.put("大四", "大四");
    model.addAttribute("gradeItems", gradeItems);
    
    List<String> hobbyItems = Arrays.asList("游戏", "运动", "音乐", "追剧", "学习", "社交");
    model.addAttribute("hobbyItems", hobbyItems);
    
    return "student/register";
}

@PostMapping("/register")
public String register(@ModelAttribute Student student, Model model) {
    student.setRegisterTime(new Date());
    studentService.register(student);
    model.addAttribute("student", student);
    return "student/profile";
}
```

### 附加挑战
> 1. 在表单中添加数据校验：使用 `@Valid` 注解和 `BindingResult`，实现学号不能为空、密码长度不少于6位、年龄在16-30岁之间等校验
> 2. 在个人资料页面使用 `<form:form modelAttribute="student" method="get">` 展示只读信息

---

## 📝 练习三：活动API模块（JSON数据交互）

### 场景描述
小城想让其他开发者也能接入校园活动数据，于是提供了JSON格式的RESTful API。

### 知识点
- `@RestController` 注解
- `@RequestBody` 注解（接收JSON请求体）
- `@ResponseBody` 注解（返回JSON响应）
- RESTful URL设计

### 题目要求

**1. 创建活动实体类 `Activity.java`**

```java
public class Activity {
    private String activityId;     // 活动ID
    private String title;          // 活动标题
    private String description;    // 活动描述
    private String organizer;      // 主办方
    private String type;           // 活动类型：学术/体育/文艺/公益/娱乐
    private Date startTime;        // 开始时间
    private Date endTime;          // 结束时间
    private String location;       // 活动地点
    private Integer maxParticipants; // 最大参与人数
    private Integer currentParticipants; // 当前报名人数
    private String status;         // 状态：报名中/进行中/已结束
    // 省略getter/setter
}
```

**2. 创建响应结果类 `Result.java`**

统一JSON响应格式：

```java
public class Result<T> {
    private Integer code;          // 状态码：200成功，400失败，500异常
    private String message;        // 提示信息
    private T data;                 // 数据内容
    private Long timestamp;        // 时间戳
    
    // 静态工厂方法
    public static <T> Result<T> success(T data) {
        Result<T> result = new Result<>();
        result.setCode(200);
        result.setMessage("success");
        result.setData(data);
        result.setTimestamp(System.currentTimeMillis());
        return result;
    }
    
    public static <T> Result<T> error(String message) {
        Result<T> result = new Result<>();
        result.setCode(400);
        result.setMessage(message);
        result.setTimestamp(System.currentTimeMillis());
        return result;
    }
    
    // 省略getter/setter
}
```

**3. 创建REST控制器 `ActivityApiController.java`**

实现以下JSON API接口：

| 功能 | 请求方式 | 请求路径 | 说明 |
|------|---------|---------|------|
| 获取所有活动 | GET | `/api/activities` | 返回活动列表JSON |
| 获取活动详情 | GET | `/api/activities/{id}` | 返回单个活动JSON |
| 按类型查询 | GET | `/api/activities?type=体育` | 根据type参数筛选 |
| 搜索活动 | GET | `/api/activities/search?keyword=篮球` | 关键词搜索 |
| 发布新活动 | POST | `/api/activities` | 接收JSON请求体 |
| 更新活动 | PUT | `/api/activities/{id}` | 更新活动信息 |
| 删除活动 | DELETE | `/api/activities/{id}` | 删除活动 |
| 报名参加 | POST | `/api/activities/{id}/join` | 报名参加活动 |

**4. 控制器代码示例**

```java
@RestController
@RequestMapping("/api/activities")
public class ActivityApiController {

    @GetMapping
    public Result<List<Activity>> getAllActivities(
            @RequestParam(required = false) String type,
            @RequestParam(required = false) String keyword) {
        
        List<Activity> activities;
        
        if (keyword != null && !keyword.isEmpty()) {
            // 关键词搜索
            activities = activityService.search(keyword);
        } else if (type != null && !type.isEmpty()) {
            // 按类型筛选
            activities = activityService.findByType(type);
        } else {
            // 获取全部
            activities = activityService.findAll();
        }
        
        return Result.success(activities);
    }

    @GetMapping("/{id}")
    public Result<Activity> getActivityById(@PathVariable String id) {
        Activity activity = activityService.findById(id);
        if (activity != null) {
            return Result.success(activity);
        }
        return Result.error("活动不存在");
    }

    @PostMapping
    public Result<String> createActivity(@RequestBody Activity activity) {
        activity.setStatus("报名中");
        activity.setCurrentParticipants(0);
        activityService.save(activity);
        return Result.success("活动创建成功");
    }

    @PutMapping("/{id}")
    public Result<String> updateActivity(@PathVariable String id, 
                                         @RequestBody Activity activity) {
        Activity existing = activityService.findById(id);
        if (existing == null) {
            return Result.error("活动不存在");
        }
        activity.setActivityId(id);
        activityService.update(activity);
        return Result.success("活动更新成功");
    }

    @DeleteMapping("/{id}")
    public Result<String> deleteActivity(@PathVariable String id) {
        activityService.delete(id);
        return Result.success("活动删除成功");
    }

    @PostMapping("/{id}/join")
    public Result<String> joinActivity(@PathVariable String id,
                                       @RequestBody Map<String, String> request) {
        String studentId = request.get("studentId");
        
        Activity activity = activityService.findById(id);
        if (activity == null) {
            return Result.error("活动不存在");
        }
        
        if ("已结束".equals(activity.getStatus())) {
            return Result.error("活动已结束，无法报名");
        }
        
        if (activity.getCurrentParticipants() >= activity.getMaxParticipants()) {
            return Result.error("活动人数已满");
        }
        
        activityService.addParticipant(id, studentId);
        return Result.success("报名成功！");
    }
}
```

### JSON数据示例

```json
// GET /api/activities 返回
{
    "code": 200,
    "message": "success",
    "timestamp": 1705123456789,
    "data": [
        {
            "activityId": "ACT001",
            "title": "校园篮球赛",
            "description": "一年一度的校园篮球赛，各学院组队参加",
            "organizer": "体育部",
            "type": "体育",
            "startTime": "2024-02-15 14:00:00",
            "endTime": "2024-02-15 18:00:00",
            "location": "体育馆",
            "maxParticipants": 100,
            "currentParticipants": 56,
            "status": "报名中"
        },
        {
            "activityId": "ACT002",
            "title": "AI技术讲座",
            "description": "邀请业界专家讲解ChatGPT与AI未来",
            "organizer": "计算机学院",
            "type": "学术",
            "startTime": "2024-02-20 19:00:00",
            "endTime": "2024-02-20 21:00:00",
            "location": "报告厅A",
            "maxParticipants": 200,
            "currentParticipants": 180,
            "status": "报名中"
        }
    ]
}

// POST /api/activities 请求体
{
    "title": "新生破冰晚会",
    "description": "欢迎大一新生加入校园大家庭",
    "organizer": "学生会",
    "type": "娱乐",
    "startTime": "2024-03-01 19:00:00",
    "endTime": "2024-03-01 21:30:00",
    "location": "大学生活动中心",
    "maxParticipants": 500
}
```

### 附加挑战
> 1. 实现分页API：添加 `page` 和 `size` 参数，返回分页数据
> 2. 实现活动统计API：GET `/api/activities/stats`，返回各类活动的数量统计
> 3. 添加日期范围查询：GET `/api/activities?startDate=2024-02-01&endDate=2024-02-28`

---

## 🎯 综合练习：整合三大模块

### 题目要求

将以上三个模块整合到一个项目中，实现以下功能：

1. **统一入口页面 `index.jsp`**
   - 导航栏：二手交易 | 学生中心 | 活动中心
   - 展示热门活动（调用JSON API获取）

2. **用户Session管理**
   - 登录后在Session中存储用户信息
   - 各模块共享用户登录状态

3. **数据共享**
   - 二手交易的"联系卖家"功能可以查看卖家基本信息（调用学生信息）
   - 活动报名需要验证学号（查询学生信息）

### 整体项目结构

```
src/
├── main/
│   ├── java/
│   │   └── com/
│   │       └── campus/
│   │           ├── controller/
│   │           │   ├── ItemController.java      # 二手交易
│   │           │   ├── StudentController.java   # 学生中心
│   │           │   ├── ActivityController.java  # 活动页面
│   │           │   └── ActivityApiController.java # JSON API
│   │           ├── service/
│   │           │   ├── ItemService.java
│   │           │   ├── StudentService.java
│   │           │   └── ActivityService.java
│   │           ├── dao/
│   │           │   ├── ItemDao.java
│   │           │   ├── StudentDao.java
│   │           │   └── ActivityDao.java
│   │           └── entity/
│   │               ├── Item.java
│   │               ├── Student.java
│   │               ├── Course.java
│   │               ├── Activity.java
│   │               └── Result.java
│   └── resources/
│   │   └── springmvc-config.xml
│   └── webapp/
│       ├── WEB-INF/
│       │   ├── web.xml
│       │   └── views/
│       │       ├── item/
│       │       │   ├── list.jsp
│       │       │   ├── detail.jsp
│       │       │   └── add.jsp
│       │       ├── student/
│       │       │   ├── register.jsp
│       │       │   ├── profile.jsp
│       │       │   ├── edit.jsp
│       │       │   └── courseSelect.jsp
│       │       └── activity/
│       │           └── list.jsp
│       └── index.jsp
```

---
## 提交内容

1. 项目代码（包含文件结构说明）
2. 项目演示图片

所有内容打包为zip文件，命名为：`学号-姓名-作业2.zip`，提交到作业平台。

## 💡 开发提示

1. **使用 `@ModelAttribute` 共享数据**：在控制器中定义一个方法用 `@ModelAttribute` 注解，可以在所有请求前执行，用于准备公共数据

2. **JSON日期处理**：在实体类的Date字段上添加 `@JsonFormat(pattern = "yyyy-MM-dd HH:mm:ss", timezone = "GMT+8")`

3. **CORS跨域**：如果前端是独立项目，需要在控制器上添加 `@CrossOrigin` 注解

4. **静态资源**：在springmvc-config.xml中配置 `<mvc:resources mapping="/static/**" location="/static/"/>`

---

