# ROS 2 Pipeline Project (p9)

本项目基于 ROS 2 Humble 构建，实现了包含自定义接口、周期发布、中继安全限幅及接收订阅的完整数据通信流水线（Pipeline）。

---

## 1. 项目架构与节点职责

- **`luncher`（自定义接口包）**：定义了包含线速度 `lx` 与角速度 `az` 的自定义消息接口 `luncher/msg/Twist`。
- **`pub`（发布节点）**：周期性生成随机运动数据，发布到 `/twist` 话题。
- **`pipe`（管道过滤节点）**：订阅 `/twist` 话题，对运动数据进行安全限幅过滤，并将处理后的结果转发至 `/p_twist` 话题。
- **`sub`（订阅节点）**：订阅 `/p_twist` 话题，实时接收并打印处理后的运动指令。

---

## 2. 核心 API 知识点与《ROS2 理论与实践》教材章节对应

本项目所使用的核心 ROS 2 API 及其在《ROS2 理论与实践》教程中的对应章节如下：

| API / 宏 / 语法 | 功能说明 | 《ROS2 理论与实践》对应章节 | 官方文档参考链接 |
| :--- | :--- | :--- | :--- |
| `rclcpp::init()`<br>`rclcpp::shutdown()` | ROS 2 上下文生命周期初始化与资源安全释放 | **第2章 资料：API文档 ➔ 1.流程相关API (1.1 / 1.4)** | [rclcpp: init / shutdown](https://docs.ros.org/en/humble/p/rclcpp/generated/function_namespacerclcpp_1a2260f8b2d906e57929d5ec4294a28bb.html) |
| `rclcpp::Node` | 节点基类，管理节点名称、生命周期与通信实体 | **第2章 资料：API文档 ➔ 2.节点相关API (1.Node构造函数)** | [rclcpp::Node Class](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_publisher()` | 创建话题发布者（Publisher）对象 | **第2章 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++)**<br>**第2章 资料：API文档 ➔ 2.节点相关API (3.话题通信)** | [create_publisher API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_subscription()` | 创建话题订阅者（Subscription）并绑定回调函数 | **第2章 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++)**<br>**第2章 资料：API文档 ➔ 2.节点相关API (3.话题通信)** | [create_subscription API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_wall_timer()` | 创建基于系统时间的周期定时器（Wall Timer） | **第2章 2.2 话题通信 ➔ 2.2.2 话题通信之原生消息(C++)**<br>**第2章 资料：API文档 ➔ 2.节点相关API (4.定时器)** | [create_wall_timer API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `rclcpp::spin()` | 阻塞主线程并运行单线程执行器处理回调队列 | **第2章 资料：API文档 ➔ 1.流程相关API (1.3 回旋函数)** | [rclcpp::spin API](https://docs.ros.org/en/humble/p/rclcpp/generated/function_namespacerclcpp_1adbe82762dd93028da35338c884004297.html) |
| `RCLCPP_INFO()` | 节点格式化日志输出宏 | **第1章 1.3 快速体验 ➔ 1.3.2 HelloWorld(C++)实现** | [Logging Macros](https://docs.ros.org/en/humble/p/rclcpp/generated/define_logging_8hpp_1ab577c29ae7067d51eeae24619d80d220.html) |
| `rosidl_generate_interfaces()` | CMake 宏：编译生成自定义 msg 接口代码 | **第2章 2.2 话题通信 ➔ 2.2.4 话题通信自定义接口消息**<br>**第2章 2.2 话题通信 ➔ 2.2.5 话题通信之自定义消息(C++)** | [ROS 2 Interfaces](https://docs.ros.org/en/humble/Concepts/Basic/About-Interfaces.html) |

---

## 3. 构建与运行指南

### 编译工作空间
```bash
colcon build
source install/setup.bash