#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <move_base_msgs/MoveBaseActionResult.h>
#include <vector>
#include <math.h>
using namespace std;

class fac_demo{
  public:
    fac_demo(ros::NodeHandle &node) :
      nh_(node)
    {
      arm_pick_sub = nh_.subscribe("arm_pick", 10, &fac_demo::arm_pickCB, this);
      vel_pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
      goal_pub = nh_.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
      arm_place_pub = nh_.advertise<std_msgs::Bool>("arm_place", 10);
    }
  private:
    ros::NodeHandle nh_;
    ros::Subscriber arm_pick_sub;
    ros::Subscriber amcl_sub1;
    ros::Subscriber amcl_sub2;
    ros::Subscriber move_base_res1;
    ros::Publisher vel_pub;
    ros::Publisher goal_pub;
    ros::Publisher arm_place_pub;

    geometry_msgs::Twist vel;
    geometry_msgs::PoseStamped goal;
    std_msgs::Bool arm_place;


    double station1_x = 14.5113822001;
    double station1_y = 3.68106130164;

    double station2_x = 5.97245308241;
    double station2_y = 2.82131053684;
    double station2_z = -0.997553360049;
    double station2_w = 0.0699091829106;

    double station3_x = 2.58638990116;
    double station3_y = 2.3601986901;
    double station3_z = -0.999042028895;
    double station3_w = 0.0437609929198;

    double station4_x = 2.58638990116;
    double station4_y = 2.3601986901;

    int count = 0;



    void amcl_subCB2(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &amcl_pose){

      double vel_x = 0;
      double vel_y = 0;

      if(fabs(station4_x - amcl_pose->pose.pose.position.x) < 0.1 && fabs(station4_y - amcl_pose->pose.pose.position.y) < 0.1){
        arm_place.data = true;
        arm_place_pub.publish(arm_place);
        amcl_sub2.shutdown();
      }
      if(fabs(station4_x - amcl_pose->pose.pose.position.x) > 0.1){
          if(station4_x > amcl_pose->pose.pose.position.x){
            vel_x = -0.1;
          }else if(station4_x < amcl_pose->pose.pose.position.x){
            vel_x = 0.1;
          }
      }else{
        vel_x= 0;
      }
      if(fabs(station4_y - amcl_pose->pose.pose.position.y) > 0.1){
          if(station4_y > amcl_pose->pose.pose.position.y){
            vel_y = -0.1;
          }else if(station4_y < amcl_pose->pose.pose.position.y){
            vel_y = 0.1;
          }
      }else{
        vel_y= 0;
      }
      vel.linear.x = vel_x;
      vel.linear.y = vel_y;
      vel_pub.publish(vel);
    }

    void move_base_resCB(const move_base_msgs::MoveBaseActionResult::ConstPtr &result){

      count++;
      cout << count << endl;
      if(count == 1 && result->status.status == 3){
        for(int i=0; i<3; i++){
          cout << "wait for " << 2-i << " seconds" << endl;
          ros::Duration(1).sleep();
        }
        goal.header.frame_id = "map";
        goal.pose.position.x = station3_x;
        goal.pose.position.y = station3_y;
        goal.pose.orientation.z =station3_z;
        goal.pose.orientation.w =station3_w;
        goal_pub.publish(goal);
      }
      if(count == 2 && result->status.status == 3){
        amcl_sub2 = nh_.subscribe("amcl_pose", 10, &fac_demo::amcl_subCB2, this);
      }
    }

    void amcl_subCB1(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &amcl_pose){

      double vel_x = 0;
      double vel_y = 0;

      if(fabs(station1_x - amcl_pose->pose.pose.position.x) < 0.05 && fabs(station1_y - amcl_pose->pose.pose.position.y) < 0.05){
        vel.linear.x = vel_x;
        vel.linear.y = vel_y;
        vel_pub.publish(vel);
        goal.header.frame_id = "map";
        goal.pose.position.x = station2_x;
        goal.pose.position.y = station2_y;
        goal.pose.orientation.z =station2_z;
        goal.pose.orientation.w =station2_w;
        goal_pub.publish(goal);
        move_base_res1 = nh_.subscribe("move_base/result", 10, &fac_demo::move_base_resCB, this);
        amcl_sub1.shutdown();
      }

      if(fabs(station1_x - amcl_pose->pose.pose.position.x) > 0.05){
          if(station1_x > amcl_pose->pose.pose.position.x){
            vel_x = -0.12;
          }else if(station1_x < amcl_pose->pose.pose.position.x){
            vel_x = 0.12;
          }
      }else{
        vel_x= 0;
      }
      if(fabs(station1_y - amcl_pose->pose.pose.position.y) > 0.05){
          if(station1_y > amcl_pose->pose.pose.position.y){
            vel_y = -0.12;
          }else if(station1_y < amcl_pose->pose.pose.position.y){
            vel_y = 0.12;
          }
      }else{
        vel_y= 0;
      }
      vel.linear.x = vel_x;
      vel.linear.y = vel_y;
      vel_pub.publish(vel);
    }

    void arm_pickCB(const std_msgs::Bool::ConstPtr &arm_pick){
      if(arm_pick->data){
        amcl_sub1 = nh_.subscribe("amcl_pose", 10, &fac_demo::amcl_subCB1, this);
        arm_pick_sub.shutdown();
      }
    }
};


int main(int argc, char **argv){
  ros::init(argc, argv, "fac_demo");
  ros::NodeHandle nh;
  fac_demo FD(nh);
  ros::spin();
  return 0;
}

