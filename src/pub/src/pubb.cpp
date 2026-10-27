//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"
#include "luncher/msg/twist.hpp"
#include <chrono>
#include <random>
using namespace std::chrono_literals;
class pupe_node:public rclcpp::Node {
    rclcpp::Publisher<luncher::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer;


public:
    pupe_node():Node("pipe") {
       publisher_= this->create_publisher<luncher::msg::Twist>("twist",10);
       timer=  this->create_wall_timer(1000ms,[this]{pupe_node::timecallback();});
    }
    void timecallback() {
        auto msg=luncher::msg::Twist();
        std::default_random_engine engine_{std::random_device{}()};
        std::uniform_real_distribution<float> dist_{-2.0f, 2.0f};
         msg.az = dist_(engine_);
        msg.lx = dist_(engine_);
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);


    }
};
int main(int argc,char**argv) {
    rclcpp::init(argc,argv);
    auto node=std::make_shared<pupe_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}