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
class QPointF;
class QRect;

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
		void changePage(int);

		QGroupBox *metadataGroup;
		QLineEdit *notes;
		QLineEdit *pageNumber;

		int currentPage;

		void loadFile(std::string);

		void writeEverythingToFile();

		std::string transcriptionFileName = "transcription.txt";
		std::string whitelistFileName = "quality";
		std::string pageNumberFileName = "page_number";
		std::string notesFileName = "notes";

	private slots:
		void saveClicked();
		void prevClicked();
		void nextClicked();
		void loadClicked();

};

#endif
