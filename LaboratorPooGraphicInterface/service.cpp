#include "service.h"
#include <iostream>
#include<fstream>





void Service::Add(const int apartament, const std::string& nume, const float suprafata, const std::string& tip) {
	Locatar l(apartament, nume, suprafata, tip);
	val.ValidateLocatar(l);
	val.ValidateAdaugare(l, GetAll());
	repo.StoreLocatar(l);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, l));

}

void Service::Remove(const int apartament) {
	val.ValidateSearch(apartament, GetAll());
	if (notificare.SearchinNotificare(apartament) == 0)
	{
		notificare.Del(apartament);
	}
	Locatar l = repo.getLocatar(apartament);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, l));
	repo.DeleteLocatar(apartament);
}



void Service::Update(const int apartament, const int apartament1, const std::string nume, const double suprafata, const std::string tip) {
	Locatar l(apartament1, nume, suprafata, tip);
	val.ValidateLocatar(l);
	val.ValidateSearch(apartament, GetAll());
	Locatar l2 = repo.getLocatar(apartament);
	undoActions.push_back(std::make_unique<UndoModifica>(repo, l2, apartament1));

	repo.UpdateLocatar(apartament, l);



}


const std::vector<Locatar>& Service::GetAll() const noexcept {
	return repo.GetAll();
}



int Service::Search(const int apartament)
{
	val.ValidateSearch(apartament, GetAll());
	return repo.SearchLocatar(apartament);
}




std::vector<Locatar> Service::Filter(std::function <bool(const Locatar&)> f) const noexcept {
	std::vector<Locatar> result;
	std::vector<Locatar> c{ repo.GetAll() };
	//std::copy_if(repo.GetAll().begin(), repo.GetAll().end(), std::back_inserter(result), f);
	std::copy_if(c.begin(), c.end(), std::back_inserter(result), f);
	return result;
}

std::map<string, std::pair<string, int>> Service::dictionar() {


	std::map<string, std::pair<string, int>> dic;

	std::vector<Locatar> res{ GetAll() };

	for (auto& el : res) {

		int x = dic.count(el.GetTip());
		if (x > 0)
			dic[el.GetTip()].second++;
		else
			dic[el.GetTip()] = std::make_pair(el.GetTip(), x + 1);

	}


	return dic;
}



std::vector<Locatar> Service::FiltruTip(const std::string tip) noexcept
{
	return Filter([tip](const Locatar& l) noexcept {
		return l.GetTip() == tip;
		});

}


std::vector<Locatar> Service::FiltruSuprafata(const float suprafata) noexcept
{
	return Filter([suprafata](const Locatar& l) noexcept {
		return l.GetSuprafata() <= suprafata;
		});

}


std::vector<Locatar> Service::Sort(functie f) const {

	std::vector<Locatar> result{ repo.GetAll() };
	std::sort(result.begin(), result.end(), f);
	return result;
}


std::vector<Locatar> Service::SortByNume() const {
	return Sort([](const Locatar& m1, const Locatar& m2) {
		return m1.GetNume() > m2.GetNume();
		});
}

std::vector<Locatar> Service::SortByNumeC() const {
	return Sort([](const Locatar& m1, const Locatar& m2) {
		return m1.GetNume() < m2.GetNume();
		});
}

std::vector<Locatar> Service::SortBySuprafata() const {
	return Sort([](const Locatar& m1, const Locatar& m2) {
		return m1.GetSuprafata() > m2.GetSuprafata();
		});
}

std::vector<Locatar> Service::SortBySuprafataC() const {

	return Sort([](const Locatar& m1, const Locatar& m2) {
		return m1.GetSuprafata() < m2.GetSuprafata();
		});

}



std::vector<Locatar> Service::SortByTipSuprafata() const {
	return Sort([](const Locatar& m1, const Locatar& m2) {
		if (m1.GetTip() != m2.GetTip()) return m1.GetTip() < m2.GetTip(); else return m1.GetSuprafata() > m2.GetSuprafata();
		});
}


std::vector<Locatar> Service::SortByTipSuprafataC() const {
	return Sort([](const Locatar& m1, const Locatar& m2) {
		if (m1.GetTip() != m2.GetTip()) return m1.GetTip() > m2.GetTip(); else return m1.GetSuprafata() > m2.GetSuprafata();
		});
}

void  Service::AddNotificare(const int apartament) {
	std::vector <std::string> messages;
	std::cout << apartament << " ";
	const int i = Search(apartament);
	const int j = notificare.SearchinNotificare(apartament);
	if (j == 0)
	{
		messages.push_back("Acest locatar se afla deja pe lista de notificare!\n");
		throw ValidateException(messages);
	}

	else
	{
		std::vector<Locatar> re{ repo.GetAll() };
		notificare.Add(re[i]);
	}

}

