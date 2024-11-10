import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import math

class EightShapePublisher(Node):

    def __init__(self):
        super().__init__('eight_shape_publisher')
        self.publisher = self.create_publisher(Twist, '/robot/cmd_vel', 10)
        timer_period = 0.1  # Период таймера
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.time = 0  # Время для изменения направления

    def timer_callback(self):
        # Делаем движение по восьмерке
        twist = Twist()

        # Синусоида для создания осциллирующей угловой скорости
        twist.linear.x = -0.3  # скорость по оси X (прямолинейное движение)

        # Меняем угловую скорость с использованием синусоиды
        twist.angular.z = 1.2 * math.sin(self.time)

        # Увеличиваем время для синуса
        self.time += 0.1

        self.publisher.publish(twist)


def main(args=None):
    rclpy.init(args=args)

    eight_shape_publisher = EightShapePublisher()

    rclpy.spin(eight_shape_publisher)

    rclpy.shutdown()


if __name__ == '__main__':
    main()
