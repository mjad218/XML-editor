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

void SyntaxHighlighter::highlightBlock(const QString& text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::green);

    QRegularExpression expression("<");
    QRegularExpressionMatchIterator i = expression.globalMatch(text);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        setFormat(match.capturedStart(), match.capturedLength(), myClassFormat);
    }
	highlightErrors(text);
}


// Checking Consistency 
bool SyntaxHighlighter::checkConsistency(std::string tag, std::stack<std::string>& s) {
	if (tag == s.top()) {
		s.pop();
		return true;
	}
	return false;
}

void SyntaxHighlighter::highlightErrors(const QString& text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
	std::string str;
	str = document()->toPlainText().QString::toStdString();;

	std::cout << "str"; 
	std::cout << str; 
	std::stack<std::string> tags;
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
			if (isClosingTag) {
				isClosingTag = false;
				if (!checkConsistency(tagName, tags)) {
					isConsistant = false;
					QTextCharFormat myClassFormat;
					myClassFormat.setFontWeight(QFont::Bold);
					myClassFormat.setForeground(Qt::darkMagenta);
					setFormat(i, 5, myClassFormat);
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

