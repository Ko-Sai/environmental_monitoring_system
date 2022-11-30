/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/network.h>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/monitoring_gui/qnode.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace monitoring_gui {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{
		 
	}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::getParameters(ros::NodeHandle &n_handle)
{

	n_handle.param("m_world_weather"             , m_rosbag_name        , std::string("dummy"));

}


bool QNode::init() 
{

	ros::init(init_argc,init_argv,"monitoring_gui");
	
	ros::NodeHandle nh_private("~");
	getParameters(nh_private);	

	if ( ! ros::master::check() )
	{
		return false;
	}

	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	image_transport::ImageTransport it(n);
	image_transport::TransportHints hints("raw");
	subscriber_ = it.subscribe("/camera/rgb/image_raw", 1, &QNode::callbackImage, this, hints);

	// Add your ros communications here.
	cmd_vel_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	// image_subscriber = n.subscribe("/camera/rgb/image_raw", 5, &QNode::callbackImage, this);
	temp_subscriber = n.subscribe("/dummy/temperature_data", 5, &QNode::callbackTemp, this);
	humidity_subscriber = n.subscribe("/dummy/humidity_data", 5, &QNode::callbackHumidity, this);
	start();
	return true;

}

bool QNode::init(const std::string &master_url, const std::string &host_url) 
{

	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"monitoring_gui");

	if ( ! ros::master::check() ) 
	{
		return false;
	}

	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;

	// Add your ros communications here.
	start();
	return true;

}

void QNode::run() 
{

	ros::Rate loop_rate(30);
	int count = 0;
	while ( ros::ok() ) 
	{

		pub_cmd_vel();

		ros::spinOnce();
		loop_rate.sleep();
		++count;

	}

	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) 
{

	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;

	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;

		}
	}

	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar

}

void QNode::callbackImage(const sensor_msgs::Image::ConstPtr& img_msg)
{

	image_data = img_msg;

	Q_EMIT imageUpdated();
}

void QNode::callbackTemp(std_msgs::Float32 temp_msg)
{

	temp_data = temp_msg.data;

	Q_EMIT tempUpdated();
}

void QNode::callbackHumidity(std_msgs::Float32 humidity_msg)
{

	humidity_data = humidity_msg.data;

	Q_EMIT humidityUpdated();
}

void QNode::set_forward_speed()
{

	std::cout<<"forward"<<std::endl;
	cmd_vel_msg.linear.x = 0.3;
	cmd_vel_msg.angular.z = 0.0;

}

void QNode::set_backward_speed()
{

	std::cout<<"backward"<<std::endl;
	cmd_vel_msg.linear.x = -0.3;
	cmd_vel_msg.angular.z = 0.0;

}

void QNode::set_left_speed()
{

	std::cout<<"left"<<std::endl;
	cmd_vel_msg.linear.x = 0.0;
	cmd_vel_msg.angular.z = 0.3;

}

void QNode::set_right_speed()
{

	std::cout<<"right"<<std::endl;
	cmd_vel_msg.linear.x = 0.0;
	cmd_vel_msg.angular.z = -0.3;

}

void QNode::set_stop_speed()
{

	std::cout<<"stop"<<std::endl;
	cmd_vel_msg.linear.x = 0.0;
	cmd_vel_msg.angular.z = 0.0;
	
}

void QNode::pub_cmd_vel()
{
	cmd_vel_publisher.publish(cmd_vel_msg);
}

}  // namespace monitoring_gui

