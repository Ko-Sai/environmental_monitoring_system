#include "gui/env_visualizer.h"

int main (int argc, char** argv)
{
  
  // Initialize ROS
  ROS_INFO("Node started");
  ros::init (argc, argv, "Environment Monitoring");

  EnvVisualizer envObj;

  envObj.run();

  return 0;
}