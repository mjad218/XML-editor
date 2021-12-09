#include "xmleditor.h"
#include <QLabel>
xmleditor::xmleditor(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("XML Editor");
    ui.setupUi(this);
    openFile = new QPushButton("Open File");
    saveFile = new QPushButton("Save File");
    xmlText = new QPlainTextEdit("type xml");
    setCentralWidget(xmlText);
	init_menubar();

	init_statusbar();

	init_toolbar();
}
xmleditor::~xmleditor()
{

}

void xmleditor::init_menubar()
{
	filemenu = menuBar()->addMenu("File");
	editmenu = menuBar()->addMenu("Edit");
	formatmenu = menuBar()->addMenu("Format");
	viewmenu = menuBar()->addMenu("View");
	helpmenu = menuBar()->addMenu("Help");
}

void xmleditor::init_toolbar()
{
	toolbar = new QToolBar();
	toolbar->addAction(QIcon(), "New");
	toolbar->addAction(QIcon(), "Open");
	toolbar->addAction(QIcon(), "Save");
	toolbar->addAction(QIcon(), "Save As");
	toolbar->addAction(QIcon(), "Print");
	toolbar->addAction(QIcon(), "Copy");
	toolbar->addAction(QIcon(), "Cut");
	toolbar->addAction(QIcon(), "Paste");

	addToolBar(toolbar);

}

void xmleditor::init_statusbar()
{
	statusBar()->addPermanentWidget(new QLabel(""));
	statusBar()->addPermanentWidget(new QLabel(tr("%1 %").arg(font_size)));

}

