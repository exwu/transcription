#include <iostream>
#include <QtGui>
#include <QWidget>

#include "editor.h"

using namespace std;

int main(int argc, char **argv) {
	std::cout << "Hello, world!" << endl;

	QApplication app(argc, argv);

	Editor editor;
	editor.resize(600, 800);

	editor.show();

	return app.exec();
}

