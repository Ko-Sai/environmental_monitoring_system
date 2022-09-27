#include "gazebo_publisher.h"

using namespace gazebo;
GZ_REGISTER_WORLD_PLUGIN(TempHumidityPublisher)

TempHumidityPublisher::TempHumidityPublisher()
{

    temp_publisher     = nh.advertise<std_msgs::Float64>("/gazebo/temperature_data", 1);
    humidity_publisher = nh.advertise<std_msgs::Float64>("/gazebo/humidity_data", 1);

}


TempHumidityPublisher::~TempHumidityPublisher() {}


void TempHumidityPublisher::Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
{

    std_msgs::Float64 msg;
    msg.data = 100.0;
    ROS_INFO("Hello Publisher!");
 
    temp_publisher.publish(msg);    
    

}
