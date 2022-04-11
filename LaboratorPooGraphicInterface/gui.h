
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
#include<string>
#include<qmessagebox.h>
#include "service.h"
#include<vector>
#include<qtablewidget.h>
#include<qtableview.h>
#include <QColor>
#include <QPainter>
#include<qbrush.h>
#include<qspinbox.h>
#include<qcombobox.h>
#include<qslider.h>
#include<qradiobutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qcombobox.h>
#include<qwidget.h>
#include<qpainter.h>
#include"MyModel.h"


class Observer {
public:
    virtual void update() = 0;
};

class Cos : public Observer {
    Service& srv;
    QWidget* wid1 = new QWidget;
    QVBoxLayout* cos = new QVBoxLayout();
    QListWidget* lst = new QListWidget;
    int nrLinii = 0;
    int nrColoane = 4;

    QTableWidget* tbl = new QTableWidget(nrLinii, nrColoane, nullptr);
    
    QPushButton* btAddC = new QPushButton{ "Adauga lista" };
    QPushButton* btGenerC = new QPushButton{ "Generare lista" };
    QPushButton* btGolireC = new QPushButton{ "Golire lista" };
   

    QLineEdit* txtA = new QLineEdit;
    QLineEdit* txtB = new QLineEdit;
    std::vector<Observer*>& observers;
    int k = 0;

public:
    Cos(Service& srv, std::vector<Observer*>& observers, int k) : srv{ srv }, observers{ observers }, k{ k } {
        connect();
        wid1->setLayout(cos);
        if (k == 1)
            cos->addWidget(lst);
        else cos->addWidget(tbl);
        auto f = new QHBoxLayout;
        f->addWidget(btAddC);
        f->addWidget(txtA);
        cos->addLayout(f);
        auto g = new QHBoxLayout;
        g->addWidget(btGenerC);
        g->addWidget(txtB);
        cos->addLayout(g);
        cos->addWidget(btGolireC);
        update();
        wid1->show();
    }
    void connect() {

        QObject::connect(btGolireC, &QPushButton::clicked, [&]() {
            
            srv.Delete();
            notifyObservers();
             });

        QObject::connect(btAddC, &QPushButton::clicked, [&]() {
            
            try { srv.AddNotificare(txtA->text().toInt());
            }
            catch (ValidateException& err) {
             
                
               QMessageBox::warning(NULL, "Warning", QString::fromStdString(err.GetMessages()[0]));
            }
            notifyObservers();
            
            });

        QObject::connect(btGenerC, &QPushButton::clicked, [&]() {
            

            if (txtB->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
            if (txtB->text().toInt() > srv.GetAll().size() && txtB->text().toInt() < 0) QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul invalid!"));
            if (txtB->text().toInt() > srv.GetAll().size() - srv.GetAllNotificare().size()) QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul invalid!"));
            else {
                srv.random(txtB->text().toInt());
                notifyObservers();
            }
            });

        

        }

    void update() override {

        tbl->clear();


        int c = 0;
        for (auto& x : srv.GetAllNotificare()) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(x.GetNume()));
            QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(x.GetApartament()));
            QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(x.GetSuprafata()));
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(x.GetTip()));
            tbl->insertRow(c);

            tbl->setItem(c, 0, item);
            tbl->setItem(c, 1, item1);
            tbl->setItem(c, 2, item2);
            tbl->setItem(c, 3, item3);
            c++;
        }


        lst->clear();

        for (const auto& l : srv.GetAllNotificare()) {
            QListWidgetItem* item2 = new QListWidgetItem(QString::fromStdString(l.GetNume()));
            item2->setData(Qt::UserRole, QString::number(l.GetApartament()));
            lst->addItem(item2);
        }


        
    }

    void notifyObservers() {
        for (auto& o : observers)
            o->update();
    }

};


