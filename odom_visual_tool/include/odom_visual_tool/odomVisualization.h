#include <ros/ros.h>

/* ros msg */
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>

#include <iostream>
#include <vector>

namespace odom_visualization
{
  class odomVisualization
  {
  public:
    ros::NodeHandle m_nh;
    std::vector<geometry_msgs::Point> m_points;
    int m_cnt_odom;
    int m_max_cnt_odom;
    int m_marker_id;
    visualization_msgs::MarkerArray m_markers;
    nav_msgs::Path m_visual_path;

    std::string m_odom_sub_topic_name;
    std::string m_markers_pub_topic_name;
    std::string m_path_pub_topic_name;

    ros::Publisher m_markers_pub;
    ros::Publisher m_path_pub;

    ros::Subscriber m_odom_sub;

    void onInit();
    void odomCallback(const nav_msgs::OdometryConstPtr& odom_msg);
    visualization_msgs::Marker initMarker();
  };
}
