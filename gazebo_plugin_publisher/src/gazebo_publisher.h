#ifndef GAZEBO_PUBLISHER
#define GAZEBO_PUBLISHER

#include "gazebo/common/Plugin.hh"
#include "gazebo/common/Events.hh"
#include <ros/ros.h>
#include <std_msgs/Float32.h>



namespace gazebo {

class TempHumidityPublisher : public WorldPlugin
{

    public:
        TempHumidityPublisher(); 
        ~TempHumidityPublisher();

        void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);
        void publish_data();

    private:
        ros::NodeHandle nh;
        ros::Publisher temp_publisher;
        ros::Publisher humidity_publisher;
        event::ConnectionPtr connection;

        std_msgs::Float32 temp_data;
        std_msgs::Float32 humidity_data;

};


}
#endif
