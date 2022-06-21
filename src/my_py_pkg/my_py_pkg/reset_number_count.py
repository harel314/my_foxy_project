#!/usr/bin/env python3
from requests import request
import rclpy
from rclpy.node import Node
from functools import partial
 
from example_interfaces.srv import SetBool

class ResetClient(Node):
    def __init__(self):
        super().__init__("reset_number_count")
        self.get_logger().info("reset_number_count has been initialized")
        self.call_reset_counter_server(True)

    def call_reset_counter_server(self,reset):
        client = self.create_client(SetBool, "reset_counter")
        while not client.wait_for_service(1.0):
            self.get_logger().warn("Waiting for Server..")
        
        request = SetBool.Request()
        request.data = True

        future = client.call_async(request)
        future.add_done_callback(partial(self.callback_reset_number, reset = reset))
    
    def callback_reset_number(self,future,reset):
        try:
            response = future.result()
            self.get_logger().info(str(response.success))
        except Exception as e:
            self.get_logger().error("Service call failed, %" %(e,))


def main(args=None):
    rclpy.init(args=args)
    node = ResetClient()  
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":

    main()