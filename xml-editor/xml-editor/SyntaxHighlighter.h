#pragma once
#include <stack>
#include <qsyntaxhighlighter.h>
#include <QObject>
#include <QTextDocument>
#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QObject* parent = nullptr);
    SyntaxHighlighter(QTextDocument* parent);

protected:
    std::stack<std::string> tags;
    void highlightErrors(const QString& str);
    void highlightBlock(const QString& text);
    bool checkConsistency(std::string tag, std::stack<std::string>& s);
};
