
#include"ui_LaboratorPooGraphicInterface.h"
#include <QtWidgets/QApplication>
#include <stdlib.h>
#include <crtdbg.h> 
#include "qlabel.h"
#include "domain.h"
#include "repository.h"
#include "service.h"
#include "UI.h"
#include "Validator.h"
#include"gui.h"
#include <QtWidgets/qpushbutton.h>

void TestAll() {

	TesteDomain();
	TesteRepo();
	TesteRepofile();
	TesteExceptionRepo();
	TesteSrv();
	TestValidator();
	TesteListaNotificare();
	

}


int main(int argc, char *argv[])
{

	TestAll();
	
    QApplication a(argc, argv);

	RepoFile repo{"C:\\Users\\Alexandra\\VisualStudio Projects\\LaboratorPooGraphicInterface\\fisier.txt"};
	Service srv{ repo };
	Product gui{ srv };
	gui.show();
    return a.exec();
}







