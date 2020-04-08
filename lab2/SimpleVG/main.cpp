#include "SimpleVG.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimpleVG w;
	w.show();
	return a.exec();
}
