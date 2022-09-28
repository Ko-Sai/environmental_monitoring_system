#include "gazebo_publisher.h"

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(TempHumidityPublisher)

TempHumidityPublisher::TempHumidityPublisher()
{

    temp_publisher     = nh.advertise<std_msgs::Float64>("/gazebo/temperature_data", 1);
    humidity_publisher = nh.advertise<std_msgs::Float64>("/gazebo/humidity_data", 1);
    ROS_INFO("Hello Constructor!");

}


TempHumidityPublisher::~TempHumidityPublisher() {}


void TempHumidityPublisher::Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf)
{

    // std_msgs::Float64 msg;
    // msg.data = 100.0;
    // ROS_INFO("Hello Publisher!");
 
    // temp_publisher.publish(msg); 
    ROS_INFO("Hello Load1!");
    this->connection = this->parentSensor->ConnectUpdated(std::bind(&TempHumidityPublisher::publish, this));
    ROS_INFO("Hello Load2!");

}

void TempHumidityPublisher::publish()
{
    std_msgs::Float64 msg;
    msg.data = 100.0;
    ROS_INFO("Hello Publisher!");
 
    temp_publisher.publish(msg); 
}
