#include "repository.h"
#include<iostream>
#include<random>

void ExceptionRepo::StoreLocatar(const Locatar& l) {


	repo.insert(std::pair<int, Locatar>(l.GetApartament(), l));
}

void ExceptionRepo::DeleteLocatar(const int apartament)
{
	std::vector<std::string> messages;
	float x = (float)rand() / ((float)RAND_MAX / 1);
	if (x > probabilitate)
	{
		messages.push_back("eroare aruncata de ExceptionRepo");
		throw RepoException(messages);
	}
	else {
		std::map<int, Locatar>::iterator it;
		it = repo.find(apartament);
		repo.erase(it);

	}
}

void ExceptionRepo::UpdateLocatar( int apartament, Locatar& l)
{
	std::vector<std::string> messages;
	float x = (float)rand() / ((float)RAND_MAX / 1);
	if (probabilitate > x)
	{
		messages.push_back("eroare aruncata de ExceptionRepo");
		throw RepoException(messages);
	}
	else {
		std::map<int, Locatar>::iterator it;
		it = repo.find(apartament);
		it->second = l;
	}



}

int ExceptionRepo::SearchLocatar(const int apartament)
{
	int i = 0;
	for (auto j = repo.begin(); j != repo.end(); j++) {
		if (j->first == apartament)
			return i;
		i++;
	}

	return -1;
}

const std::vector<Locatar>& ExceptionRepo::GetAll()   noexcept
{
	vec.clear();
	for (auto j = repo.begin(); j != repo.end(); j++) {
		vec.push_back(j->second);
	}
	return vec;
}







Locatar ExceptionRepo::getLocatar(int apartament)
{
	for (auto j = repo.begin(); j != repo.end(); j++)
		if (j->first == apartament)
			return j->second;
}

std::ostream& operator<<(std::ostream& out, const RepoException& err)
{

	for (const auto& message : err.messages)
		out << message << "\n";
	return out;

}





void Repository::StoreLocatar(const Locatar& l) {
	repo.push_back(l);
}


/*
		Functie de atergere Locatar in repository
		apartament- locatarul care trebuie sters
*/
void Repository::DeleteLocatar(const int apartament)
{
	int i = 0;
	for (const auto loc : repo)
	{
		if (loc.GetApartament() == apartament)
		{
			std::vector<Locatar> ::iterator it{ repo.erase(repo.begin() + i) };


		}
		i++;
	}
}

//Functie care returneaza toti locatarii

const std::vector<Locatar>& Repository::GetAll() noexcept {
	return repo;
}

Locatar Repository::getLocatar(const int apartament)
{

	for (auto el : repo)
	{

		if (el.GetApartament() == apartament)
			return el;
	}
}


/*
		Functie de modificare Locatar din repository
		apartament- locatarul care trebuie modificat
		l - locatar nou
*/
void Repository::UpdateLocatar(const int apartament, Locatar& l) {

	const int x = SearchLocatar(apartament);
	if (x > -1)
	{
		for (auto& loc : repo)
			if (loc.GetApartament() == apartament)
				loc = l;
	}
}

/*
		Functie de cautare Locatar in repository
		apartament- locatarul care trebuie cautat
*/
int Repository::SearchLocatar(const int apartament) noexcept {

	int i = 0;
	for (const auto loc : repo) {
		if (loc.GetApartament() == apartament)
			return i;
		i++;
	}

	return -1;
}


void TestStore() {


	Repository lista;
	lista.StoreLocatar(Locatar(2, "Popescu Ion", 100, "2 camere"));
	lista.StoreLocatar(Locatar(3, "Ionescu Vasile", 90, "open space"));
	assert(lista.GetAll().size() == 2);
}


void TestDelete() {

	Repository lista;
	lista.StoreLocatar(Locatar(2, "Popescu Ion", 100, "2 camere"));
	lista.StoreLocatar(Locatar(3, "Ionescu Vasile", 90, "open space"));
	assert(lista.GetAll().size() == 2);
	lista.DeleteLocatar(3);
	assert(lista.GetAll().size() == 1);

	//assert(lista.DeleteLocatar(12)==0);

}

