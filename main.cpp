#include "./mainwindow/mainwindow.h"
#include "./app/application.h"

int main(int argc, char *argv[])
{
	dia::Application app(argc, argv);
	dia::MainWindow  win;
	win.show();
	return app.exec();
}
