#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

class QPushButton;
class QTextEdit;
class QLabel;

class Editor: public QWidget {
	Q_OBJECT

	public: 
		explicit Editor(QWidget *parent = 0);

	private:
		QTextEdit *input;
		QPushButton *save;
		QPushButton *prev;
		QPushButton *next;
		QLabel *image;

	private slots:
		void saveClicked();
		void prevClicked();
		void nextClicked();

};

#endif
