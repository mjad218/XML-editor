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
	int font_size;



	QMenu* filemenu;
	QMenu* editmenu;
	QMenu* formatmenu;
	QMenu* viewmenu;
	QMenu* helpmenu;


	QPlainTextEdit* textarea;
	QToolBar* toolbar;
};