void TestUpdate() {

	Repository lista;

	lista.StoreLocatar(Locatar(2, "Popescu Ion", 100, "2 camere"));
	lista.StoreLocatar(Locatar(3, "Ionescu Vasile", 90, "open space"));
	Locatar l(2, "Popescu Vasile", 101, "3 camere");
	lista.UpdateLocatar(2, l);

	assert(lista.GetAll()[0].GetNume() == "Popescu Vasile");
	assert(lista.GetAll()[0].GetApartament() == 2);
	assert(lista.GetAll()[0].GetSuprafata() == 101);
	assert(lista.GetAll()[0].GetTip() == "3 camere");



}

void TesteSearch() {

	Repository lista;
	lista.StoreLocatar(Locatar(2, "Popescu Ion", 100, "2 camere"));
	lista.StoreLocatar(Locatar(3, "Ionescu Vasile", 90, "open space"));
	assert(lista.SearchLocatar(2) == 0);
	assert(lista.SearchLocatar(22) == -1);

}



////Functie teste repository
void TesteRepo() {

	TestStore();
	TesteSearch();
	TestDelete();
	TestUpdate();
}

void RepoFile::loadFromFile()
{

	std::ifstream in(fName);
	while (!in.eof()) {

		float suprafata;
		int apartament;
		in >> apartament;
		if (in.eof()) break;
		std::string nume, tip;
		in >> nume;  in >> suprafata; in >> tip;
		Locatar l{ apartament,nume.c_str(),suprafata,tip.c_str() };
		Repository::StoreLocatar(l);
	}
	in.close();
}

void RepoFile::writeToFile()
{
	std::ofstream out(fName);
	for (auto& l : GetAll()) {
		out << l.GetApartament() << " ";
		out << l.GetNume() << " ";
		out << l.GetSuprafata() << " ";
		out << l.GetTip() << " ";
		out << std::endl;
	}
	out.close();
}


void TesteRepofile() {


	int n = 3, m = 9;
	std::ifstream in("teste.txt");
	std::ofstream out("teste.txt");
	out << "";

	RepoFile repo{ "teste.txt" };
	assert(repo.GetAll().size() == 0);
	repo.StoreLocatar(Locatar{ 12,"ana",123,"2_camere" });
	repo.StoreLocatar(Locatar{ 14,"ana",123,"2_camere" });
	
	repo.DeleteLocatar(12);
	assert(repo.GetAll().size() == 1);

	Locatar l{ 123,"nume",123,"tip" };
	repo.UpdateLocatar(14, l);

	assert(repo.SearchLocatar(123) == 0);

	std::string nume, tip;
	int apartament;
	float suprafat;
	while (!in.eof()) {

		in >> apartament >> nume >> suprafat >> tip;
		assert(apartament == 123);
		assert(nume == "nume");
		assert(suprafat == 123);
		assert(tip == "tip");

	}

	in.close();

}


void TesteExceptionRepo() {
	ExceptionRepo repo{45};

	repo.StoreLocatar(Locatar{ 1,"ana",23,"tip" });
	repo.StoreLocatar(Locatar{ 2,"ana",23,"tip" });
	repo.StoreLocatar(Locatar{ 3,"ana",23,"tip" });
	repo.StoreLocatar(Locatar{ 4,"ana",23,"tip" });
	assert(repo.SearchLocatar(1) == 0);
	assert(repo.SearchLocatar(10) == -1);
	//repo.UpdateLocatar(1, Locatar{ 1,"maria",23,"tip" });
	auto m = repo.getLocatar(1);
	assert(m.GetNume() == "ana");
	repo.StoreLocatar(Locatar{ 1,"ana",23,"tip" });
	try {
		Locatar l1 = Locatar{ 1,"maria",23,"tip" };
		repo.UpdateLocatar(1,l1 ); }
	catch (RepoException) { assert(true); }

	assert(repo.GetAll().size() == 4);
	repo.DeleteLocatar(1);
	assert(repo.GetAll().size() == 3);

	ExceptionRepo repo1{ -1 };
	repo1.StoreLocatar(Locatar{ 1,"ana",23,"tip" });
	Locatar l2 = Locatar{ 1,"maria",23,"tip" };
	repo1.UpdateLocatar(1,l2 ); 
	assert(repo1.getLocatar(1).GetNume() == "maria");


	
}