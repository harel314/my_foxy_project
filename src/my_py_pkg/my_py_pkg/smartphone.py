#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String

class SmartPhoneNode(Node):
    def __init__(self):
        super().__init__("smartphone")
        self.get_logger().info("Smartphone hass been started. ")
        self.subscriber  = self.create_subscription(String, "robot_news",self.callback_robot_news,10)

    def callback_robot_news(self,msg):
        self.get_logger().info(msg.data)

def main(args=None):
    rclpy.init(args=args) #initiate the node
    node = SmartPhoneNode()
    rclpy.spin(node) #will keep the node alive
    rclpy.shutdown() #shutdown the node


if __name__ == "__main__":

    main()