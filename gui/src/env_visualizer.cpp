#include "gui/env_visualizer.h"

EnvVisualizer::EnvVisualizer( QWidget* parent )
  : QWidget( parent )
{

		QGridLayout* controls_layout = new QGridLayout(); 

		m_forward_movement_button = new QPushButton;
  	m_forward_movement_button->setText("^");
  	m_forward_movement_button->setGeometry(QRect(90, 180, 91, 31));

  	m_backward_movement_button = new QPushButton;
  	m_backward_movement_button->setText("v");
  	m_backward_movement_button->setGeometry(QRect(90, 180, 91, 31));

  	m_left_movement_button = new QPushButton;
  	m_left_movement_button->setText("<");
  	m_left_movement_button->setGeometry(QRect(90, 180, 91, 31));

  	m_right_movement_button = new QPushButton;
  	m_right_movement_button->setText(">");
  	m_right_movement_button->setGeometry(QRect(90, 180, 91, 31));

  	m_start_button = new QPushButton;
  	m_start_button->setText("Start");
  	m_start_button->setGeometry(QRect(90, 180, 91, 31));

  	m_stop_movement_button = new QPushButton;
  	m_stop_movement_button->setText("Stop");
  	m_stop_movement_button->setGeometry(QRect(90, 180, 91, 31));

  	m_temp_data_display = new QLineEdit;
  	m_temp_data_display->setText("Temp data");
  	m_humidity_data_display = new QLineEdit;
  	m_humidity_data_display->setText("Humidity data");

		m_forward_movement_button->setEnabled(true);
  	m_backward_movement_button->setEnabled(true);  
  	m_left_movement_button->setEnabled(true);
  	m_right_movement_button->setEnabled(true);
  	m_start_button->setEnabled(true);
  	m_stop_movement_button->setEnabled(true);

		controls_layout->addWidget( m_forward_movement_button, 0, 0 );
  	controls_layout->addWidget( m_backward_movement_button, 0, 1 );
  	controls_layout->addWidget( m_left_movement_button, 0, 2 );
  	controls_layout->addWidget( m_right_movement_button, 0, 3 );
  	controls_layout->addWidget( m_start_button, 1, 0 );
  	controls_layout->addWidget( m_stop_movement_button, 1, 1 );
  	controls_layout->addWidget( m_temp_data_display, 1, 2 );
  	controls_layout->addWidget( m_humidity_data_display, 1, 3 );

  	render_panel_ = new rviz::RenderPanel();
  	QVBoxLayout* main_layout = new QVBoxLayout;
  	main_layout->addLayout( controls_layout );
  	main_layout->addWidget( render_panel_ );

  	setLayout( main_layout );

  	// Make signal/slot connections.
  	connect( m_start_button, SIGNAL(clicked()), this, SLOT( on_m_start_button_clicked()));
  	connect( m_forward_movement_button, SIGNAL(clicked()), this, SLOT( on_m_forward_movement_button_clicked()));
  	connect( m_backward_movement_button, SIGNAL(clicked()), this, SLOT( on_m_backward_movement_button_clicked()));
  	connect( m_left_movement_button, SIGNAL(clicked()), this, SLOT( on_m_left_movement_button_clicked()));
  	connect( m_right_movement_button, SIGNAL(clicked()), this, SLOT( on_m_right_movement_button_clicked()));
  	connect( m_stop_movement_button, SIGNAL(clicked()), this, SLOT( on_m_stop_movement_button_clicked()));

  	manager_ = new rviz::VisualizationManager( render_panel_ );
  	render_panel_->initialize( manager_->getSceneManager(), manager_ );

  	manager_->initialize();
  	manager_->startUpdate();

}

EnvVisualizer::~EnvVisualizer()
{

		delete manager_;
}


void EnvVisualizer::on_m_start_button_clicked()
{
		// rviz::Display *display_ptr = nullptr;
		display_ = manager_->createDisplay( "rviz/Image", "/camera/rgb/image_raw", true );
		ROS_ASSERT( display_ != NULL );
    display_->subProp("Image Topic")->setValue("/camera/rgb/image_raw");

}


void EnvVisualizer::on_m_forward_movement_button_clicked()
{

		twist.linear.x = 0.2;
		twist.angular.z = 0.0;
		cmd_vel_pub.publish(twist);

}

void EnvVisualizer::on_m_backward_movement_button_clicked()
{

		twist.linear.x = -0.2;
		twist.angular.z = 0.0;
		cmd_vel_pub.publish(twist);

}

void EnvVisualizer::on_m_left_movement_button_clicked()
{

		twist.linear.x = 0.0;
		twist.angular.z = -0.2;
		cmd_vel_pub.publish(twist);

}

void EnvVisualizer::on_m_right_movement_button_clicked()
{

		twist.linear.x = 0.0;
		twist.angular.z = 0.2;
		cmd_vel_pub.publish(twist);

}

void EnvVisualizer::on_m_stop_movement_button_clicked()
{

		twist.linear.x = 0.0;
		twist.angular.z = 0.0;
		cmd_vel_pub.publish(twist);

}


void EnvVisualizer::run()
{

	ros::Rate loop_rate(10); 
	  
	// Publishers
	cmd_vel_pub           = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

	// Subscribers


	// while(ros::ok())
	// { 

	//     ros::spinOnce();  
	//     loop_rate.sleep();

	//  }

}