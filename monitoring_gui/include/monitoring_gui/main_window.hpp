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


private Q_SLOTS:
    void on_forwardButton_clicked();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
};

}  // namespace monitoring_gui

#endif // monitoring_gui_MAIN_WINDOW_H
