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
  	n_handle.param("m_world_weather"               , m_world_weather          , std::string("office"));
  	n_handle.param("hot_h_temp"                    , hot_h_temp               , float(38.5));
  	n_handle.param("hot_l_temp"                    , hot_l_temp               , float(35.0));
  	n_handle.param("cold_h_temp"                   , cold_h_temp              , float(15.0));
  	n_handle.param("cold_l_temp"                   , cold_l_temp              , float(12.0));
  	n_handle.param("mid_h_temp"                    , mid_h_temp               , float(22.5));
  	n_handle.param("mid_l_temp"                    , mid_l_temp               , float(20.0));
  	n_handle.param("hot_h_humidity"                , hot_h_humidity               , float(80));
  	n_handle.param("hot_l_humidity"                , hot_l_humidity               , float(70));
  	n_handle.param("cold_h_humidity"               , cold_h_humidity              , float(30));
  	n_handle.param("cold_l_humidity"               , cold_l_humidity              , float(20));
  	n_handle.param("mid_h_humidity"                , mid_h_humidity               , float(60));
  	n_handle.param("mid_l_humidity"                , mid_l_humidity               , float(40));


}

int dummyPublisher::get_worldWeather()
{

	if (m_world_weather == "factory_warehouse")
	{
		h_temp = hot_h_temp;
		l_temp = hot_l_temp;

		h_humidity = cold_h_humidity;
		l_humidity = cold_l_humidity;
	} 	

	else if(m_world_weather == "agriculture")
	{
		h_temp = cold_h_temp;
		l_temp = cold_l_temp;

		h_humidity = hot_h_humidity;
		l_humidity = hot_l_humidity;
	}
	else if(m_world_weather == "office" || m_world_weather == "house")
	{
		h_temp = mid_h_temp;
		l_temp = mid_l_temp;

		h_humidity = mid_h_humidity;
		l_humidity = mid_l_humidity;
	}

}

void dummyPublisher::publish_data()
{

	get_worldWeather();
	dummy_temp_data = l_temp + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(h_temp-l_temp)));
    dummy_humidity_data = l_humidity + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(h_humidity-l_humidity)));

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





