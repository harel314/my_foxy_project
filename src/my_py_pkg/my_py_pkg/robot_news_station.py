#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.msg import String

class RobotNewsStationNode(Node):
    def __init__(self):
        super().__init__("robot_news_station")

        self.robot_name = "C3PO"
        self.publisher_ = self.create_publisher(String, "robot_news", 10)        
        self.timer = self.create_timer(0.5,self.publish_news)
        self.get_logger().info("Robot News Station has been started")


    def publish_news(self):
        msg = String()
        msg.data = 'Hi, this is ' + str(self.robot_name) + ' from the robot news station'
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args) #initiate the node
    node = RobotNewsStationNode()
    rclpy.spin(node) #will keep the node alive
    rclpy.shutdown() #shutdown the node

if __name__ == "__main__":

    main()