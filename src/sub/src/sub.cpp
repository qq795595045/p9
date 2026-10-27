//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"     // ROS2 C++ 客户端核心头文件
#include"luncher/msg/twist.hpp"  // 自定义 Twist 消息头文件

// 定义订阅接收节点类
class sub_node:public rclcpp::Node {
    // 话题订阅者智能指针
    rclcpp::Subscription<luncher::msg::Twist>::SharedPtr subber;
public:
    sub_node():Node("suber") {
        // 创建订阅者：订阅 "p_twist" 话题，收到消息调用 subcallback 回调
        subber=this->create_subscription<luncher::msg::Twist>
        ("p_twist",10,[this](const luncher::msg::Twist &msg){sub_node::subcallback(msg);});
    }
    // 订阅回调函数：打印接收到的 Twist 消息
    void subcallback(const luncher::msg::Twist &msg) {
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);

    }
};
int main(int argc,char**argv) {
    // 初始化 ROS2 客户端
    rclcpp::init(argc,argv);
    // 创建节点对象
    auto node=std::make_shared<sub_node>();
    // 进入回旋事件循环
    rclcpp::spin(node);
    // 释放资源关闭节点
    rclcpp::shutdown();
}
