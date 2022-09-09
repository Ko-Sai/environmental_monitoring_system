#include "gui/env_visualizer.h"

int main (int argc, char** argv)
{
  
  // Initialize ROS
  ROS_INFO("Node started");
  ros::init (argc, argv, "visualizer"); // need to change node name

  EnvVisualizer EnvVisualizerObj;

  EnvVisualizerObj.run();

  return 0;
}