#include "xmleditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    xmleditor w;
    w.show();
    return a.exec();
}