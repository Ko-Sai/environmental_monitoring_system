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
#include <opencv2/core/core.hpp>

#include <QImage>

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

protected:
    image_transport::Subscriber subscriber_;

    cv::Mat conversion_mat_;

private Q_SLOTS:
    void on_forwardButton_clicked();
    void on_startButton_clicked();
    void imageUpdatedView(sensor_msgs::Image img_data);

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
    std::string topic;
};

}  // namespace monitoring_gui

#endif // monitoring_gui_MAIN_WINDOW_H
