#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool 
class MyNumCounter(Node): 
    def __init__(self):
        super().__init__("number_counter") 
        self.count = 0
        self.subscriber_ = self.create_subscription(Int64, "nombre",self.subscriberCallback,10)
        self.publisher_ = self.create_publisher(Int64, "nombre_count", 10)
        self.timer = self.create_timer(0.5,self.publisherCallback)
        self.get_logger().info("Time to count some numbers")
        self.server = self.create_service(SetBool, "reset_counter",self.serviceCallback)
        
    def subscriberCallback(self,msg):
        self.count += msg.data


    def publisherCallback(self):
        msg = Int64()
        msg.data = self.count
        self.publisher_.publish(msg)
    
    def serviceCallback(self,request,response):
        self.get_logger().info(str(request.data))
        if request.data:
            self.count = 0
            response.success = True
        return response

def main(args=None):
    rclpy.init(args=args)
    node = MyNumCounter() 
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    
    main()