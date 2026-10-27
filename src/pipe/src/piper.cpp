//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"
#include"luncher/msg/twist.hpp"
#include <chrono>
using namespace std::chrono_literals;
class pipe_node:public rclcpp::Node {
    rclcpp::Subscription<luncher::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<luncher::msg::Twist>::SharedPtr pubber;
    rclcpp::TimerBase::SharedPtr timer_base_;
    float  p_lx;
    float p_az;

public:
    pipe_node():rclcpp::Node("pipe_node") {
        subscription_=this->create_subscription<luncher::msg::Twist>
        ("twist",10,[this](const luncher::msg::Twist msg){pipe_node::subcallback(msg);});
        pubber=this->create_publisher<luncher::msg::Twist>("p_twist",10);
        timer_base_=this->create_wall_timer(1s,[this]{timecallback();});
    }
    void subcallback(const luncher::msg::Twist msg) {
        p_az=msg.az;
        p_lx=msg.lx;
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);
    }
    void timecallback() {
        auto msg=luncher::msg::Twist();

        if (p_az>-1.0&&p_az<1.0)msg.az=p_az;else {
            if (p_az>=1.0)msg.az=1.0;
            if (p_az<=-1.0)msg.az=-1.0;

        }
        if (p_lx>-0.5&&p_lx<0.5)msg.lx=p_lx;else {
            if (p_lx>=1.0)msg.lx=1.0;
            if (p_lx<=-1.0)msg.lx=-1.0;
        }
        pubber->publish(msg);

    }
};
int main(int argc,char**argv) {
    rclcpp::init(argc,argv);
    auto node=std::make_shared<pipe_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}