#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using namespace std::chrono_literals;

class Publisher : public rclcpp::Node
{
public:
    Publisher() : Node("publisher"), time_{0}
    {
        // Assign publisher object to pub_ shared pointer
        pub_ = this->create_publisher<std_msgs::msg::String>("topic", 50);
        timer_ = this->create_wall_timer(1s, std::bind(&Publisher::callback_function, this));
    }

private:
    void callback_function()
    {
        auto message = std_msgs::msg::String();
        double position = (time_ * time_) + (2 * time_); // position function t^2+2t
        message.data = "Current time: " + std::to_string(time_) + "   Current Position: " + std::to_string(position);
        RCLCPP_INFO(this->get_logger(), "publishing: '%s'", message.data.c_str());
        time_++; // increment time by 1
        pub_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
    int time_;

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher>());
    rclcpp::shutdown();
    return 0;
}