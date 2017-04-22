#include "editor.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>

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

string formatNumber(int);

Editor::Editor(QWidget *parent) 
	:QWidget(parent) {
		currentPage = -1;

		// Initialize the components
		// LHS
		scene = new QGraphicsScene(this);
		image = new QGraphicsView(scene);
		image->setScene(scene);
		scene->setBackgroundBrush(Qt::gray);
		// Radios
		whitelist = new QGroupBox();
		white = new QRadioButton("white");
		gray = new QRadioButton("gray");
		black = new QRadioButton("black");
		whitelist->setStyleSheet("border:0");
		defaultRadio = white;
		defaultRadio->setChecked(true);
		// Metadata
		metadataGroup = new QGroupBox();
		notes = new QLineEdit();
		notes->setPlaceholderText("Notes");
		pageNumber = new QLineEdit();
		pageNumber->setPlaceholderText("page number");

		// RHS
		fileRead = new QGroupBox();
		fileInput = new QLineEdit();
		fileInput->setPlaceholderText("scan number");
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
		// Radio
		QHBoxLayout *radioBox = new QHBoxLayout;
		radioBox->addWidget(white);
		radioBox->addWidget(gray);
		radioBox->addWidget(black);
		whitelist->setLayout(radioBox);
		//layout->addWidget(whitelist, 2, 2, Qt::AlignRight);
		// Metadata
		QHBoxLayout *metadataBox = new QHBoxLayout;
		metadataBox->addWidget(notes);
		metadataBox->addWidget(pageNumber);
		metadataBox->addWidget(whitelist);
		metadataGroup->setLayout(metadataBox);
		metadataBox->setStretch(0, 1);
		metadataBox->setStretch(1, 0);
		metadataBox->setStretch(1, 0);
		layout->addWidget(metadataGroup, 2, 0, 1, 3);
		
		// RHS
		// File input
		QHBoxLayout *fileBox = new QHBoxLayout;
		fileBox->addWidget(fileInput);
		fileBox->addWidget(loadButton);
		fileBox->setStretch(0, 1);
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

void writeStringToFile(string fileName, string contents) {
	ofstream file;
	file.open(fileName);
	file << contents << endl;
	file.close();
}

void Editor::saveClicked() {
	// Get the directory based on page number
	string dirName = "transcriptions/" + formatNumber(currentPage) + "/";
	DIR *dir = opendir(dirName.c_str());
	if (dir) {
	} else if (ENOENT == errno) {
		// Directory doesn't exist, create it
		mkdir(dirName.c_str(), S_IRWXU | S_IRWXG);
	}
	dir = opendir(dirName.c_str());

	// Write transcription to file
	writeStringToFile(dirName + transcriptionFileName, input->toPlainText().toStdString());
	writeStringToFile(dirName + whitelistFileName, getCheckedRadio());
	writeStringToFile(dirName + pageNumberFileName, pageNumber->text().toStdString());
	writeStringToFile(dirName + notesFileName, notes->text().toStdString());
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
	changePage(currentPage - 1);
}

void Editor::nextClicked() {
	changePage(currentPage + 1);
}

void getAllFiles() {
	DIR *dir;
	class dirent *ent;

	dir = opendir("scans");
	while ((ent = readdir(dir)) != NULL) {
		const string file_name = ent->d_name;
		cout << file_name << endl;
	}
}

string readFile(string fileName) {
	// Read from the file
	ifstream file(fileName.c_str());
	stringstream buffer;
	buffer << file.rdbuf();
	string str = buffer.str();
	return str.substr(0, str.size() - 1);
}

void Editor::loadClicked() {
	changePage(stoi(fileInput->text().toStdString()));
}


string formatNumber(int number) {
	ostringstream str;
	str << setw(4) << setfill('0') << number;
	return str.str();
}

void Editor::changePage(int scanNumber) {
	// Draw the new iamge
	string str = formatNumber(scanNumber);
	string toLoad = "scans/" + str + ".jpg";
	currentPage = scanNumber;
	QPixmap *pix = new QPixmap(toLoad.c_str());
	scene->addPixmap(*pix);
	image->fitInView(pix->rect(), Qt::KeepAspectRatio);

	// Keep the file input in sync
	fileInput->setText(str.c_str());

	// Check to see if we've transcribed it before
	string dirName = "transcriptions/" + formatNumber(currentPage) + "/";
	DIR *dir = opendir(dirName.c_str());
	if (dir) {
		// Read in the old values
		input->setText(QString::fromStdString(readFile(dirName + transcriptionFileName)));
		pageNumber->setText(QString::fromStdString(readFile(dirName + pageNumberFileName)));
		notes->setText(QString::fromStdString(readFile(dirName + notesFileName)));
		string qualityValue = readFile(dirName + whitelistFileName);
		if (qualityValue == "white") {
			white->setChecked(true);
		} else if (qualityValue == "gray") {
			gray->setChecked(true);
		} else if (qualityValue == "black") {
			black->setChecked(true);
		} else {
			cout << "got bad value for whitelist: " << qualityValue << "/" << endl;
		}

	} else if (ENOENT == errno) {
		// Didn't exist, just unset everything
		input->setText("");
		pageNumber->setText("");
		notes->setText("");
		defaultRadio->setChecked(true);
	}
}



