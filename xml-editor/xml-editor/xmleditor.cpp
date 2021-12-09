#include "xmleditor.h"
xmleditor::xmleditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    openFile = new QPushButton( "Open File", this);
}
