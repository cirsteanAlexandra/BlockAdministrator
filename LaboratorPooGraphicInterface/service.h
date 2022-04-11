#pragma once

#include "repository.h"
#include <assert.h>
#include "Validator.h"
#include <functional>
#include<algorithm>
#include<random>
#include<string>
#include <cstdlib>
#include <ctime>
#include<map>
#include "Undo.h"
using std::unique_ptr;

typedef bool(*functie) (const Locatar&, const Locatar&);

class Notificare {

private:
	std::vector<Locatar> notificare;
public:

	Notificare() = default;
	void Add(const Locatar& l) {
		notificare.push_back(l);
	}
	const std::vector<Locatar>& GetAll() noexcept {
		return notificare;
	}


	void Del(const int apartament) {
		int i = 0;
		for (auto el : notificare) {
			if (el.GetApartament() == apartament)
				std::vector<Locatar> ::iterator it{ notificare.erase(notificare.begin() + i) };
			i++;
		}

	}

	void DeleteNotificare() {
		notificare.clear();
	}

	int SearchinNotificare(const int apartament) const noexcept {
		auto res = std::find_if(notificare.begin(), notificare.end(), [apartament](const Locatar& l) {return l.GetApartament() == apartament; });
		if (res != notificare.end())
			return 0;
		return 1;
	}

};

class Service
{
	AbstractRepo& repo;

	Validator& val;
	Notificare notificare;

	std::vector<unique_ptr<UndoAction>> undoActions;

	std::vector <Locatar> Filter(std::function <bool(const Locatar&)> f) const noexcept;
	std::map<string, std::pair<string, int>> dic;
	/*
		Functie generica de sortare locatarii
	*/
	std::vector<Locatar> Sort(functie f) const;
public:

	std::map<string, std::pair<string, int>> dictionar();
	/*
		Functie de creare service
		rep - repository locatari
		postconditii: obiect de tip service
	*/
	Service(AbstractRepo& rep) noexcept : repo{ rep }, val{ val }{};
	//Service(ExceptionRepo& rep) noexcept : repo{ rep }, val{ val }{};




	/*
		Functie de adaugare locatar in lista
	*/
	//void Add(const int a, const std::string n, const double b, const std::string t);
	void Add(const int apartament, const std::string& nume, const float suprafata, const std::string& tip);
	/*
		Functie de stergere locatar in lista
	*/
	void Remove(const int apartament);

	/*
		Functie de modificare locatar in lista
	*/
	void Update(const int apartament, const int apartament1, const std::string nume, const double suprafata, const std::string tip);

	/*
		Functie de cautare locatar in lista
	*/
	int Search(const int apartament);

	/*
		Functie de filtrare locatari dupa tip
	*/
	std::vector<Locatar> FiltruTip(const std::string tip) noexcept;

	/*
		Functie de filtrare locatari dupa suprafata
	*/
	std::vector<Locatar> FiltruSuprafata(const float suprafata) noexcept;
	//void dictionar();

	/*
		Functie  de sortare locatarii crescator dupa suprafata
	*/
	std::vector <Locatar> SortBySuprafataC() const;

	/*
		Functie de sortare locatarii descrescator dupa tip si suprafata
		se returneaza o lista de locatari ordonati descrescator dupa tip
	*/
	std::vector<Locatar> SortByTipSuprafataC() const;

	//Functie care returneaza toti locatarii 
	const std::vector<Locatar>& GetAll() const noexcept;

	/*
		Functie de sortare locatarii dupa nume(nealfabetic)
		se returneaza o lista cu locatarii ordonata nealfabetic
	*/
	std::vector<Locatar> SortByNume() const;

	/*
		Functie de sortare locatarii alfabetic dupa nume
		se returneaza o lista cu locatarii care indeplinesc cerintele date

	*/
	std::vector<Locatar> SortByNumeC() const;

	/*
		Functie de sortare locatarii descrescator dupa suprafata
		se returneaza o lista cu locatarii care indeplinesc cerintele date
	*/
	std::vector<Locatar> SortBySuprafata() const;

	/*
		Functie de sortare locatarii descrescator dupa tip si suprafata
		se returneaza o lista cu locatarii ordonati descrescator dupa tip
	*/
	std::vector<Locatar> SortByTipSuprafata() const;

	void AddNotificare(const int apartament);
	const std::vector<Locatar>& GetAllNotificare();
	void Delete();
	void random(int n);
	void Export(const std::string nume_fisiere);
	void ExportHtml(const std::string nume_fisiere);
	void Undo();

	float GetSpr(int apartament);
	std::string GetTi(int apartament);

	int cauta_dupa_apartamnet(int apartament);
};

void TesteSrv();
void TesteListaNotificare();

