#!/usr/bin/env python3
from typing import Counter
import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self):
        super().__init__("py_test")
        self.get_logger().info("Hello ROS2")
        self.counter_ = 0
        self.create_timer(0.5, self.timer_callback) # will run this code every 0.5 sec
    
    def timer_callback(self): # callback function will run in loop
        self.counter_ +=1
        self.get_logger().info("Hello " + str(self.counter_))

def main(args=None):
    rclpy.init(args=args) #initiate the node
    node = MyNode()
    rclpy.spin(node) #will keep the node alive
    rclpy.shutdown() #shutdown the node

if __name__ == "__main__":
    main()