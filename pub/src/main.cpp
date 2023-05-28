#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <chrono>

using namespace std::chrono_literals;

class pub : public rclcpp::Node{
  rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr pub_tpc;
  rclcpp::TimerBase::SharedPtr tim;

  void tim_callback() {
    std_msgs::msg::UInt8MultiArray msg;
    msg.data.resize(8);

    for (int i = 0; i < 8; i++) { 
      msg.data[i] = i;
      RCLCPP_INFO(this->get_logger(), "%d", i);
    }

    pub_tpc->publish(msg);
  }

public:
  pub(): Node("pub") {
    pub_tpc = this->create_publisher<std_msgs::msg::UInt8MultiArray>("chatter", 10);
    tim = this->create_wall_timer(1000ms, std::bind(&pub::tim_callback, this));
  }
  
};

int main(int argc, char ** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<pub>());
  rclcpp::shutdown();
  return 0;
}
