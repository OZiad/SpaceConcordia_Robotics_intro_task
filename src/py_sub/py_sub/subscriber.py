import rclpy
import re
from rclpy.node import Node

from std_msgs.msg import String

class Subscriber(Node): 
    def __init__(self):
        super().__init__('subscriber')
        self.subscription = self.create_subscription(String, 'topic', self.listener_callback, 50)
    def listener_callback(self, msg):
        //re.findall(r'\d+',msg.data)
        self.get_logger().info('I received the following message: "%s'%msg.data)


def main (args=none):
    rclpy.init(args=args)
    subscriber = Subscriber()
    rclpy.spin(subscriber)
    rclpy.shutdown()
    
    

if __name__ == '__main__':
    main()

        