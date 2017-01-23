#include <odom_visual_tool/odomVisualization.h>

namespace odom_visualization
{
  void odomVisualization::onInit()
  {
    ros::NodeHandle pnh("~");
    pnh.param("odom_sub_topic_name", m_odom_sub_topic_name, std::string("/truck/global/odom"));
    pnh.param("markers_pub_topic_name", m_markers_pub_topic_name, std::string("/truck/markers"));
    pnh.param("path_pub_topic_name", m_path_pub_topic_name, std::string("/truck/path"));
    pnh.param("max_cnt_odom", m_max_cnt_odom, 1000);
    pnh.param("clear_old_visualization", m_is_clear_old_visualization, true);

    m_cnt_odom = 0;
    m_marker_id = 0;
    m_odom_sub = m_nh.subscribe<nav_msgs::Odometry>(m_odom_sub_topic_name, 1, &odomVisualization::odomCallback, this);
    m_path_pub = m_nh.advertise<nav_msgs::Path>(m_path_pub_topic_name, 1);
    m_markers_pub = m_nh.advertise<visualization_msgs::MarkerArray>(m_markers_pub_topic_name, 1);
  }

    void odomVisualization::odomCallback(const nav_msgs::OdometryConstPtr& odom_msg)
    {
      if (m_cnt_odom == 0)
        m_visual_path.header = odom_msg->header;
      else if (m_is_clear_old_visualization && m_cnt_odom >= m_max_cnt_odom){
        m_visual_path.poses.erase(m_visual_path.poses.begin());
        m_visual_path.header = m_visual_path.poses[0].header;
        m_markers.markers.erase(m_markers.markers.begin());
        --m_cnt_odom;
        // todo: remove previous marker, add delele mark to old ones.
      }
      ++m_cnt_odom;
      geometry_msgs::PoseStamped cur_pose;
      cur_pose.header = odom_msg->header;
      cur_pose.pose = odom_msg->pose.pose;
      m_visual_path.poses.push_back(cur_pose);

      visualization_msgs::Marker cur_marker = initMarker();
      cur_marker.header = odom_msg->header;
      cur_marker.pose = odom_msg->pose.pose;
      m_markers.markers.push_back(cur_marker);

      m_markers_pub.publish(m_markers);
      m_path_pub.publish(m_visual_path);
    }

    visualization_msgs::Marker odomVisualization::initMarker()
    {
      visualization_msgs::Marker point_marker;
      point_marker.ns = "odom";
      point_marker.action = visualization_msgs::Marker::ADD;
      point_marker.id = m_marker_id;
      ++m_marker_id;
      point_marker.type = visualization_msgs::Marker::CUBE;

      point_marker.pose.position.x = 0.0;
      point_marker.pose.position.y = 0.0;
      point_marker.pose.position.z = 0.0;

      point_marker.pose.orientation.x = 0.0;
      point_marker.pose.orientation.y = 0.0;
      point_marker.pose.orientation.z = 0.0;
      point_marker.pose.orientation.w = 1.0;
      point_marker.scale.x = 0.1;
      point_marker.scale.y = 0.1;
      point_marker.scale.z = 0.1;
      point_marker.color.a = 1.0;
      point_marker.color.r = 1.0f;
      point_marker.color.g = 0.0f;
      point_marker.color.b = 0.0f;
      return point_marker;
    }
}
