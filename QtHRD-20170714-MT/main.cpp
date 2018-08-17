#include "mirror.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Mirror*m = new Mirror();
	m->MultiThreadHRD();
	return a.exec();
}