class CosGUIRO : public Observer, public QWidget {
    QVBoxLayout* retetaLayout = new QVBoxLayout();
    Service& srv;
    std::vector<Observer*>& observers;
public:
    CosGUIRO(Service& srv, std::vector<Observer*>& observers) : srv{ srv }, observers{ observers } {
        this->setLayout(retetaLayout);
        this->setFixedHeight(512);
        this->setFixedWidth(512);
        update();
        this->show();
    }
    void paintEvent(QPaintEvent* ev) override {
        QPainter p{ this };
        int x = 20;
        int y = 21;
        int k = 22;
        int z = 23;
        int n = srv.GetAllNotificare().size();
        for (int i = 0; i < n; i++) {


             p.drawEllipse(x, y, z, k);
            k++;
            z++;
            x = x + 10; y++;
            int frameNo = 0;
            bool floatBased = false;
            
            for (int diameter = 0; diameter < 256; diameter += 9) {
                int delta = abs((frameNo % 128) - diameter / 2);
                int alpha = 255 - (delta * delta) / 4 - diameter;
                if (alpha > 0) {
                    p.setPen(QPen(QColor(0, diameter / 2, 127, alpha), 3));

                    if (floatBased)
                        p.drawEllipse(QRectF(-diameter / 2.0, -diameter / 2.0, diameter, diameter));
                    else
                    {
                        QPoint l(5, 7);
                    
                        p.drawEllipse(QRect(-diameter / 2, -diameter / 2, diameter, diameter));
                       // p.drawEllipse(l, qreal(-diameter / 2, -diameter / 2), qreal(diameter,diameter));
                    }
                   
                }
            }
        }


    


    }
    void update() override {
        this->repaint();
    }
};


class Product : public QWidget
{public:
    Service& srv;
    Notificare noti;
        Product(Service& srv) :srv{ srv } {
        initGUI();
        initConect();
        refresh();
        
        }
private:
    int nrLinii = 0;
    int nrColoane = 4;
   
    QTableWidget* tbl1 = new QTableWidget(nrLinii, nrColoane, nullptr);

    QListWidget* lst = new QListWidget;
    QListWidget* nt = new QListWidget;
    
    QPushButton* btExit = new QPushButton{ "&Exit" };
    QPushButton* btAdd = new QPushButton{ "&Add" };
    QPushButton* btUp = new QPushButton{ "&Update" };
    QPushButton* btDel = new QPushButton{ "&Delete" };
    QPushButton* btFind = new QPushButton{ "&Find" };
    QPushButton* btSortA = new QPushButton{ "&Sort Nume" };
    QPushButton* btSortAc = new QPushButton{ "&Sort NumeD" };
    QPushButton* btSortD = new QPushButton{ "&Sort Suprafata" };
    QPushButton* btSortDc = new QPushButton{ "&Sort SuprafataD" };
    QPushButton* btSortC = new QPushButton{ "&Sort Tip" };
    QPushButton* btSortCc = new QPushButton{ "&Sort TipD" };
    QPushButton* btFiltru1 = new QPushButton{ "&Filter Suprafata " };
    QPushButton* btFiltru2 = new QPushButton{ "&Filter Tip" };
    QPushButton* btUndo = new QPushButton{ "Undo" };

    QPushButton* btceva = new QPushButton{ "Lista Notificare" };
    QPushButton* btAddN = new QPushButton{ "Add Lista" };
    QPushButton* btGol = new QPushButton{ "Golire Lista" };
    QPushButton* btRan = new QPushButton{ "Add Random" };
    QPushButton* btExpCvs = new QPushButton{ "Export CVS" };
    QPushButton* btExpHtml = new QPushButton{ "Export Html" };

    QPushButton* btCOS = new QPushButton{ "CosCRUDGUI" };
    QPushButton* btCOS2 = new QPushButton{ "CosV2CRUDGUI" };
    QPushButton* btCOSRo = new QPushButton{ "CosReadOnlyGUI" };

    QPushButton* btAddNC = new QPushButton{ "Add Lista" };
    QPushButton* btGolC = new QPushButton{ "Golire Lista" };

    QPushButton* btAddNCR = new QPushButton{ "Add Lista" };
    QPushButton* btGolCR = new QPushButton{ "Golire Lista" };
    
    QSpinBox* aa = new QSpinBox;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* BOX = new QLineEdit;
    QLineEdit* txtApr = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtSpr= new QLineEdit;
    QLineEdit* txtNume1 = new QLineEdit;
    QLineEdit* txtApr1 = new QLineEdit;
    QLineEdit* txtTip1 = new QLineEdit;
    QLineEdit* txtSpr1 = new QLineEdit;
    QLineEdit* txtFil = new QLineEdit;
    QLineEdit* txtFil2 = new QLineEdit;
    QLineEdit* txtFind= new QLineEdit;
    QLineEdit* txtRan = new QLineEdit;
    QLineEdit* txtCvs = new QLineEdit;
    QLineEdit* txtHtml = new QLineEdit;
    QTableView* retetaList = new QTableView();


    MyModel* lst1 = new MyModel();
   

