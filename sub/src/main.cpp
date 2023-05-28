#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

#include <memory>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

class sub: public rclcpp::Node {
  rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr sub_tpc;

  void sub_callback(std_msgs::msg::UInt8MultiArray::SharedPtr msg) {

    for (auto a : msg->data) RCLCPP_INFO(this->get_logger(), "%d", a);
  }
public:
  sub() : Node("sub"){
    sub_tpc = this->create_subscription<std_msgs::msg::UInt8MultiArray>(
      "chatter", 10, std::bind(&sub::sub_callback, this, std::placeholders::_1));
  }
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<sub>());
  rclcpp::shutdown();
  return 0;
}
