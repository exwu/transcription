#include <iostream>
#include <QtGui>
#include <QWidget>

#include "editor.h"

using namespace std;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	Editor editor;
	editor.showFullScreen();


	editor.show();

	return app.exec();
}

