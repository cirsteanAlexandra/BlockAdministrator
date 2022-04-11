#include <QtWidgets/QApplication>
#include "service.h"
#include<iostream>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <qlineedit.h>
#include<assert.h>
#include<qlabel.h>
#include<qlineedit.h>
#include<qformlayout.h>
#include<qlistwidget.h>
#include<qcombobox.h>
#include"MyModel.h"
#include<qtableview.h>
#include<qmessagebox.h>
class Product : public QWidget
{
public:
    Service& srv;
    Product(Service& srv) :srv{ srv } {
        initGUI();
        initConect();
        refresh();
    }

    MyModel* lst1 = new MyModel();
    QTableView* retetaList = new QTableView();
    QPushButton* btAdd = new QPushButton{ "&Add" };
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtApr = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtSpr = new QLineEdit;

    QComboBox* box = new QComboBox;

    void initGUI()
    {
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);
        auto stgly2 = new QVBoxLayout;
        retetaList->setModel(lst1);
        stgly2->addWidget(retetaList);

        stgly2->addWidget(box);

        lyMain->addLayout(stgly2);

        auto stgly = new QVBoxLayout;
        auto formLy = new QFormLayout;
        formLy->addRow("Apartament", txtApr);
        formLy->addRow("Nume", txtNume);
        formLy->addRow("Suprafata", txtSpr);
        formLy->addRow("Tip", txtTip);
        stgly->addWidget(btAdd);
        stgly->addLayout(formLy);
        lyMain->addLayout(stgly);

     }

    void initConect() {
        QObject::connect(btAdd, &QPushButton::clicked, this, &Product::addL);
   }

    void addL() {
        try {
            srv.Add(txtApr->text().toInt(), txtNume->text().toStdString(), txtSpr->text().toDouble(), txtTip->text().toStdString());
            refresh();
        }
        catch (ValidateException& err) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));
        }
    }


    void addInCombo(const std::vector<Locatar>& locatari) {


        for (auto& x : locatari)

            box->addItem(QString::fromStdString(x.GetNume()));
    }

    void refresh() {

        addInCombo(srv.GetAll());
        lst1->setProduse(srv.GetAll());
    }

};