//
// Created by qq795 on 2026/10/26.
//
#include "rclcpp/rclcpp.hpp"
#include"luncher/msg/twist.hpp"

class sub_node:public rclcpp::Node {
    rclcpp::Subscription<luncher::msg::Twist>::SharedPtr subber;
public:
    sub_node():Node("suber") {
        subber=this->create_subscription<luncher::msg::Twist>
        ("p_twist",10,[this](const luncher::msg::Twist &msg){sub_node::subcallback(msg);});
    }
    void subcallback(const luncher::msg::Twist &msg) {
        RCLCPP_INFO(this->get_logger(),"%f,%f",msg.az,msg.lx);

    }
};
int main(int argc,char**argv) {
    rclcpp::init(argc,argv);
    auto node=std::make_shared<sub_node>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}