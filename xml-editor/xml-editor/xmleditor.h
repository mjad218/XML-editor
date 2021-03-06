#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xmleditor.h"
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <string>
#include "SyntaxHighlighter.h"

class xmleditor : public QMainWindow
{
    Q_OBJECT

public:
    xmleditor(QWidget *parent = Q_NULLPTR);
	xmleditor::~xmleditor();

	void New();

	void Open();

	void Save();
	void SaveAs();
	void Exit();
private:
	SyntaxHighlighter* highlighter;

    QPushButton* openFile;
    QPushButton* saveFile;
    QPushButton* compress;
    QWidget* qwidget;
    QVBoxLayout* verticalBox;
    QHBoxLayout* horizontalBox;
    Ui::xmleditorClass ui;
	void init_menubar();
	void init_toolbar();
	void init_statusbar();
	void documentChanged(); 
	void setCurrentFile(QString filename);
	void documntModified();
	bool maybesave();
	void minify();
	bool checkConsistency(std::string tag, std::stack<std::string>& s);
	void makeFileCoonsistent();
	void fixClosingTag(std::string& str, std::string& tag, unsigned int& i, std::stack<std::string>& tags);
	void fixMissingTag(std::string& str, std::string& tag, unsigned int& i, std::stack<std::string>& tags);
	bool hasMissingTag(std::string tag, std::stack<std::string>& s);

	int font_size;

	QMenu* filemenu;
	QMenu* editmenu;
	QMenu* formatmenu;
	QMenu* viewmenu;
	QMenu* helpmenu;
	QMenu* optionsmenu;
	QAction* MinifyAction;

	QAction* NewAction;
	QAction* OpenAction;
	QAction* SaveAction;
	QAction* SaveAsAction;
	QAction* ExitAction;
	QAction* AboutAction;
	QAction* MakeConsistentAction;
	QTextEdit* textarea;
	QToolBar* toolbar;

	QString CurrentFilename;

};
