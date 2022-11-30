#ifndef DUMMY_PUBLISHER_H
#define DUMMY_PUBLISHER_H

#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Float32.h>

using namespace std;

class dummyPublisher
{
  	public:

    	dummyPublisher();
    	~dummyPublisher();

    	void run();

  	private:

    	// Ros Node
    	ros::NodeHandle nh;

	    //Publishers
	    ros::Publisher temp_publisher;
	    ros::Publisher humidity_publisher;

	    //Topic names
	    string m_topic_temp_data;          
	    string m_topic_humidity_data; 

	    //Variables 
	    string m_world_weather;
	    std_msgs::Float32 temp_data;
        std_msgs::Float32 humidity_data;

        float hot_h_temp;
        float hot_l_temp;
        float cold_h_temp;
        float cold_l_temp;
        float mid_h_temp;
        float mid_l_temp;

        float hot_h_humidity;
        float hot_l_humidity;
        float cold_h_humidity;
        float cold_l_humidity;
        float mid_h_humidity;
        float mid_l_humidity;

        float h_temp;
        float l_temp;

        float h_humidity;
        float l_humidity;

        float dummy_temp_data;
        float dummy_humidity_data;

	    //Functions         
	    bool getParameters(ros::NodeHandle &n_handle);
	    int get_worldWeather();
	    void publish_data();

};

#endif
