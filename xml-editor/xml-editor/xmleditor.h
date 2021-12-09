#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xmleditor.h"
#include <qpushbutton.h>

class xmleditor : public QMainWindow
{
    Q_OBJECT

public:
    xmleditor(QWidget *parent = Q_NULLPTR);

private:
    QPushButton* openFile; 
    Ui::xmleditorClass ui;
};
