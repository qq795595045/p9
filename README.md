# ROS 2 Pipeline Project (p9)

本项目基于 ROS 2 Humble，构建了一个包含消息发布、中继过滤和接收订阅的完整通信管道。

## 项目架构
- `luncher`: 自定义接口包，定义了包含 `lx` 和 `az` 的 `Twist` 消息。
- `pub`: 发布节点，周期性向 `/twist` 话题发布随机运动数据。
- `pipe`: 中继处理节点，订阅 `/twist` 话题，对线速度和角速度进行安全限幅，并将处理后的数据发布到 `/p_twist`。
- `sub`: 订阅节点，监听 `/p_twist` 话题并打印输出。

---

## 核心 API 与官方文档链接

| API / 宏 / 接口 | 功能说明 | 官方文档参考链接 |
| :--- | :--- | :--- |
| `rclcpp::init()` / `rclcpp::shutdown()` | ROS 2 上下文生命周期的初始化与释放 | [rclcpp: init / shutdown](https://docs.ros.org/en/humble/p/rclcpp/generated/function_namespacerclcpp_1a2260f8b2d906e57929d5ec4294a28bb.html) |
| `rclcpp::Node` | ROS 2 节点基类，负责管理通信实体 | [rclcpp::Node Class](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_publisher()` | 创建话题发布者 (Publisher) | [create_publisher API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_subscription()` | 创建话题订阅者 (Subscription) 并绑定回调 | [create_subscription API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `Node::create_wall_timer()` | 创建基于系统时间的周期定时器 (Wall Timer) | [create_wall_timer API](https://docs.ros.org/en/humble/p/rclcpp/generated/classrclcpp_1_1Node.html) |
| `rclcpp::spin()` | 阻塞并驱动节点的事件循环处理回调 | [rclcpp::spin API](https://docs.ros.org/en/humble/p/rclcpp/generated/function_namespacerclcpp_1adbe82762dd93028da35338c884004297.html) |
| `RCLCPP_INFO()` | 节点标准日志格式化输出宏 | [Logging Macros](https://docs.ros.org/en/humble/p/rclcpp/generated/define_logging_8hpp_1ab577c29ae7067d51eeae24619d80d220.html) |
| `rosidl_generate_interfaces()` | CMake 宏：编译生成自定义 msg/srv/action 代码 | [About ROS 2 Interfaces](https://docs.ros.org/en/humble/Concepts/Basic/About-Interfaces.html) |

## 构建与运行
```bash
colcon build
source install/setup.bash