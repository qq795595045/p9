//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"          // ROS2 C++ 客户端核心头文件
#include "luncher/msg/twist.hpp"      // 自定义 Twist 消息头文件
#include <chrono>                     // 时间库
#include <random>                     // 随机数库
using namespace std::chrono_literals; // 启用时间字面量（如 1000ms）

// 定义发布节点类，继承自 rclcpp::Node
class pupe_node:public rclcpp::Node {
    // 话题发布者智能指针
    rclcpp::Publisher<luncher::msg::Twist>::SharedPtr publisher_;
    // 周期定时器智能指针
    rclcpp::TimerBase::SharedPtr timer;


public:
    pupe_node():Node("pipe") {
       // 创建发布者，发布到 "twist" 话题，队列长度为 10
       publisher_= this->create_publisher<luncher::msg::Twist>("twist",10);
       // 创建定时器，每 1000ms 执行一次 timecallback 回调
       timer=  this->create_wall_timer(1000ms,[this]{pupe_node::timecallback();});
    }
    // 定时器回调函数：生成随机数并发布
    void timecallback() {
        auto msg=luncher::msg::Twist();
        // 随机数生成引擎与分布器（范围 -2.0 到 2.0）
        std::default_random_engine engine_{std::random_device{}()};
        std::uniform_real_distribution<float> dist_{-2.0f, 2.0f};
        msg.az = dist_(engine_); // 赋值角速度
        msg.lx = dist_(engine_); // 赋值线速度
        // 发布消息
        publisher_->publish(msg);
        // 打印日志
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);


    }
};
int main(int argc,char**argv) {
    // 初始化 ROS2 客户端
    rclcpp::init(argc,argv);
    // 创建节点对象
    auto node=std::make_shared<pupe_node>();
    // 进入回旋事件循环
    rclcpp::spin(node);
    // 释放资源关闭节点
    rclcpp::shutdown();
}
