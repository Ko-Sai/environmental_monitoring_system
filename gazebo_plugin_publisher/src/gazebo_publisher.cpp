#include "gazebo_publisher.h"

using namespace gazebo;
GZ_REGISTER_WORLD_PLUGIN(TempHumidityPublisher)

TempHumidityPublisher::TempHumidityPublisher()
{

    temp_publisher     = nh.advertise<std_msgs::Float32>("/gazebo/temperature_data", 1);
    humidity_publisher = nh.advertise<std_msgs::Float32>("/gazebo/humidity_data", 1);

}

TempHumidityPublisher::~TempHumidityPublisher() {}


void TempHumidityPublisher::Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
{

    this->connection =  event::Events::ConnectWorldUpdateBegin(boost::bind(&TempHumidityPublisher::publish_data, this));

}

void TempHumidityPublisher::publish_data()
{

    temp_data.data = 100.0;
    humidity_data.data = 200.0;
 
    temp_publisher.publish(temp_data); 
    humidity_publisher.publish(humidity_data);
}
