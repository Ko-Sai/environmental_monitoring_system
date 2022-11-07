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

    dummy_temp_data = 20.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(22.5-20.0)));
    dummy_humidity_data = 30 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(50-30)));

    // std::cout<<"Random number : "<< 20.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(22.5-20.0))) <<std::endl;
    temp_data.data = dummy_temp_data;
    humidity_data.data = dummy_humidity_data;
 
    temp_publisher.publish(temp_data); 
    humidity_publisher.publish(humidity_data);
}
