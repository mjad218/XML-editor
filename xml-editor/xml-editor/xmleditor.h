#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xmleditor.h"
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
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
    QPushButton* openFile;
    QPushButton* saveFile;
    QPushButton* compress;
    QWidget* qwidget;
    QVBoxLayout* verticalBox;
    QHBoxLayout* horizontalBox;
    QPlainTextEdit* xmlText; 
    Ui::xmleditorClass ui;
	void init_menubar();
	void init_toolbar();
	void init_statusbar();

	void setCurrentFile(QString filename);
	void documntModified();
	bool maybesave();


	int font_size;

	QMenu* filemenu;
	QMenu* editmenu;
	QMenu* formatmenu;
	QMenu* viewmenu;
	QMenu* helpmenu;

	QAction* NewAction;
	QAction* OpenAction;
	QAction* SaveAction;
	QAction* SaveAsAction;
	QAction* ExitAction;
	QAction* AboutAction;

	QPlainTextEdit* textarea;
	QToolBar* toolbar;

	QString CurrentFilename;

};
