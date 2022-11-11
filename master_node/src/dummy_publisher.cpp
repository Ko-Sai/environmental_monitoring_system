#include "master_node/dummy_publisher.h"

dummyPublisher::dummyPublisher()
{
	ros::NodeHandle nh_private("~");
  	getParameters(nh_private); 
}

dummyPublisher::~dummyPublisher() {}


bool dummyPublisher::getParameters(ros::NodeHandle &n_handle)
{

	n_handle.param("m_topic_temp_data"             , m_topic_temp_data        , std::string("/dummy/temperature_data"));
  	n_handle.param("m_topic_humidity_data"         , m_topic_humidity_data    , std::string("/dummy/humidity_data"));
  	n_handle.param("m_world_weather"               , m_world_weather          , int(0));
  	n_handle.param("hot_h_temp"                    , hot_h_temp               , float(22.5));
  	n_handle.param("hot_l_temp"                    , hot_l_temp               , float(20.0));
  	n_handle.param("cold_h_temp"                   , cold_h_temp              , float(85));
  	n_handle.param("cold_l_temp"                   , cold_l_temp              , float(80));
  	n_handle.param("mid_h_temp"                    , mid_h_temp               , float(75));
  	n_handle.param("mid_l_temp"                    , mid_l_temp               , float(70));


}

int dummyPublisher::get_worldWeather()
{

	if (m_world_weather == 0)
	{
		h_temp = hot_h_temp;
		l_temp = hot_l_temp;
	} 	

	else if(m_world_weather == 1)
	{
		h_temp = cold_h_temp;
		l_temp = cold_l_temp;
	}
	else if(m_world_weather == 2)
	{
		h_temp = mid_h_temp;
		l_temp = mid_l_temp;
	}

}

void dummyPublisher::publish_data()
{

	get_worldWeather();
	dummy_temp_data = l_temp + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(h_temp-l_temp)));
    dummy_humidity_data = 30 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(50-30)));

    // std::cout<<"Random number : "<< 20.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(22.5-20.0))) <<std::endl;
    temp_data.data = dummy_temp_data;
    humidity_data.data = dummy_humidity_data;
 
    temp_publisher.publish(temp_data); 
    humidity_publisher.publish(humidity_data);
}


void dummyPublisher::run()
{

	ros::Rate loop_rate(20);
    temp_publisher     = nh.advertise<std_msgs::Float32>(m_topic_temp_data, 1);
    humidity_publisher = nh.advertise<std_msgs::Float32>(m_topic_humidity_data, 1);

    while(ros::ok())
    {

    	dummyPublisher::publish_data();

    	ros::spinOnce();  
    	loop_rate.sleep();
    }

}





