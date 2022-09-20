#include "gui/env_visualizer.h"

int main (int argc, char** argv)
{
  
  // Initialize ROS
  if( !ros::isInitialized() )
  {

    ROS_INFO("Node started");
    ros::init( argc, argv, "visualizer"); // need to change node name

  }

  QApplication app( argc, argv );

  EnvVisualizer* EnvVisualizerObj = new EnvVisualizer();
  EnvVisualizerObj->show();
  EnvVisualizerObj->run();

  app.exec();

  delete EnvVisualizerObj;
}