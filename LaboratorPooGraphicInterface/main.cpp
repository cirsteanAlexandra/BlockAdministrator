#include "LaboratorPooGraphicInterface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LaboratorPooGraphicInterface w;
    w.show();
    return a.exec();
}
