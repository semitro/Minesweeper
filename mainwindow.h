#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "logic.h"
#include "render.h"
#include "mainwindow.h"
#include <qapplication.h>
//#define WINDOW_WIDTH  640 //N_X*BLOCK_SIZE
//#define WINDOW_HEIGHT 640 //N_Y*BLOCK_SIZE
//#define WINDOW_WIDTH map.getSize()*BLOCK_RENDER_SIZE
//#define WINDOW_HEIGHT map.getSize()*BLOCK_RENDER_SIZE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_pushButton_start_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
