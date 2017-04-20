#include "editor.h"
#include <iostream>
#include <fstream>
#include <dirent.h>

#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGraphicsScene>

using namespace std;

Editor::Editor(QWidget *parent) 
	:QWidget(parent) {
		// Initialize the components
		// LHS
		scene = new QGraphicsScene(this);
		image = new QGraphicsView(scene);
		image->setScene(scene);
		image->setDragMode(QGraphicsView::RubberBandDrag);
		scene->setBackgroundBrush(Qt::gray);
		// Image cropping
		saveCrop = new QPushButton("save crop", this);
		toggleCrop = new QPushButton("view crop", this);
		toggleCrop->setCheckable(true);
		// Radios
		whitelist = new QGroupBox();
		white = new QRadioButton("white");
		gray = new QRadioButton("gray");
		black = new QRadioButton("black");
		whitelist->setStyleSheet("border:0");
		defaultRadio = white;
		defaultRadio->setChecked(true);

		// RHS
		fileRead = new QGroupBox();
		fileInput = new QLineEdit();
		loadButton = new QPushButton("load");

		input = new QTextEdit(this);
		// Buttons
		save = new QPushButton("save", this);
		prev = new QPushButton("prev", this);
		next = new QPushButton("next", this);

		// Add handlers
		connect(save, SIGNAL (clicked()), this, SLOT (saveClicked()));
		connect(prev, SIGNAL (clicked()), this, SLOT (prevClicked()));
		connect(next, SIGNAL (clicked()), this, SLOT (nextClicked()));
		connect(loadButton, SIGNAL (clicked()), this, SLOT (loadClicked()));

		// Do layout
		QGridLayout *layout = new QGridLayout;
		layout->setColumnStretch(0, 10);
		layout->setColumnStretch(1, 10);
		layout->setColumnStretch(2, 10);
		layout->setColumnStretch(3, 10);
		layout->setColumnStretch(4, 10);
		layout->setColumnStretch(5, 10);
		// LHS
		// Image
		layout->addWidget(image, 0, 0, 2, 3);
		// Cropping
		layout->addWidget(saveCrop, 2, 0);
		layout->addWidget(toggleCrop, 2, 1);
		// Radio
		QHBoxLayout *radioBox = new QHBoxLayout;
		radioBox->addWidget(white);
		radioBox->addWidget(gray);
		radioBox->addWidget(black);
		whitelist->setLayout(radioBox);
		layout->addWidget(whitelist, 2, 2, Qt::AlignRight);
		
		// RHS
		// File input
		QHBoxLayout *fileBox = new QHBoxLayout;
		fileBox->addWidget(fileInput);
		fileBox->addWidget(loadButton);
		fileBox->setStretch(0, 1);
		fileBox->setStretch(1, 0);
		fileRead->setLayout(fileBox);
		layout->addWidget(fileRead, 0, 3, 1, 3);
		// Text Editor
		layout->addWidget(input, 1, 3, 1, 3);
		// Buttons
		layout->addWidget(prev, 2, 3);
		layout->addWidget(save, 2, 4);
		layout->addWidget(next, 2, 5);

		setLayout(layout);

}

void Editor::saveClicked() {
	cout << input->toPlainText().toStdString() << endl;

	// Write image to file
	ofstream file;
	file.open("test.txt");

	file << input->toPlainText().toStdString() << endl;
	file.close();

	cout << getCheckedRadio() << endl;
}

string Editor::getCheckedRadio() {
	if (white->isChecked()) {
		return "white";
	} 
	if (gray->isChecked()) {
		return "gray";
	} 
	if (black->isChecked()) {
		return "black";
	} 
	return "";
}

void Editor::prevClicked() {
}

void Editor::nextClicked() {
	loadFile("input_test.txt");
}

void getAllFiles() {
	DIR *dir;
	class dirent *ent;

	dir = opendir("scans");
	cout << "hi" << endl;
	while ((ent = readdir(dir)) != NULL) {
		const string file_name = ent->d_name;
		cout << file_name << endl;
	}
}

void Editor::loadFile(string fileName) {
	// Read from the file
	ifstream file(fileName.c_str());
	string s = "";
	for (string line; getline(file, line); ) {
		s.append(line).append("\n");
	}
	input->setText(QString::fromStdString(s));
	// Reset the radio buttons
	defaultRadio->setChecked(true);


}

void Editor::loadClicked() {
	QPixmap *pix = new QPixmap("scans/0000.jpg");
	scene->addPixmap(*pix);
	image->fitInView(pix->rect(), Qt::KeepAspectRatio);
}
