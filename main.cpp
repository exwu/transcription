#include <iostream>
#include <QtGui>
#include <QWidget>

using namespace std;

int main(int argc, char **argv) {
	std::cout << "Hello, world!" << endl;

	QApplication app(argc, argv);

	return app.exec();
}

