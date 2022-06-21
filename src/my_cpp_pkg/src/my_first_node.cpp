#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("cpp_test"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Cpp Node"); // make it print in the logger

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                         std::bind(&MyNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_); // enter Hello into the logger
    }

    rclcpp::TimerBase::SharedPtr timer_; //pointer to timer_ variable
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);               // initial
    auto node = std::make_shared<MyNode>(); // create node in shared pointer
    rclcpp::spin(node);                     // spin same as in python
    rclcpp::shutdown();                     // the shutdown
    return 0;
}