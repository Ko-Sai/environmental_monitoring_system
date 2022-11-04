/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/monitoring_gui/main_window.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace monitoring_gui {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	qnode.init();
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    //topic = "/camera/rgb/image_raw";

    QObject::connect(&qnode, SIGNAL(imageUpdated()), this, SLOT(imageUpdatedView()));
    QObject::connect(&qnode, SIGNAL(tempUpdated()), this, SLOT(tempUpdatedView()));
    QObject::connect(&qnode, SIGNAL(humidityUpdated()), this, SLOT(humidityUpdatedView()));

    QObject::connect(this, SIGNAL(clicked_forward()), &qnode, SLOT(set_forward_speed()));
    QObject::connect(this, SIGNAL(clicked_backward()), &qnode, SLOT(set_backward_speed()));
    QObject::connect(this, SIGNAL(clicked_left()), &qnode, SLOT(set_left_speed()));
    QObject::connect(this, SIGNAL(clicked_right()), &qnode, SLOT(set_right_speed()));
    QObject::connect(this, SIGNAL(clicked_stop()), &qnode, SLOT(set_stop_speed()));

    rosbag_play_proc = new QProcess(this);
    
}

MainWindow::~MainWindow() {}


}  // namespace monitoring_gui


void monitoring_gui::MainWindow::on_forwardButton_clicked()
{
    Q_EMIT clicked_forward();
}

void monitoring_gui::MainWindow::on_backwardButton_clicked()
{
    Q_EMIT clicked_backward();
}

void monitoring_gui::MainWindow::on_leftButton_clicked()
{
    Q_EMIT clicked_left();
}

void monitoring_gui::MainWindow::on_rightButton_clicked()
{
    Q_EMIT clicked_right();
}

void monitoring_gui::MainWindow::on_stopButton_clicked()
{
    Q_EMIT clicked_stop();
}


void monitoring_gui::MainWindow::on_playButton_clicked()
{

    // rosbag_play_proc->start("rosbag record -o " + QString::fromStdString(std::to_string(duration))+ " "+ open_file_path);
    rosbag_play_proc->start("rosbag record -o dummy.bag /camera/rgb/image_raw __name:=my_bag");
    std::cout<<"Start recording data! "<<std::endl;

    // conversion_mat_.release();
    // subscriber_.shutdown();
}


void monitoring_gui::MainWindow::imageUpdatedView()
{

    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(qnode.image_data, sensor_msgs::image_encodings::RGB8);
    conversion_mat_ = cv_ptr->image;

    QImage image(conversion_mat_.data, conversion_mat_.cols, conversion_mat_.rows, conversion_mat_.step[0], QImage::Format_RGB888);
    ui.imageLabel->setPixmap(QPixmap::fromImage(image));
    
}

void monitoring_gui::MainWindow::tempUpdatedView()
{
    QString temp_str = QString::number(qnode.temp_data, 'f', 2);
    ui.tempDisplay->setText(temp_str);
}

void monitoring_gui::MainWindow::humidityUpdatedView()
{
    QString humidity_str = QString::number(qnode.humidity_data, 'f', 2);
    ui.humidityDisplay->setText(humidity_str);
}


void monitoring_gui::MainWindow::on_recordButton_clicked()
{

    rosbag_play_proc->start("rosnode kill /my_bag");
    std::cout<<"Stop recording data! "<<std::endl;

}
