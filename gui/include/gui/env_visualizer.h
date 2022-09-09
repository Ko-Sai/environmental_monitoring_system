#ifndef ENV_VISUALIZER_H
#define ENV_VISUALIZER_H

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

#include <ros/ros.h>

namespace rviz
{

	class VisualizationManager;

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
		//void on_m_button_record_clicked();


	private:

		// ROS Node
		ros::NodeHandle nh;

		// Subscribers
		ros::Subscriber sub_image;

		// Publishers
		ros::Publisher pub_;

		// Topic names
		std::string m_topic_image;


		// Variables
		std::string m_image_data;


		// Objects
		QPushButton* m_forward_movement_button;
  		QPushButton* m_backward_movement_button;
  		QPushButton* m_left_movement_button;
  		QPushButton* m_right_movement_button;
		rviz::VisualizationManager* manager_;


		// Functions(private)
		void visualize();


		// Callback functions
		//void rosCallbackPointCloud (const sensor_msgs::PointCloud2& msg_pointcloud);

};


#endif
