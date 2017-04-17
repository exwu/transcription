#include "editor.h"

#include <iostream>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>

Editor::Editor(QWidget *parent) 
	:QWidget(parent) {
		// Initialize the components
		QPixmap *pix = new QPixmap("test.jpg");
		image = new QLabel(this);
		image->setPixmap(*pix);
		image->setScaledContents(true);
		input = new QTextEdit(this);
		save = new QPushButton("save", this);
		save->setGeometry(10, 10, 80, 90);
		prev = new QPushButton("prev", this);
		prev->setGeometry(110, 10, 80, 90);
		next = new QPushButton("next", this);
		next->setGeometry(210, 10, 80, 90);

		// Add handlers
		connect(save, SIGNAL (clicked()), this, SLOT (saveClicked()));
		connect(prev, SIGNAL (clicked()), this, SLOT (prevClicked()));
		connect(next, SIGNAL (clicked()), this, SLOT (nextClicked()));

		// Do layout
		QGridLayout *layout = new QGridLayout;
		layout->setColumnStretch(0, 30);
		layout->setColumnStretch(1, 10);
		layout->setColumnStretch(2, 10);
		layout->setColumnStretch(3, 10);

		layout->addWidget(image, 0, 0, 2, 1);
		layout->addWidget(input, 0, 1, 1, 3);
		layout->addWidget(prev, 1, 1);
		layout->addWidget(save, 1, 2);
		layout->addWidget(next, 1, 3);

		setLayout(layout);

		


}

void Editor::saveClicked() {
	std::cout  << "saved" << std::endl;
	std::cout << input->toPlainText().toStdString() << std::endl;

	QPixmap *pix = new QPixmap("test2.jpg");
	image->setPixmap(*pix);

}

void Editor::prevClicked() {
	std::cout << "back" << std::endl;
}

void Editor::nextClicked() {
	std::cout << "forward" << std::endl;
}
