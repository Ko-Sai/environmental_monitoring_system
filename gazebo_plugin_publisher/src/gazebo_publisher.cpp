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

    // std_msgs::Float64 msg;
    // msg.data = 100.0;
    // ROS_INFO("Hello Publisher!");
 
    // temp_publisher.publish(msg); 
    transport::NodePtr node(new transport::Node());
    node->Init(_world->Name());   
    transport::PublisherPtr factoryPub = node->Advertise<msgs::Factory>("~/factory");
    msgs::Factory msg;

      // Model file to load
      msg.set_sdf_filename("model://cylinder");

      // Pose to initialize the model to
      msgs::Set(msg.mutable_pose(),
          ignition::math::Pose3d(
            ignition::math::Vector3d(1, -2, 0),
            ignition::math::Quaterniond(0, 0, 0)));

      // Send the message
      factoryPub->Publish(msg);

}