const std::vector<Locatar>& Service::GetAllNotificare() {
	return notificare.GetAll();
}


void Service::Delete() {
	notificare.DeleteNotificare();
}



void Service::Export(const std::string nume_fisiere) {

	std::vector <std::string> messages;
	std::ofstream file;
	file.open(nume_fisiere);
	if (!file.is_open())
		messages.push_back("Eroare");
	if (messages.size() > 0)
		throw ValidateException(messages);
	std::vector<Locatar> res{ GetAllNotificare() };
	for (const auto el : res) {
		file << el.GetApartament() << "," << el.GetNume() << "," << el.GetSuprafata() << "," << el.GetTip() << std::endl;
	}
	file.close();
}


void Service::ExportHtml(const std::string nume_fisiere) {


	std::ofstream file;

	file.open(nume_fisiere);
	std::vector <std::string> messages;
	if (!file.is_open())
		messages.push_back("Eroare");
	if (messages.size() > 0)
		throw ValidateException(messages);
	file << "<html><body>" << std::endl;
	file << "<table border=\"1\" style=\"width:100% \" >" << std::endl;
	std::vector<Locatar> res{ GetAllNotificare() };
	for (const auto& el : res) {
		file << "<tr>" << std::endl;
		file << "<td>" << el.GetApartament() << " ";
		file << "<td>" << el.GetNume() << " ";
		file << "<td>" << el.GetSuprafata() << std::endl;
		file << "<td>" << el.GetTip() << std::endl;
		file << "</tr>" << std::endl;

	}
	file << "</table>" << std::endl;
	file << "</body></html>" << std::endl;
	file.close();
}


void Service::Undo()
{
	std::vector<std::string>messages;


	if (undoActions.size() == 0) {

		messages.push_back("Nu mai exista operatii!\n");
		throw ValidateException(messages);
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}




std::string Service::GetTi(int apartament)
{
	for (auto& el : GetAll())
	{
		if (el.GetApartament() == apartament)
			return el.GetTip();}
	
}

float Service::GetSpr(int apartament)
{
	for (auto& el : GetAll())
	{
		if (el.GetApartament() == apartament)
			return el.GetSuprafata();}
}

int Service::cauta_dupa_apartamnet(int apartament)
{
	for (auto& el : GetAll())
	{
		if (el.GetApartament() == apartament)
			return 1;
	}
	return -1;
}
void Service::random(int n) {
	int ok = 1;
	while (n)
	{
		
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(1, 9);
		int apartament = dist(mt);

		while (cauta_dupa_apartamnet(apartament) == -1) {
			apartament = dist(mt);
		}
		//stiu ca e in lista intiala
		ok = 1;
		while (notificare.SearchinNotificare(apartament) == 0 && ok)
		{
			apartament = dist(mt);
			while (cauta_dupa_apartamnet(apartament) == -1) {
				apartament = dist(mt);
			}
			
		}
		
		
		AddNotificare(apartament);
		n--;
	}
}




void TestAdd() {

	Repository repo;

	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "3 camere");
	serv.Add(4, "Martinescu Ioan", 36.5, "2 camere");
	serv.Add(5, "Martinescu Ioan", 38.5, "6 camere");
	assert(serv.cauta_dupa_apartamnet(23) == -1);
	assert(serv.cauta_dupa_apartamnet(2) == 1);
	assert(serv.GetTi(2) == "2 camere");
	assert(serv.GetSpr(2) == 34.5);
	assert(serv.GetAll().size() == 4);




}

void TestAddNotificare() {


	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.Add(4, "Martinescu Ioan", 34.5, "2 camere");
	serv.Add(5, "Martinescu Ioan", 34.5, "2 camere");

	Notificare n;
	serv.AddNotificare(2);
	serv.AddNotificare(3);
	assert(serv.GetAllNotificare().size() == 2);
	try {
		serv.AddNotificare(2);
	}
	catch (ValidateException) {

	}

	serv.AddNotificare(4);
	assert(serv.GetAllNotificare().size() == 3);
	serv.Delete();

}

void TestDeleteNotificare() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.Add(4, "Martinescu Ioan", 34.5, "2 camere");
	serv.Add(5, "Martinescu Ioan", 34.5, "2 camere");






	Notificare n;
	serv.AddNotificare(2);
	serv.AddNotificare(3);
	serv.AddNotificare(4);


	assert(serv.GetAllNotificare().size() == 3);

	n.DeleteNotificare();
	assert(n.GetAll().size() == 0);
}



