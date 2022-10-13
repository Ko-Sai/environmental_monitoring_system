/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
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
    
}

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/



/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */


/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/


/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/



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


void monitoring_gui::MainWindow::on_startButton_clicked()
{
    conversion_mat_.release();

    subscriber_.shutdown();

    // reset image on topic change
    ui.image_frame->setImage(QImage());

}


void monitoring_gui::MainWindow::imageUpdatedView()
{
    //std::cout<<"Getting image data"<<std::endl;
}

void monitoring_gui::MainWindow::tempUpdatedView()
{
    QString temp_str = QString::number(qnode.temp_data, 'f', 2);
    ui.tempDisplay->setText(temp_str);
}

void monitoring_gui::MainWindow::humidityUpdatedView()
{
    //std::cout<<"Getting humidity data"<<std::endl;
    QString humidity_str = QString::number(qnode.humidity_data, 'f', 2);
    ui.humidityDisplay->setText(humidity_str);
}

