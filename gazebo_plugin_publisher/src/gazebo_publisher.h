#ifndef GAZEBO_PUBLISHER
#define GAZEBO_PUBLISHER

#include "gazebo/common/Plugin.hh"
#include <ros/ros.h>
#include <std_msgs/Float64.h>

namespace gazebo {

class TempHumidityPublisher : public WorldPlugin
{

    public:
        TempHumidityPublisher(); 
        ~TempHumidityPublisher();

        void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);

    private:
        ros::NodeHandle nh;
        ros::Publisher temp_publisher;
        ros::Publisher humidity_publisher;

};


}
#endif