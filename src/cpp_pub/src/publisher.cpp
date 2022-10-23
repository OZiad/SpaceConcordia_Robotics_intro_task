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
    Publisher() : Node("publisher")
    {
        // Assign publisher object to pub_ shared pointer
        pub_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&Publisher::callback_function, this));
    }

private:
    void callback_function()
    {
        auto message = std_msgs::msg::String();
        std::string sub_count = std::to_string(this->count_subscribers("topic"));
        message.data = "Number of subscribers for this topic: " + sub_count;
        if (std::stoi(sub_count) % 2 == 0 && std::stoi(sub_count) != 0)
        {
            message.data += "\nThat's an even number!";
        }
        else if (std::stoi(sub_count) % 2 != 0 && std::stoi(sub_count) != 0)
        {
            message.data += "\nThat's an odd number!";
        }
        else
        {
            message.data += "\nThat's a neutral number!";
        }
        RCLCPP_INFO(this->get_logger(), "publishing: '%s'", message.data.c_str());
        pub_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Publisher>());
    return 0;
}