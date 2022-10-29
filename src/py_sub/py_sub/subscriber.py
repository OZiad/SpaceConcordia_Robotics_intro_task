import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class Subscriber(Node): 
   
    def __init__(self):
        super().__init__('subscriber')
        self.subscription = self.create_subscription(String, 'topic', self.listener_callback, 50)
    
    def listener_callback(self, msg):
        coordinates = []
        # Function that extracts numbers from a string
        for t in msg.data.split():
            try:
                coordinates.append(float(t))
            except ValueError:
                pass
        self.get_logger().info('I received the following message: "%s'%msg.data)
        if(len(coordinates) == 2 and coordinates[0]!=0):
            velocity = coordinates[1]/coordinates[0]
            acceleration = velocity/coordinates[0]
            self.get_logger().info('The object\'s velocity is %d m/s'%velocity)
            self.get_logger().info('The object\'s acceleration is %d m/s^2\n'%acceleration)

        


def main (args=None):
    rclpy.init(args=args)
    subscriber = Subscriber()
    rclpy.spin(subscriber)
    rclpy.shutdown()
    
    

if __name__ == '__main__':
    main()

        