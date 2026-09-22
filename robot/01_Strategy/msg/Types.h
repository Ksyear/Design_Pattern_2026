#ifndef MSG_TYPES_H
#define MSG_TYPES_H

// ROS 2 메시지 흉내 - rclcpp 없이 구조만 빌려 온다.
//   Twist     <- geometry_msgs/msg/Twist      (로봇에 내리는 속도 명령)
//   Pose2D    <- geometry_msgs/msg/PoseStamped 의 평면 버전
//   LaserScan <- sensor_msgs/msg/LaserScan     (여기서는 정면 최단 거리 하나로 줄임)
//
// 이 폴더만 .cpp 짝이 없다. 데이터만 있고 동작이 없으니 정의할 것도 없기 때문이다.
struct Twist {
	double linear_x = 0.0;   // m/s
	double angular_z = 0.0;  // rad/s
};

struct Pose2D {
	double x = 0.0;
	double y = 0.0;
	double yaw = 0.0;        // rad
};

struct LaserScan {
	double front_range_m = 10.0;  // 정면 장애물까지 거리
};

#endif
