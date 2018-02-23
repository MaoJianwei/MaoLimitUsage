#include "LimitUsageGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LimitUsageGUI w;
	w.showMinimized();
	return a.exec();
}
