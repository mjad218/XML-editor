#include <stack>
#include "SyntaxHighlighter.h"
#include <QRegularExpression>
#include <iostream>
SyntaxHighlighter::SyntaxHighlighter(QObject* parent) :
    QSyntaxHighlighter(parent)
{
}

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) :
    QSyntaxHighlighter(parent)
{
}

// Checking Consistency 
bool SyntaxHighlighter::checkConsistency(std::string tag, std::stack<std::string>& s) {
	if (!s.empty()) {
		std::string str = s.top();
		if (!(tag == str)) {
			// s.push(str);
			s.pop();
			return false;
		}
		else {
			s.pop();
			return true;
		}
	}
}

void SyntaxHighlighter::highlightBlock(const QString& text)
{
    //QTextCharFormat tagFormat;
	//tagFormat.setForeground(Qt::blue);
	//std::string str = this->document()->toPlainText().toStdString();;
	//setFormat(i - tagName.length(), i - 2, tagFormat);
	highlightErrors(text);
}

void SyntaxHighlighter::highlightErrors(const QString& str) {

	std::string tagName;
	bool isClosingTag = false;
	for (unsigned int i = 0; i < str.length(); i++) {
		switch (str.at(i).toLatin1()) {
		case '<':
			tagName = "";
			break;
		case ' ':
			break;
		case '>':
			if (isClosingTag) {
				isClosingTag = false;
				if (!checkConsistency(tagName, tags)) {
					QTextCharFormat errorFormat;
					//errorFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
					errorFormat.setForeground(Qt::red);
					setFormat(i - tagName.length(), i, errorFormat);
				}
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
			tagName += str.at(i).toLatin1();
		}

	}
}
