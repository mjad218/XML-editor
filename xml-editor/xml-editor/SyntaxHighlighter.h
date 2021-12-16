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
    //QTextDocument* document() const; 
    //void setDocument(QTextDocument* doc);

protected:
    void highlightBlock(const QString& text);
    void highlightErrors(const QString& text);
    bool checkConsistency(std::string tag, std::stack<std::string>& s);

    //void setFormat(int start, int count, const QColor& color);

};
