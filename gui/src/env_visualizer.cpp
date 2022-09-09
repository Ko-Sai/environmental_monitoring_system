#include "gui/env_visualizer.h"

EnvVisualizer::EnvVisualizer()
{ 
  
}

EnvVisualizer::~EnvVisualizer(){}




void EnvVisualizer::visualize()
{

}

void EnvVisualizer::run()
{

  ros::Rate loop_rate(10); 
  
  // Publishers

  // Subscribers


  while(ros::ok())
  { 

    ros::spinOnce();  
    loop_rate.sleep();
  }

}