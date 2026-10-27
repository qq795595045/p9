//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"          // ROS2 C++ 客户端核心头文件
#include"luncher/msg/twist.hpp"       // 自定义消息头文件
#include <chrono>                     // 时间库
using namespace std::chrono_literals; // 启用时间字面量（如 1s）

// 定义管道中继过滤节点类
class pipe_node:public rclcpp::Node {
    // 话题订阅者智能指针
    rclcpp::Subscription<luncher::msg::Twist>::SharedPtr subscription_;
    // 话题发布者智能指针
    rclcpp::Publisher<luncher::msg::Twist>::SharedPtr pubber;
    // 周期定时器智能指针
    rclcpp::TimerBase::SharedPtr timer_base_;
    float  p_lx;                      // 缓存接收到的线速度
    float p_az;                       // 缓存接收到的角速度

public:
    pipe_node():rclcpp::Node("pipe_node") {
        // 创建订阅者：订阅 "twist" 话题，收到消息执行 subcallback
        subscription_=this->create_subscription<luncher::msg::Twist>
        ("twist",10,[this](const luncher::msg::Twist msg){pipe_node::subcallback(msg);});
        // 创建发布者：发布到 "p_twist" 话题
        pubber=this->create_publisher<luncher::msg::Twist>("p_twist",10);
        // 创建定时器：每隔 1s 执行一次 timecallback
        timer_base_=this->create_wall_timer(1s,[this]{timecallback();});
    }
    // 订阅回调函数：更新缓存变量并打印
    void subcallback(const luncher::msg::Twist msg) {
        p_az=msg.az;
        p_lx=msg.lx;
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);
    }
    // 定时器回调函数：进行限幅处理并发布
    void timecallback() {
        auto msg=luncher::msg::Twist();

        // 对角速度 p_az 进行限幅处理
        if (p_az>-1.0&&p_az<1.0)msg.az=p_az;else {
            if (p_az>=1.0)msg.az=1.0;
            if (p_az<=-1.0)msg.az=-1.0;

        }
        // 对线速度 p_lx 进行限幅处理
        if (p_lx>-0.5&&p_lx<0.5)msg.lx=p_lx;else {
            if (p_lx>=1.0)msg.lx=1.0;
            if (p_lx<=-1.0)msg.lx=-1.0;
        }
        // 发布限幅后的消息
        pubber->publish(msg);

    }
};
int main(int argc,char**argv) {
    // 初始化 ROS2 客户端
    rclcpp::init(argc,argv);
    // 创建节点对象
    auto node=std::make_shared<pipe_node>();
    // 进入回旋事件循环
    rclcpp::spin(node);
    // 释放资源关闭节点
    rclcpp::shutdown();
}
