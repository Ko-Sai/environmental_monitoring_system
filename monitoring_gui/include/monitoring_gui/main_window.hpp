/**
 * @file /include/monitoring_gui/main_window.hpp
 *
 * @brief Qt based gui for monitoring_gui.
 *
 * @date November 2010
 **/
#ifndef monitoring_gui_MAIN_WINDOW_H
#define monitoring_gui_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <std_msgs/Float64.h>

#include <QImage>
#include <QTimer>
#include <QProcess>

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace monitoring_gui {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();



public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	

    /******************************************
    ** Manual connections
    *******************************************/

Q_SIGNALS:
    void clicked_forward();
    void clicked_backward();
    void clicked_left();
    void clicked_right();
    void clicked_stop();

protected:
    image_transport::Subscriber subscriber_;

    cv::Mat conversion_mat_;

public Q_SLOTS:
    void on_forwardButton_clicked();
    void on_backwardButton_clicked();
    void on_leftButton_clicked();
    void on_rightButton_clicked();
    void on_stopButton_clicked();
    void on_stopRecordButton_clicked();
    void on_startRecordButton_clicked();
    void imageUpdatedView();
    void tempUpdatedView();
    void humidityUpdatedView();

    // void spin_ros();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
    std::string topic;
    int index;
    std::string rosbag_name;

    QProcess *rosbag_play_proc;

};

}  // namespace monitoring_gui

#endif // monitoring_gui_MAIN_WINDOW_H
