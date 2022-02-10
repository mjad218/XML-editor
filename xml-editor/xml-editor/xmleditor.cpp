#include "xmleditor.h"
#include <QLabel>
#include <QShortcut>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QGuiApplication>
#include <QSaveFile>
#include <iostream>
#include <QSyntaxHighlighter>

xmleditor::xmleditor(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("XML Editor");
    ui.setupUi(this);
	textarea = new QTextEdit();
	textarea->setPlaceholderText(QString("Write xml..."));
	setCentralWidget(textarea);
	highlighter = new SyntaxHighlighter(textarea);

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
	connect(MakeConsistentAction, &QAction::triggered, this, &xmleditor::makeFileCoonsistent);

	connect(textarea->document(), &QTextDocument::contentsChanged, this, &xmleditor::documntModified);

	setCurrentFile(QString());


}
xmleditor::~xmleditor()
{

}
// minify xml
void xmleditor::minify() {
	std::string str;
	str = this->textarea->document()->toPlainText().toStdString();
	std::string strout;
	bool isContent = false;

	for (unsigned int i = 0; i < str.length(); i++) {
		if (str[i] == '\n' || str[i] == ' ' || str[i] == '\t') {
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

		MakeConsistentAction = new QAction(QIcon(":/icons/fix.png"), "Make Consistent");
		MakeConsistentAction->setStatusTip("Make Consistent");
		optionsmenu->addAction(MakeConsistentAction);

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
	toolbar->addAction(MakeConsistentAction);

	addToolBar(toolbar);

}

void xmleditor::init_statusbar()
{
	statusBar()->addPermanentWidget(new QLabel(""));
	statusBar()->addPermanentWidget(new QLabel(tr("%1 %").arg(font_size)));
}
// Checking Consistency 
bool xmleditor::checkConsistency(std::string tag , std::stack<std::string>& s) {
	if (tag == s.top()) {
		s.pop();
		return true;
	}
	return false;
}
bool xmleditor::hasMissingTag(std::string tag, std::stack<std::string>& s) {
	std::string firstInStack = s.top(); 
	s.pop();
	if (tag == ( s.top()[0] == '/' ? s.top().substr(1) : s.top() )) {
		s.push(firstInStack);
		return true;
	}
	s.push(firstInStack);
	return false;
}
void xmleditor::fixClosingTag(std::string& str, std::string& tag,unsigned int& i, std::stack<std::string>& tags) {
	int startOfClosingTag = i - tags.top().length() - 2;
	int endOfClosingTag = startOfClosingTag + tags.top().length() + 2;
	tags.pop(); // pop the not correct tag
	str = str.substr(0 , startOfClosingTag) + "</" + tags.top() + str.substr(endOfClosingTag, str.length()) + ">";
	if (!tags.empty()) {
		if (tags.top().length() + 1 < str.length())
			i += tags.top().length() + 1;
		tags.pop();
	}
}

void xmleditor::fixMissingTag(std::string& str, std::string& tag, unsigned int& i, std::stack<std::string>& tags) {	
	std::string TagWithError = tags.top();

	if (TagWithError[0] == '/') {

		int startOfTag, k = i; 
		while (true) {
			k = str.std::string::rfind(("<" + TagWithError + ">").c_str(), k);
			int m = str.std::string::find(("<" + TagWithError.substr(1) + ">").c_str(), k);
			if (str.std::string::rfind(("<" + TagWithError.substr(1) + ">").c_str(), k - 1) == -1 && k > 0) {
				startOfTag == k;
				break;
			}
			startOfTag == k;
		}
		TagWithError = TagWithError.substr(1);
		int beforeStartOfNextTag = str.std::string::rfind('>', startOfTag);
		str = str.substr(0, beforeStartOfNextTag + 1) + "<" + TagWithError + ">" + str.substr(beforeStartOfNextTag + 1, str.length());
		if (!tags.empty()) {
			if (tags.top().length() + 1 < str.length())
				i -= TagWithError.length() - 3;
			tags.pop();
		}
	}
	else {
		int startOfTag = str.std::string::rfind(("<" + TagWithError + ">").c_str(), i);

		int beforeStartOfNextTag = str.std::string::find('<', startOfTag);
		str = str.substr(0, beforeStartOfNextTag) + "</" + TagWithError + ">" + str.substr(beforeStartOfNextTag, str.length());
		if (!tags.empty()) {
			if (tags.top().length() + 1 < str.length())
				i -= TagWithError.length() - 3;
			tags.pop();
		}
	}
}

void xmleditor::makeFileCoonsistent() {
	std::string str = this->textarea->document()->toPlainText().toStdString();
	std::stack<std::string> tags;
	std::string tagName;
	bool isClosingTag = false;
	bool isConsistant = false;

	while (!isConsistant) {
		for (unsigned int i = 0; i < str.length(); i++) {
			switch (str[i]) {
			case '<':
				tagName = "";
				break;
			case '\t':
				break;
			case ' ':
				break;
			case '>':
				if (isClosingTag) {
					if (!checkConsistency((tagName[0] == '/' ? tagName.substr(1) : tagName), tags)) {
						if (hasMissingTag( ( tagName[0] == '/' ?tagName.substr(1) : tagName), tags)) {
							fixMissingTag(str, tags.top(), i, tags);
						}
						else {
							tags.push( "/" + tagName);
							//fixClosingTag(str, tags.top(), i, tags);
						}
						isConsistant = true;
					}
					else {
						isConsistant = true;
					}
					isClosingTag = false;
				}
				else {
					tags.push(tagName);
					tagName = "";
				}
				break;
			case '/':
				isClosingTag = true;
				break;
			default:
				tagName += str[i];
			}
		}
	}
	this->textarea->document()->setPlainText(QString::fromStdString(str));
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