void TestRandom() {

	Repository repo;
	Service serv{ repo };
	Notificare n;
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	//serv.Add(3, "Martinescu Ioan", 34.5, "3 camere");
	//serv.Add(4, "Martinescu Ioan", 36.5, "2 camere");
	serv.Add(5, "Martinescu Ioan", 38.5, "6 camere");
	//serv.Add(6, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(7, "Martinescu Ioan", 34.5, "3 camere");
	//serv.Add(8, "Martinescu Ioan", 36.5, "2 camere");
	serv.Add(9, "Martinescu Ioan", 38.5, "6 camere");
	serv.Add(1, "Martinescu Ioan", 38.5, "6 camere");
	serv.random(4);
	assert(serv.GetAllNotificare().size() == 4);
	//serv.random(4);
	//assert(serv.GetAllNotificare().size() == 8);

}


void TestRemove() {


	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	assert(serv.GetAll().size() == 2);
	serv.Remove(2);
	assert(serv.GetAll().size() == 1);
}

void TestUpdat() {


	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.Update(3, 5, "Martinescu Ioana", 23, "2 camere");

	assert(serv.GetAll()[1].GetNume() == "Martinescu Ioana");
	assert(serv.GetAll()[1].GetSuprafata() == 23);
	assert(serv.GetAll()[1].GetTip() == "2 camere");
	assert(serv.GetAll().size() == 2);

}

void TestSearch() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	assert(serv.Search(3) == 1);


}

void TestFiltruTip() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.Add(4, "Martinescu Ioan", 34.5, "6 camere");
	serv.Add(5, "Martinescu Ioan", 34.5, "9 camere");
	auto result = serv.FiltruTip("2 camere");
	assert(result.size() == 2);
	assert(result[0].GetApartament() == 2);
	auto result1 = serv.FiltruTip("1 camera");
	assert(result1.size() == 0);
}




void TestFiltruSuprafata() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 35.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 40, "2 camere");
	serv.Add(4, "Martinescu Ioan", 90, "6 camere");
	serv.Add(5, "Martinescu Ioan", 100, "9 camere");
	auto result = serv.FiltruSuprafata(70);
	assert(result.size() == 2);
	assert(result[0].GetApartament() == 2);
}


void TesteSortNumeC() {
	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 90, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortByNumeC();
	assert(res[3].GetNume() == "Vlad");
	assert(res[2].GetNume() == "Ioan");
	assert(res[1].GetNume() == "Diana");
	assert(res[0].GetNume() == "Ana");
}


void TesteSortNume() {
	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 90, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortByNume();
	assert(res[0].GetNume() == "Vlad");
	assert(res[1].GetNume() == "Ioan");
	assert(res[2].GetNume() == "Diana");
	assert(res[3].GetNume() == "Ana");
}



void TesteSortSuprafata() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 1233, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortBySuprafata();
	assert(res[0].GetSuprafata() == 1233);
	assert(res[1].GetSuprafata() == 100);
	assert(res[2].GetSuprafata() == 40);
	assert(res[3].GetSuprafata() == 35.5);
}


void TesteSortSuprafataC() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 1233, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortBySuprafataC();
	assert(res[3].GetSuprafata() == 1233);
	assert(res[2].GetSuprafata() == 100);
	assert(res[1].GetSuprafata() == 40);
	assert(res[0].GetSuprafata() == 35.5);
}



void TesteSortTipSuprafata() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 90, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortByTipSuprafata();
	assert(res[0].GetTip() == "2 camere");
	assert(res[1].GetTip() == "2 camere");
	assert(res[0].GetSuprafata() == 40);
	assert(res[1].GetSuprafata() == 35.5);
	assert(res[2].GetTip() == "6 camere");
	assert(res[3].GetTip() == "9 camere");
}


void TesteSortTipSuprafataC() {

	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Vlad", 35.5, "2 camere");
	serv.Add(3, "Ioan", 40, "2 camere");
	serv.Add(4, "Ana", 90, "6 camere");
	serv.Add(5, "Diana", 100, "9 camere");
	auto res = serv.SortByTipSuprafataC();
	assert(res[3].GetTip() == "2 camere");
	assert(res[2].GetTip() == "2 camere");
	assert(res[2].GetSuprafata() == 40);
	assert(res[3].GetSuprafata() == 35.5);
	assert(res[1].GetTip() == "6 camere");
	assert(res[0].GetTip() == "9 camere");
}

