#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <math.h>
//#include <std_msgs/Int8.h>

float pickGoal_x = 5.09;
float pickGoal_y = 4.88;
float dropGoal_x = -3.73;
float dropGoal_y =  0.56;
float thresh = 0.30f;
bool pickup = false;
bool dropoff = false;

void callback_odom(const nav_msgs::Odometry::ConstPtr &msg)
{
  float botPos_x = msg->pose.pose.position.x;
  float botPos_y = msg->pose.pose.position.y;
  
  float pickupDist = 0.0f;
  float dropoffDist = 0.0f;
  if(!pickup && !dropoff)
  {
    pickupDist = pow( pow((pickGoal_x - botPos_x),2) + pow((pickGoal_y - botPos_y),2), 0.5);
    ROS_INFO("Distance to pickup: ([%f])", pickupDist);
    if(pickupDist <= thresh && pickupDist >= -thresh)
    {
      ROS_WARN_ONCE("Robot reached pickup goal!");
      pickup = true;
    }
  }
  if(!dropoff && pickup)
  {
    dropoffDist = pow( pow((dropGoal_x - botPos_x),2) + pow((dropGoal_y - botPos_y),2), 0.5);
    ROS_INFO("Distance to dropoff: ([%f])", dropoffDist);
    if(dropoffDist <+ thresh && dropoffDist >= -thresh)
    {
      ROS_WARN_ONCE("Robot reached dropoff goal!");
      pickup = false;
      dropoff = true;
    }
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 1000, callback_odom);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker. This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "marker_shapes";
  marker.id = 0;

  // Set the marker type to CUBE
  marker.type = shape;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 1.0f;
  marker.color.g = 0.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  
  // Pickup setup
  marker.pose.position.x = 5.09;
  marker.pose.position.y = 4.88;
  marker.pose.position.z = 0.0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
    
  
  while (ros::ok())
  {
  
    marker.lifetime = ros::Duration();

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    /*if (pickup)
    {
      marker.action = visualization_msgs::Marker::DELETE;
      ros::Duration(1.0).sleep();
      ROS_WARN_ONCE("Robot picked up object!");
      
    }
    if (dropoff)
    {
      marker.pose.position.x = dropGoal_x;
      marker.pose.position.y = dropGoal_y;
      marker.action = visualization_msgs::Marker::ADD;
      ros::Duration(1.0).sleep();
      ROS_WARN_ONCE("Robot picked up object!");
    }
    //marker_pub.publish(marker);

    ros::spinOnce();*/
  }
       
  // Display marker at pickup location
  ROS_INFO("Create Marker");
  marker.pose.position.x = 3.5;
  marker.pose.position.y = -0.26;
  marker.action = visualization_msgs::Marker::ADD;
    
  // Publish pickup marker
  marker_pub.publish(marker);

  // Establish 5 sec delay before deleting marker, then DELETE
  //ros::Duration(5.0).sleep();
  ROS_INFO("Remove pickup marker");
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);

  // Wait 5 seconds until displaying marker at drop-off location
  //ros::Duration(5.0).sleep();
  ROS_INFO("create drop-off marker");
  marker.pose.position.x = 4.57;
  marker.pose.position.y = 2.58;
  marker.action = visualization_msgs::Marker::ADD;
  // Display marker at drop-off location
  marker_pub.publish(marker);

  return 0;
}
