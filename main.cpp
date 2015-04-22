#include "mainwindow.h"
#include <qapplication.h>
using namespace sf;

int main(int argc,char **argv){
	QApplication app(argc,argv);
		MainWindow mainWindow;
		mainWindow.show();
	return app.exec();
}
