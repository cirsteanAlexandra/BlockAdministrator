#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LaboratorPooGraphicInterface.h"

class LaboratorPooGraphicInterface : public QMainWindow
{
    Q_OBJECT

public:
    LaboratorPooGraphicInterface(QWidget *parent = Q_NULLPTR);

private:
    Ui::LaboratorPooGraphicInterfaceClass ui;
};
