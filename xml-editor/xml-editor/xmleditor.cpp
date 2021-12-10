#include "xmleditor.h"
#include <QLabel>
#include <QShortcut>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QGuiApplication>
#include <QSaveFile>

xmleditor::xmleditor(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("XML Editor");
    ui.setupUi(this);
	textarea = new QPlainTextEdit();
	setCentralWidget(textarea);

	init_menubar();

	init_statusbar();

	init_toolbar();

	QFont font;
	//font.setFamily("Courier");
	//textarea->setFont(font);

	//textarea->zoomIn(font_size);

	connect(NewAction, &QAction::triggered, this, &xmleditor::New);
	connect(OpenAction, &QAction::triggered, this, &xmleditor::Open);
	connect(SaveAction, &QAction::triggered, this, &xmleditor::Save);
	connect(SaveAsAction, &QAction::triggered, this, &xmleditor::SaveAs);
	connect(MinifyAction, &QAction::triggered, this, &xmleditor::minify);

	connect(textarea->document(), &QTextDocument::contentsChanged, this, &xmleditor::documntModified);
	connect(textarea->document(), &QTextDocument::contentsChanged, this, &xmleditor::documentChanged);


	setCurrentFile(QString());


}
xmleditor::~xmleditor()
{

}
// Checking Consistency 
bool xmleditor::checkConsistency(std::string tag , std::stack<std::string>& s) {
	if (tag == s.top()) {
		s.pop();
		return true;
	}
	return false;
}

void xmleditor::documentChanged() {
	std::string str;
	str = this->textarea->document()->toPlainText().toStdString();
	std::stack<std::string> tags;
	std::string tagName;

	bool isClosingTag = false;
	bool isConsistant = true;

	for (unsigned int i = 0; i < str.length(); i++) {
		// if(!isConsistant){
		//    break;
		// }
		switch (str[i]) {
		case '<':
			tagName = "";
			break;
		case ' ':
			break;

		case '>':
			if (isClosingTag) {
				if (!checkConsistency(tagName, tags)) {
					isConsistant = false;
				}
				isClosingTag = false;
			}
			else {
				tags.push(tagName);
				tagName = "";
			}

			break;
		case '/':
			/*  if(sti[i+1]=='>'){
				 tags.push(tagName);
				 tags.push(tagName);
			  }
			  if(sti[i-1]=='<'){
				 tags.push(tagName);
			  }*/
			isClosingTag = true;

			break;
		default:
			tagName += str[i];

		}
	}

	if (isConsistant) {
		QMessageBox::information(this, "Info", "is Consistant");
	}
	else {
		QMessageBox::information(this, "Info", "not Consistant");
	}
}


// minify xml 


void xmleditor::minify() {
	std::string str;
	str = this->textarea->document()->toPlainText().toStdString();
	std::string strout;
	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '\n' || str[i] == ' ') {
			continue;
		}
		strout += str[i];
	}
	this->textarea->document()->setPlainText(QString::fromStdString(strout));
}
void xmleditor::init_menubar()
{
	filemenu = menuBar()->addMenu("File");
	{
		NewAction = new QAction(QIcon(":/icons/new.png"), "New");
		NewAction->setShortcut(QKeySequence::New);
		NewAction->setStatusTip("Create new File");
		filemenu->addAction(NewAction);

		OpenAction = new QAction(QIcon(":/icons/open.png"), "Open");
		OpenAction->setShortcut(QKeySequence::Open);
		OpenAction->setStatusTip("open exist File");
		filemenu->addAction(OpenAction);


		SaveAction = new QAction(QIcon(":/icons/save.png"), "Save");
		SaveAction->setShortcut(QKeySequence::Save);
		SaveAction->setStatusTip("save File");
		filemenu->addAction(SaveAction);

		SaveAsAction = new QAction(QIcon(":/icons/save-as.png"), "Save As");
		//SaveAsAction->setShortcut(QKeySequence::SaveAs); not working
		SaveAsAction->setShortcut(tr("Ctrl+Shift+S"));
		SaveAsAction->setStatusTip("save file as new format");
		filemenu->addAction(SaveAsAction);

		filemenu->addSeparator();
		ExitAction = new QAction(QIcon(":/icons/exit.png"), "Exit");
		ExitAction->setShortcut(tr("Ctrl+Q"));
		ExitAction->setStatusTip("exit program");
		filemenu->addAction(ExitAction);
	}

	optionsmenu = menuBar()->addMenu("Options");
	{
		MinifyAction = new QAction(QIcon(":/icons/minify.png"), "Minify");
		MinifyAction->setStatusTip("Minify XML");
		optionsmenu->addAction(MinifyAction);
	}

	helpmenu = menuBar()->addMenu("Help");
	{
		AboutAction = new QAction(QIcon(":/icons/help.png"), "help");
		AboutAction->setStatusTip("about us");
		helpmenu->addAction(AboutAction);
	}


}

