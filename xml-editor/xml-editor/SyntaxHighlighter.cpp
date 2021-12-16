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
	if (tag == s.top()) {
		s.pop();
		return true;
	}
	return false;
}

void SyntaxHighlighter::highlightBlock(const QString& text)
{
    QTextCharFormat tagFormat;
	tagFormat.setForeground(Qt::blue);
	std::string str = text.QString::toStdString();
	std::string tagName;
	bool isClosingTag = false;
	bool isConsistant = true;
	std::string styledXML;
	for (unsigned int i = 0; i < str.length(); i++) {
		switch (str[i]) {
		case '<':
			tagName = "";
			break;
		case ' ':
			break;
		case '>':
			setFormat(i - tagName.length(), i - 2, tagFormat);
			if (isClosingTag) {
				isClosingTag = false;
				if (!checkConsistency(tagName, tags)) {
					isConsistant = false;
					QTextCharFormat errorFormat;
					errorFormat.setForeground(Qt::red);
					setFormat(i - tagName.length(),  i, errorFormat);
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
			tagName += str[i];
		}
	}
}