    std::vector<Observer*> observers;
   

    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }

   
    
    void initConect() {
        QObject::connect(btExit, &QPushButton::clicked, [&]() {
            QMessageBox::information(nullptr, "Messages", "bye!            ");
            close();
            
            });
        QObject::connect(btFiltru1, &QPushButton::clicked, [&]() {
            if (txtFil->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
            else reloadList(srv.FiltruSuprafata(txtFil->text().toDouble()));
            });
        QObject::connect(btFiltru2, &QPushButton::clicked, [&]() {
            if (txtFil2->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
            else reloadList(srv.FiltruTip(txtFil2->text().toStdString()));
            });
        QObject::connect(btAdd, &QPushButton::clicked, this, &Product::addL);
       
        QObject::connect(btDel, &QPushButton::clicked, this, &Product::del);
        QObject::connect(btFind, &QPushButton::clicked, this, &Product::caut);
       
       

        QObject::connect(btSortA, &QPushButton::clicked, [&]() {
            reloadList(srv.SortByNumeC()); });

        QObject::connect(btSortAc, &QPushButton::clicked, [&]() {
            reloadList(srv.SortByNume()); });

        QObject::connect(btSortD, &QPushButton::clicked, [&]() {
            reloadList(srv.SortBySuprafata()); });

        QObject::connect(btSortDc, &QPushButton::clicked, [&]() {
            reloadList(srv.SortBySuprafataC()); });


        QObject::connect(btSortC, &QPushButton::clicked, [&]() {
            reloadList(srv.SortByTipSuprafata()); });
        QObject::connect(btSortCc, &QPushButton::clicked, [&]() {
            reloadList(srv.SortByTipSuprafataC()); });

        QObject::connect(btCOS, &QPushButton::clicked, [&]() {
            
           
              addObserver(new Cos{ srv,observers,1 });
            });

        QObject::connect(btCOS2, &QPushButton::clicked, [&]() {


            addObserver(new Cos{ srv,observers,2 });
            });

        QObject::connect(btCOSRo, &QPushButton::clicked, [&]() {

            

            addObserver(new CosGUIRO{ srv,observers }); });
            

        
        QObject::connect(btceva, &QPushButton::clicked, [&]() {
            
          
            
            QWidget* wid = new QWidget;
            QVBoxLayout* v = new QVBoxLayout;
            wid->setLayout(v);
            v->addWidget(nt);
            auto buton = new QHBoxLayout;
            buton->addWidget(btAddN);
            buton->addWidget(btGol);
            auto buton1 = new QHBoxLayout;
            buton1->addWidget(btRan);
            buton1->addWidget(txtRan);
            auto buton2 = new QHBoxLayout;
            buton2->addWidget(btExpCvs);
            buton2->addWidget(txtCvs);
            auto buton3 = new QHBoxLayout;
            buton3->addWidget(btExpHtml);
            buton3->addWidget(txtHtml);
            
            v->addLayout(buton);
            v->addLayout(buton1);
            v->addLayout(buton2);
            v->addLayout(buton3);

            QObject::connect(aa, QOverload<int>::of(&QSpinBox::valueChanged),
                [=](int i) {

                    srv.AddNotificare(i);
                    reloadList1(srv.GetAllNotificare());
                });

            QObject::connect(btAddN, &QPushButton::clicked, [&]() {
                try {
                   
                    srv.AddNotificare(txtApr->text().toInt());
                     reloadList1(srv.GetAllNotificare());
                }
                catch (ValidateException& err) {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));

                }});

            QObject::connect(btGol, &QPushButton::clicked, [&]() {
                srv.Delete();
                reloadList1(srv.GetAllNotificare());
                });

            QObject::connect(btRan, &QPushButton::clicked, [&]() {
                if (txtRan->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
                if (txtRan->text().toInt() > srv.GetAll().size()&& txtRan->text().toInt()<0) QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul invalid!"));
                if (txtRan->text().toInt() > srv.GetAll().size()-srv.GetAllNotificare().size()) QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul invalid!"));
                else {
                    try {
                        srv.random(txtRan->text().toInt());
                        reloadList1(srv.GetAllNotificare());
                    }
                    catch (ValidateException& err) {
                        QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));

                    }
                }
                });


            QObject::connect(btExpCvs, &QPushButton::clicked, [&]() {
                if (txtCvs->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
                
                else 
                    
                    srv.Export(txtCvs->text().toStdString());
                       
                   
                });
            
            QObject::connect(btExpHtml, &QPushButton::clicked, [&]() {
                if (txtHtml->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));

                else

                    srv.ExportHtml(txtHtml->text().toStdString());


                });

            wid->show();
          });
       

        QObject::connect(btUndo, &QPushButton::clicked, [&]() {
            try {
                srv.Undo();
                reloadList(srv.GetAll());
            }
            catch (ValidateException& err) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));

            }
            });

        QObject::connect(btUp, &QPushButton::clicked, this,&Product::mod);

        

        QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
            
            auto sel = lst->selectedItems();
            if (sel.isEmpty()) {
                txtApr->setText("");
                txtNume->setText("");
                txtSpr->setText("");
                txtTip->setText("");
            }
            else {
                
                
                auto selItem = sel.at(0);
                txtNume->setText(selItem->text());
                auto apr = selItem->data(Qt::UserRole).toString();
                txtApr->setText(apr);
                auto p = srv.GetSpr(apr.toInt());
                auto t = srv.GetTi(apr.toInt());
                txtSpr->setText(QString::number(p));
                txtTip->setText(QString::fromStdString(t));

                
                
               
                QListWidgetItem * item = lst->selectedItems().at(0);
                item->setData(Qt::BackgroundRole, QBrush{ Qt::darkGreen,Qt::SolidPattern });

                QWidget* widi = new QWidget;
                auto formLy = new QFormLayout;
               
                widi->setLayout(formLy);
                txtApr1->setText(txtApr->text());
                txtNume1->setText(txtNume->text());
                txtSpr1->setText(txtSpr->text());
                txtTip1->setText(txtTip->text());
                formLy->addRow("Apartament", txtApr1);
                formLy->addRow("Nume", txtNume1);
                formLy->addRow("Suprafata", txtSpr1);
                formLy->addRow("Tip", txtTip1);
                
                txtApr1->setReadOnly(true);
                txtNume1->setReadOnly(true);
                txtSpr1->setReadOnly(true);
                txtTip1->setReadOnly(true);
                widi->show();
                
                }
           
            }
        );
        QObject::connect(tbl1, &QTableWidget::itemSelectionChanged, [&]() {

            auto sel = tbl1->selectedItems();
            if (sel.isEmpty()) {
                txtApr->setText("");
                txtNume->setText("");
                txtSpr->setText("");
                txtTip->setText("");
            }
            else {


                auto selItem = sel.at(0);
                txtNume->setText(selItem->text());
                auto apr = selItem->data(Qt::UserRole).toString();
                txtApr->setText(apr);
                auto p = srv.GetSpr(apr.toInt());
                auto t = srv.GetTi(apr.toInt());
                txtSpr->setText(QString::number(p));
                txtTip->setText(QString::fromStdString(t));


                QWidget* widi = new QWidget;
                auto formLy = new QFormLayout;

                widi->setLayout(formLy);
                txtApr1->setText(txtApr->text());
                txtNume1->setText(txtNume->text());
                txtSpr1->setText(txtSpr->text());
                txtTip1->setText(txtTip->text());
                formLy->addRow("Apartament", txtApr1);
                formLy->addRow("Nume", txtNume1);
                formLy->addRow("Suprafata", txtSpr1);
                formLy->addRow("Tip", txtTip1);

                txtApr1->setReadOnly(true);
                txtNume1->setReadOnly(true);
                txtSpr1->setReadOnly(true);
                txtTip1->setReadOnly(true);
                widi->show();

            }

            }
        );
        
    }
       

    void mod() {
        try {
            srv.Update(txtApr->text().toInt(), txtApr->text().toInt(), txtNume->text().toStdString(), txtSpr->text().toDouble(), txtTip->text().toStdString());
            reloadList1(srv.GetAllNotificare());
            reloadList(srv.GetAll());
        }
        catch (ValidateException& err) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));

        }
    }
    void caut() {
        if (txtFind->text().toStdString() == "") QMessageBox::warning(nullptr, "Warning", QString::fromStdString("Parametrul este vid!"));
        else {
            try {
                int x = srv.Search(txtFind->text().toInt());
                if (x != -1)
                    QMessageBox::information(nullptr, "Messages", "Locatarul se afla in lista!");
            }
            catch (ValidateException& err) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));

            }
        }
    }
    void del() {

        try {
            srv.Remove(txtApr->text().toInt());
            reloadList1(srv.GetAllNotificare());
            reloadList(srv.GetAll());
        }
        catch (ValidateException& err) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));
        
        }
   }

     void addL() {
         try{
         srv.Add(txtApr->text().toInt(), txtNume->text().toStdString(), txtSpr->text().toDouble(), txtTip->text().toStdString());

         
        // reloadList(srv.GetAll());
         refresh();
         }
         catch (ValidateException& err) {
             QMessageBox::warning(this, "Warning", QString::fromStdString(err.GetMessages()[0]));
         }
      }
     
    

     void reloadList(const std::vector<Locatar>& locatari) {
        
         lst->clear();
         
         for (const auto& l : locatari) {
             
             QListWidgetItem* item2 = new QListWidgetItem(QString::fromStdString(l.GetNume()));
             item2->setData(Qt::UserRole, QString::number(l.GetApartament()));
             item2->setData(Qt::BackgroundRole, QBrush{ Qt::white,Qt::SolidPattern });
                 
             lst->addItem(item2);
         }
         
         /*tbl1->clear();
         int c = 0;
         for (auto& x : locatari) {
             QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(x.GetNume()));
             QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(x.GetApartament()));
             QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(x.GetSuprafata()));
             QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(x.GetTip()));
             tbl1->insertRow(c);
             
             tbl1->setItem(c, 0, item);
             tbl1->setItem(c, 1, item1);
             tbl1->setItem(c, 2, item2);
             tbl1->setItem(c, 3, item3);
             c++;
         }*/
            
     }

     void reloadList1(const std::vector<Locatar>& locatari) {

         nt->clear();

         for (const auto& l : locatari) {
             QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(l.GetNume()));
             item->setData(Qt::UserRole, QString::number(l.GetApartament()));
             nt->addItem(item);
         }


     }

   
     void refresh() {
         
         
         //lst1->setProduse(srv.GetAll());
        
         
         //update_ferestre();
         reloadList(srv.GetAll());
         reloadList1(srv.GetAllNotificare());
        
    }

     

    void initGUI() {
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);
     
        auto stgly2 = new QVBoxLayout;
       // retetaList->setModel(lst1);
       // retetaList->setModel(lst);

        //stgly2->addWidget(retetaList);
        stgly2->addWidget(lst);
       // stgly2->addWidget(tbl1);
        
        auto lyBtns2 = new QVBoxLayout;
       

        QHBoxLayout* sort = new QHBoxLayout();
        sort->addWidget(btSortA);
        sort->addWidget(btSortAc);
        stgly2->addLayout(sort);

        QHBoxLayout* sort1 = new QHBoxLayout();
        sort1->addWidget(btSortD);
        sort1->addWidget(btSortDc);
        stgly2->addLayout(sort1);


        
        QHBoxLayout* sort2 = new QHBoxLayout();
        sort2->addWidget(btSortC);
        sort2->addWidget(btSortCc);
        stgly2->addLayout(sort2);

        lyMain->addLayout(stgly2);
       
        auto stgly = new QVBoxLayout;

        auto formLy = new QFormLayout;
        formLy->addRow("Apartament", txtApr);
        formLy->addRow("Nume", txtNume);
        formLy->addRow("Suprafata", txtSpr);
        formLy->addRow("Tip", txtTip);

        stgly->addLayout(formLy);

        auto lyBtns = new QVBoxLayout;
        lyBtns->addWidget(btAdd);
        lyBtns->addWidget(btUp);
        lyBtns->addWidget(btDel);
        lyBtns->addWidget(btUndo);
        QHBoxLayout* lista= new QHBoxLayout();
        lista->addWidget(btceva);
        
        lyBtns->addLayout(lista);

        QHBoxLayout *filterPriceLayout = new QHBoxLayout();
        filterPriceLayout->addWidget(btFind);
        filterPriceLayout->addWidget(txtFind);
        lyBtns->addLayout(filterPriceLayout);
        QHBoxLayout* filterPriceLayout1 = new QHBoxLayout();
        filterPriceLayout1->addWidget(btFiltru1);
        filterPriceLayout1->addWidget(txtFil);
        lyBtns->addLayout(filterPriceLayout1);
        QHBoxLayout* filterPriceLayout2 = new QHBoxLayout();
        filterPriceLayout2->addWidget(btFiltru2);
        filterPriceLayout2->addWidget(txtFil2);

        lyBtns->addLayout(filterPriceLayout2);
        lyBtns->addWidget(btExit);
        stgly->addLayout(lyBtns);

         QVBoxLayout* wid = new QVBoxLayout;
         wid->addWidget(btCOS);
         wid->addWidget(btCOS2);
         wid->addWidget(btCOSRo);
         //wid->addWidget(tbl);
       
        lyMain->addLayout(stgly);
        
        lyMain->addLayout(wid);
      
     
    }

};
