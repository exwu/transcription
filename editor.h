#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

class QPushButton;
class QRadioButton;
class QGroupBox;
class QTextEdit;
class QLabel;
class QGraphicsView;
class QGraphicsScene;
class QLineEdit;

class Editor: public QWidget {
	Q_OBJECT

	public: 
		explicit Editor(QWidget *parent = 0);

	private:

		QGroupBox *fileRead; 
		QLineEdit *fileInput;
		QPushButton *loadButton;

		QTextEdit *input;
		QPushButton *save;
		QPushButton *prev;
		QPushButton *next;
		QGraphicsView *image;
		QGraphicsScene *scene;

		QGroupBox *whitelist;
		QRadioButton *white;
		QRadioButton *gray;
		QRadioButton *black;
		QRadioButton *defaultRadio;

		std::string getCheckedRadio();

		void loadFile(std::string);

	private slots:
		void saveClicked();
		void prevClicked();
		void nextClicked();
		void loadClicked();

};

#endif
