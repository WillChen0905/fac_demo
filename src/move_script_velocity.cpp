#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include "geometry_msgs/Twist.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "Move_Script_Velocity");
	ros::NodeHandle nh;

	ros::Publisher move_script_pub = nh.advertise< geometry_msgs::PoseStamped >("cmd_vel", 10); //我不知道速度命令該發給誰,我知道位置命令是經由/move_base_simple/goal這個topic給move_base
																							   //我只能用名子猜是cmd_vel,然後他是geometry_msgs/Twist的格式

	geometry_msgs::Twist msg ;

	 msg.linear.x=0.1;
     msg.linear.y=0.0;
     msg.linear.z=  0.0;  
     msg.angular.x= 0;
     msg.angular.y= 0;
     msg.angular.z=0.0;


//我參考這個https://answers.ros.org/question/331522/sending-velocity-commands-to-the-robot-throught-cmd_vel-topic/

	move_script_pub.publish(msg);

	ros::spin();
	return 0;
}