#include <ros/ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"



int main(int argc, char** argv)
{
	ros::init(argc, argv, "Move_Script_Position");
	ros::NodeHandle nh;

	ros::Publisher move_script_pub = nh.advertise< geometry_msgs::PoseStamped >("/move_base_simple/goal", 10);
	//ros::Subscriber move_script_sub = nh.subscribe("/tf", 10);

	geometry_msgs::PoseStamped simple_goal;


    	//這邊我不知道該怎形容他的姿態,我參考的是 person_tracking.cpp的102行,這些參數適用echo看來的
		simple_goal.pose.position.x = 18.291;           //simple_goal.pose.position.x = 18.291;
		simple_goal.pose.position.y = 0.8767;           //simple_goal.pose.position.y = 0.8767;
		simple_goal.pose.orientation.z = -0.006792;     // simple_goal.pose.orientation = quat_msg;
		simple_goal.pose.orientation.w = -0.9999;       // simple_goal.pose.orientation = quat_msg;
		simple_goal.header.frame_id = "map";         


	move_script_pub.publish(simple_goal);



	ros::spin();
	return 0;
}