void TesteListaNotificare() {


	Notificare n;
	Locatar l(12, "ana", 12.4, "opne_space");
	Locatar l2(13, "ana", 12.4, "opne_space");
	n.Add(l);
	n.Add(l2);
	assert(n.GetAll().size() == 2);
	assert(n.SearchinNotificare(12) == 0);
	assert(n.SearchinNotificare(14) == 1);
	n.Del(12);
	assert(n.GetAll().size() == 1);
	n.DeleteNotificare();
	assert(n.GetAll().size() == 0);
}

void TesteExport() {
	Repository repo;
	Service serv{ repo };
	Notificare n;
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.AddNotificare(2);
	serv.AddNotificare(3);

	serv.Export("teste.csv");
	std::fstream file;
	file.open("teste.csv", std::ios::in);
	std::string line, v1;
	std::getline(file, line);

	assert(line[0] = 2);
	file.close();



}
void TesteExport2() {
	Repository repo;
	Service serv{ repo };
	Notificare n;
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "2 camere");
	serv.AddNotificare(2);
	serv.AddNotificare(3);


	serv.ExportHtml("teste.html");
	std::fstream file;
	file.open("teste.html", std::ios::in);
	assert(file.is_open());
	file.close();
}

void TestDictionar() {


	Repository repo;
	Service serv{ repo };
	std::map<string, std::pair<string, int>> dic;
	std::map<string, std::pair<string, int>> dic2;
	serv.Add(2, "Grigorescu Vlad", 34.5, "2_camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "3_camere");
	serv.Add(4, "Martinescu Ioan", 36.5, "2_camere");
	serv.Add(5, "Martinescu Ioan", 38.5, "6_camere");
	serv.Add(6, "Grigorescu Vlad", 34.5, "2_camere");
	serv.Add(7, "Martinescu Ioan", 34.5, "3_camere");
	serv.Add(8, "Martinescu Ioan", 36.5, "2_camere");
	serv.Add(9, "Martinescu Ioan", 38.5, "6_camere");
	serv.Add(1, "Martinescu Ioan", 38.5, "6_camere");
	dic = serv.dictionar();
	auto j = dic.begin();
	assert(j->first == "2_camere");
	assert(j->second.second == 4);
	j++;

	assert(j->first == "3_camere");
	assert(j->second.second == 2);
	j++;

	assert(j->first == "6_camere");
	assert(j->second.second == 3);

	dic2 = serv.dictionar();


}

void TesteUndo() {
	Repository repo;
	Service serv{ repo };
	serv.Add(2, "Grigorescu Vlad", 34.5, "2 camere");
	serv.Add(3, "Martinescu Ioan", 34.5, "3 camere");
	serv.Add(4, "Martinescu Ioan", 34.5, "3 camere");
	serv.Add(5, "Martinescu Ioan", 34.5, "3 camere");
	assert(serv.GetAll().size() == 4);
	serv.Undo();
	assert(serv.GetAll().size() == 3);
	serv.Undo();
	assert(serv.GetAll().size() == 2);

	serv.Remove(3);
	assert(serv.GetAll().size() == 1);
	serv.Undo();
	assert(serv.GetAll().size() == 2);

	serv.Update(2, 12, "nume", 123, "tip");
	assert(serv.GetAll()[0].GetApartament() == 12);
	assert(serv.GetAll()[0].GetNume() == "nume");
	assert(serv.GetAll()[0].GetSuprafata() == 123);
	assert(serv.GetAll()[0].GetTip() == "tip");

	serv.Undo();
	assert(serv.GetAll()[0].GetApartament() == 2);
	assert(serv.GetAll()[0].GetNume() == "Grigorescu Vlad");
	assert(serv.GetAll()[0].GetSuprafata() == 34.5);
	assert(serv.GetAll()[0].GetTip() == "2 camere");

	serv.Undo();
	serv.Undo();

	try {
		serv.Undo();
	}

	catch (ValidateException) {
		assert(true);
	}
}

void TesteSrv() {


	TestAdd();
	TestSearch();
	TestRemove();
	TestUpdat();
	TestFiltruTip();
	TestFiltruSuprafata();
	TesteSortNume();
	TesteSortNumeC();
	TesteSortSuprafata();
	TesteSortSuprafataC();
	TesteSortTipSuprafata();
	TesteSortTipSuprafataC();
	TesteListaNotificare();
	TestDeleteNotificare();
	TestAddNotificare();
	TestRandom();
	TesteExport();
	TesteExport2();
	TestDictionar();
	TesteUndo();
}
