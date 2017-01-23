#include <odom_visual_tool/odomVisualization.h>

using namespace odom_visualization;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "odom_visualization_node");
  odomVisualization odom_visual;
  odom_visual.onInit();
  ros::spin();
  return 0;
}
