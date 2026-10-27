# ROS 2 Pipeline Project (p9)

本项目基于 ROS 2 Humble 构建，实现了包含自定义接口、周期发布、中继安全限幅及接收订阅的完整数据通信流水线（Pipeline）。

---

## 1. 项目架构与节点职责

- **`luncher`（自定义接口包）**：定义了包含线速度 `lx` 与角速度 `az` 的自定义消息接口 `luncher/msg/Twist`。
- **`pub`（发布节点）**：周期性生成随机运动数据，发布到 `/twist` 话题。
- **`pipe`（管道过滤节点）**：订阅 `/twist` 话题，对运动数据进行安全限幅过滤，并将处理后的结果转发至 `/p_twist` 话题。
- **`sub`（订阅节点）**：订阅 `/p_twist` 话题，实时接收并打印处理后的运动指令。

---

## 2. 核心 API 知识点与 ROS 2 在线讲义章节对应

本项目所使用的核心 ROS 2 API 均与你的在线讲义教程 **[ROS2 理论与实践](https://qq795595045.github.io/ros2/)** 保持严格对应。点击下方链接可**直接在浏览器中打开对应章节的在线电子书**：

| API / 宏 / 语法 | 功能说明 | 对应讲义章节 | 在线讲义直达页面 |
| :--- | :--- | :--- | :--- |
| `rosidl_generate_interfaces()` | CMake 宏：编译生成自定义 msg 接口代码 | 2.2 话题通信 ➔ 2.2.4 话题通信自定义接口消息 | [📖 2.2.4 话题通信自定义接口消息](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-jie-kou-xiao-xi.html) |
| `Node::create_publisher()` | 创建话题发布者（Publisher）对象 | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| `Node::create_subscription()` | 创建话题订阅者（Subscription）并绑定回调函数 | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| `Node::create_wall_timer()` | 创建基于系统时间的周期定时器（Wall Timer） | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| `rclcpp::init()`<br>`rclcpp::shutdown()` | ROS 2 上下文生命周期初始化与资源安全释放 | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| `rclcpp::spin()` | 阻塞主线程并运行单线程执行器处理回调队列 | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| `rclcpp::Node` | 节点基类，管理节点名称、生命周期与通信实体 | 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++) | [📖 2.2.2 话题通信之原生消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/222-hua-ti-tong-xin-c-shi-73b028-yuan-sheng-xiao-606f29.html) |
| 自定义 Twist 消息 C++ 调用 | 在 C++ 节点中发布/接收自定义接口消息 | 2.2 话题通信 ➔ 2.2.5 话题通信之自定义消息(C++) | [📖 2.2.5 话题通信自定义消息(C++)](https://qq795595045.github.io/ros2/_book/di-2-zhang-ros2-tong-xin-ji-zhi-he-xin/22-hua-ti-tong-xin/223-hua-ti-tong-xin-c-shi-xian.html) |
| `RCLCPP_INFO()` | 节点格式化日志输出宏 | 1.3 快速体验 ➔ 1.3.1 HelloWorld(C++)实现 | [📖 1.3.1 HelloWorld(C++)实现](https://qq795595045.github.io/ros2/_book/chapter1/13-ros2kuai-su-ti-yan/131-helloworldcshi-73b029.html) |

---

## 3. 构建与运行指南

### 编译工作空间
```bash
colcon build
source install/setup.bash
```

### 依次启动节点（需分别打开 3 个终端）
```bash
# 终端 1：启动管道限幅节点
ros2 run pipe pipe

# 终端 2：启动订阅接收节点
ros2 run sub sub

# 终端 3：启动发布节点
ros2 run pub pub
```
