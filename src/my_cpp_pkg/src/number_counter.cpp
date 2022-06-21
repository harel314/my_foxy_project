#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"

using std::placeholders::_1;
using std::placeholders::_2;


class MyNumCounter : public rclcpp::Node 
{
public:
    MyNumCounter() : Node("number_counter")
    {
        Const = 0;
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "nombre", 10,
            std::bind(&MyNumCounter::SubscribeCallback, this, std::placeholders::_1));

        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("nombre_counter", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                         std::bind(&MyNumCounter::NumPublisher, this));

        RCLCPP_INFO(this->get_logger(), "Let's count some numbers");

        server_ = this->create_service<example_interfaces::srv::SetBool>(
            "reset_counter",
            std::bind(&MyNumCounter::callbackReset, this, _1,_2)
            );
    }

private:
    void NumPublisher()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = Const;
        publisher_->publish(msg);
    }
    void SubscribeCallback(const example_interfaces::msg::Int64::SharedPtr msg)
    {

        Const += msg->data;
    }
    void callbackReset(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                              const example_interfaces::srv::SetBool::Response::SharedPtr response){
        if (request->data == true){
            response->success = true;
            response->message = "reset";
            Const = 0;
        }
        else{
            response->success = false;
            response->message = "no reset";
        }
    }

    std::int64_t Const;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNumCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}