void xmleditor::init_toolbar()
{
	toolbar = new QToolBar();
	toolbar->addAction(NewAction);
	toolbar->addAction(OpenAction);
	toolbar->addAction(SaveAction);
	toolbar->addAction(SaveAsAction);

	addToolBar(toolbar);

}

void xmleditor::init_statusbar()
{
	statusBar()->addPermanentWidget(new QLabel(""));
	statusBar()->addPermanentWidget(new QLabel(tr("%1 %").arg(font_size)));
}


/////////////////////////////////////////////////// helpers

void xmleditor::setCurrentFile(QString filename)
{
	CurrentFilename = filename;
	textarea->document()->setModified(false);

	setWindowModified(false);

	QString showname = CurrentFilename;

	if (CurrentFilename.isEmpty())
		showname = "untitled.txt";

	setWindowFilePath(showname);
}

void xmleditor::documntModified()
{
	setWindowModified(textarea->document()->isModified());
}


bool xmleditor::maybesave()
{
	if (!textarea->document()->isModified())
		return true;

	auto ret = QMessageBox::warning(this, "Warning", "the document is modified \n do you want to save ? ",
		QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

	switch (ret)
	{
	case QMessageBox::Save:
		Save();
		break;
	case QMessageBox::Cancel:
		return false;
		break;
	case QMessageBox::Discard:
		break;
	default:
		break;
	}

	return true;
}

///////////////////////////////////////////////////// Functions

void xmleditor::New()
{
	if (maybesave())
	{
		textarea->clear();
		setCurrentFile(QString());
	}
}

void xmleditor::Open()
{
	if (maybesave())
	{
		CurrentFilename = QFileDialog::getOpenFileName(this);

		if (!CurrentFilename.isEmpty())
		{
			setCurrentFile(CurrentFilename);

			QFile file(CurrentFilename);

			if (!file.open(QFile::ReadOnly | QFile::Text))
			{
				QMessageBox::warning(this, "Warning", "erorr loading file");
			}

			QTextStream in(&file);

			QGuiApplication::setOverrideCursor(Qt::WaitCursor);
			textarea->document()->setPlainText(in.readAll());
			QGuiApplication::restoreOverrideCursor();
		}
	}
}

void xmleditor::Save()
{
	if (CurrentFilename.isEmpty())
	{
		SaveAs();
	}
	else
	{
		QGuiApplication::setOverrideCursor(Qt::WaitCursor);

		QSaveFile file(CurrentFilename);

		if (file.open(QFile::WriteOnly | QFile::Text))
		{
			QTextStream out(&file);
			out << textarea->document()->toPlainText();

			if (!file.commit())
			{
				QMessageBox::warning(this, "warning", "error in saving file");
			}

		}
		else
		{
			QMessageBox::warning(this, "warning", "error in open file");
		}

		QGuiApplication::restoreOverrideCursor();
		setCurrentFile(CurrentFilename);
		statusBar()->showMessage("file saved", 2000);
	}
}

void xmleditor::SaveAs()
{
	QFileDialog dialog(this);

	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);

	if (dialog.exec() != QDialog::Accepted)
	{
		// erorr
	}
	else
	{
		CurrentFilename = dialog.selectedFiles().first();
		setCurrentFile(CurrentFilename);
		Save();
	}
}

void xmleditor::Exit()
{
}
