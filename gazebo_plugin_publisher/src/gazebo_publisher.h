#ifndef GAZEBO_PUBLISHER
#define GAZEBO_PUBLISHER

#include "gazebo/common/Plugin.hh"
#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include "gazebo/sensors/sensors.hh"
#include "gazebo/common/Events.hh"
#include <gazebo/sensors/Sensor.hh>
#include <gazebo/sensors/SensorTypes.hh>

namespace gazebo {

class GAZEBO_VISIBLE TempHumidityPublisher : public SensorPlugin
{

    public:
        TempHumidityPublisher(); 
        ~TempHumidityPublisher();

        void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);
        void publish();

    protected: sensors::RaySensorPtr parentSensor;
    private:
        
        event::ConnectionPtr connection;
        
    ros::NodeHandle nh;
    ros::Publisher temp_publisher;
    ros::Publisher humidity_publisher;
};


}
#endif