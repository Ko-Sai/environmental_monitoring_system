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
	void callbackImage(sensor_msgs::Image img_data);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();
    void imageUpdated(sensor_msgs::Image img_data);

public Q_SLOTS:
	void set_forward_speed();
	void set_backward_speed();
	void set_left_speed();
	void set_right_speed();
	void set_stop_speed();

private:
	int init_argc;
	char** init_argv;

	ros::Publisher chatter_publisher;
	ros::Publisher cmd_vel_publisher;
	ros::Subscriber image_subscriber;

    QStringListModel logging_model;
    sensor_msgs::Image image_data;
    geometry_msgs::Twist cmd_vel_msg;

    void pub_cmd_vel();
};

}  // namespace monitoring_gui

#endif /* monitoring_gui_QNODE_HPP_ */
