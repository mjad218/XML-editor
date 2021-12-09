#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_xmleditor.h"

class xmleditor : public QMainWindow
{
    Q_OBJECT

public:
    xmleditor(QWidget *parent = Q_NULLPTR);

private:
    Ui::xmleditorClass ui;
};
