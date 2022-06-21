#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class MyNumPublisher : public rclcpp::Node 
{
public:
    MyNumPublisher() : Node("number_publisher") 
    {
        this->declare_parameter("number_to_publish",2);
        this->declare_parameter("publish_frequency",1.0);

        Const = this->get_parameter("number_to_publish").as_int();
        double publish_frequency = this->get_parameter("publish_frequency").as_double();

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("nombre", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds((int)(500 / publish_frequency)),
                                         std::bind(&MyNumPublisher::NumPublisher, this));
        RCLCPP_INFO(this->get_logger(), "Let's publish some numbers");
        
    }
 
private:
    void NumPublisher(){
        auto msg = example_interfaces::msg::Int64();
        msg.data = Const;
        publisher_->publish(msg);
    }
    
    std::int64_t Const;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNumPublisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}