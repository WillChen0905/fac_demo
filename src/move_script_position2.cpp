#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"



int main(int argc, char** argv)
{
	ros::init(argc, argv, "Move_Script_Position2");
	ros::NodeHandle nh;

	ros::Publisher move_script_pub = nh.advertise< geometry_msgs::PoseStamped >("/move_base_simple/goal", 10);
	ros::Subscriber move_script_sub = nh.subscribe("/tf", 10);

if(!(simple_goal.pose.position.x = 18.291 && simple_goal.pose.position.y = 0.8767 ){ /*我這邊不知道該放什麼來接收/tf的資料,我用echo看過/tf的資料格式但是還是沒辦法確定要放什在這裡*/ )
	
    geometry_msgs::PoseStamped simple_goal;
 
     
		simple_goal.pose.position.x = 18.291;                   //simple_goal.pose.position.x = 18.291;
		simple_goal.pose.position.y = 0.8767;                  //simple_goal.pose.position.y = 0.8767;
		simple_goal.pose.orientation.z = -0.006792;     // simple_goal.pose.orientation = quat_msg;
		simple_goal.pose.orientation.w = -0.9999;       // simple_goal.pose.orientation = quat_msg;
		simple_goal.header.frame_id = "map";}


	move_script_pub.publish(simple_goal);

else if(simple_goal.pose.position.x = 18.291 && simple_goal.pose.position.y = 0.8767)
{ 
	geometry_msgs::PoseStamped simple_goal;
	    simple_goal.pose.position.x = 0;                   
		simple_goal.pose.position.y = 0;                 
		simple_goal.pose.orientation.z = 0;     
		simple_goal.pose.orientation.w =0 ;     
		simple_goal.header.frame_id = "map";}
	
}



	ros::spin();
	return 0;
}