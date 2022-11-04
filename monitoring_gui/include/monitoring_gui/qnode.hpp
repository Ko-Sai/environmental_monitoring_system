/**
 * @file /include/monitoring_gui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef monitoring_gui_QNODE_HPP_
#define monitoring_gui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <string>

#include <image_transport/image_transport.h>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace monitoring_gui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);
	void callbackImage(const sensor_msgs::Image::ConstPtr& img_msg);
	void callbackTemp(std_msgs::Float32 temp_msg);
	void callbackHumidity(std_msgs::Float32 humidity_msg);
	
	sensor_msgs::Image::ConstPtr image_data;
    float temp_data;
    float humidity_data;

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();
    void imageUpdated();
    void tempUpdated();
    void humidityUpdated();

public Q_SLOTS:
	void set_forward_speed();
	void set_backward_speed();
	void set_left_speed();
	void set_right_speed();
	void set_stop_speed();

private:
	int init_argc;
	char** init_argv;

	ros::Publisher cmd_vel_publisher;
	ros::Subscriber image_subscriber;
	ros::Subscriber temp_subscriber;
	ros::Subscriber humidity_subscriber;

	image_transport::Subscriber subscriber_;

    QStringListModel logging_model;
    geometry_msgs::Twist cmd_vel_msg;

    void pub_cmd_vel();
};

}  // namespace monitoring_gui

#endif /* monitoring_gui_QNODE_HPP_ */
