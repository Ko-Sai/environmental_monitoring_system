#ifndef ENV_VISUALIZER_H
#define ENV_VISUALIZER_H

#include <QWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QColor>
#include <QDebug>

#include <ros/ros.h>

class EnvVisualizer{

	public:
		EnvVisualizer();
		~EnvVisualizer();

		// Functions(public)
		void run();


	private:

		// ROS Node
		ros::NodeHandle nh;

		// Subscribers
		ros::Subscriber sub_;

		// Publishers
		ros::Publisher pub_;

		// Topic names


		// Variables


		// Objects


		// Functions(private)
		void visualize();


		// Callback functions




};


#endif
