#ifndef ENV_VISUALIZER_H
#define ENV_VISUALIZER_H

#include <QApplication>
#include <QWidget>
#include <QFileDialog>
#include <QSlider>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QColor>
#include <QProcess>
#include <QTimer>
#include <QCloseEvent>
#include <QDebug>

#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"

#include <ros/ros.h>

#include <geometry_msgs/Twist.h>

namespace rviz
{

	class VisualizationManager;
	class RenderPanel;

}

class EnvVisualizer: public QWidget
{
	Q_OBJECT

	public:
		
		EnvVisualizer( QWidget* parent = 0 );
		virtual ~EnvVisualizer();

		// Functions(public)
		void run();

	private Q_SLOTS:
		void on_m_start_button_clicked();
		void on_m_forward_movement_button_clicked();
		void on_m_backward_movement_button_clicked();
		void on_m_left_movement_button_clicked();
		void on_m_right_movement_button_clicked();
		void on_m_stop_movement_button_clicked();

	private:

		// ROS Node
		ros::NodeHandle nh;

		// Subscribers
		ros::Subscriber sub_image;

		// Publishers
		ros::Publisher cmd_vel_pub;

		// Topic names
		std::string m_topic_image;
		std::string m_topic_cmd_vel;


		// Variables
		std::string m_image_data;


		// Objects
		QPushButton* m_forward_movement_button;
  		QPushButton* m_backward_movement_button;
  		QPushButton* m_left_movement_button;
  		QPushButton* m_right_movement_button;
  		QPushButton* m_start_button;
  		QPushButton* m_stop_movement_button;
  		rviz::Display* display_;
		rviz::VisualizationManager* manager_;
		rviz::RenderPanel* render_panel_;

		geometry_msgs::Twist twist;


		// Functions(private)
		void visualize();


		// Callback functions
		//void rosCallbackPointCloud (const sensor_msgs::PointCloud2& msg_pointcloud);

};


#endif
