#pragma once
#include<qwidget.h>
#include<qabstractitemmodel.h>
#include"domain.h"

class MyModel: public QAbstractTableModel
{private:   std::vector<Locatar> locatari;
vector<Locatar>filtru;
public:
	MyModel() {};
	
	MyModel(std::vector<Locatar>& locatari) : locatari{ locatari } {};
    int rowCount(const QModelIndex& parent = QModelIndex()) const override { return locatari.size(); }
	int columnCount(const QModelIndex& parent = QModelIndex()) const override { return 5; }

	QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override {
		
		if (role == Qt::BackgroundRole)
		{
			Locatar p = locatari[index.row()];
			if (std::find_if(filtru.begin(), filtru.end(), [p](const Locatar& p1) { return p.GetTip() == p1.GetTip(); }) != filtru.end())
				return QBrush(Qt::red);
		}
		
		
		
		if (role == Qt::DisplayRole) {
			Locatar m = locatari[index.row()];
			if (index.column() == 0)
				return QString::fromStdString(m.GetNume());
			if (index.column() == 1)
				return QString::number(m.GetApartament());
			if (index.column() == 2)
				return QString::number(m.GetSuprafata());
			if (index.column() == 3) {
				char numar[10];
				return QString::fromStdString(m.GetTip());
			}
		}

		
		return QVariant{};   }




    void setProduse(vector<Locatar> prod)
	{   locatari = prod;
		emit layoutChanged();}


	void setFiltru(vector<Locatar> prod)
	{
		filtru = prod;
		emit layoutChanged();
	}
};

