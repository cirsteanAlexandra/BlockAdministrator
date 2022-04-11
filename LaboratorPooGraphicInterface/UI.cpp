#include "UI.h"
#include<string>

void UI::print(const std::vector<Locatar>& locatari) const {


	for (const auto& loc : locatari)
	{
		std::cout << "Apartament " << loc.GetApartament() << " || ";
		std::cout << " Nume " << loc.GetNume() << " || ";
		std::cout << " Suprafata " << loc.GetSuprafata() << " || ";
		std::cout << " Tipul " << loc.GetTip() << "\n";
	}
}

void UI::start() {






	std::string nume, tip, n, t;
	int apartament, a;
	float suprafata, s;
	int cmd = -1;

	serv.Add(2, "Vlad", 34.5, "tipA");
	serv.Add(3, "Ioan", 34.5, "tipF");
	serv.Add(4, "ion", 34.5, "tipC");
	serv.Add(9, "maria", 34.5, "tipA");
	serv.Add(5, "Vlad", 394.5, "tipB");
	serv.Add(6, "Ioan", 34.75, "tipF");
	serv.Add(1, "Laura", 314.5, "tipD");
	serv.Add(7, "Ana", 334.5, "tipD");
	serv.Add(8, "Vlad", 34.5, "tipD");

	while (cmd) {



		std::cout << "1.Adauga locatar" << "\n";
		std::cout << "2.Sterge locatar" << "\n";
		std::cout << "3.Modifica locatar" << "\n";
		std::cout << "4.Cauta locatar" << "\n";
		std::cout << "5.Afiseaza locatari" << "\n";
		std::cout << "6.Filtru" << "\n";
		std::cout << "7.Sortare" << "\n";
		std::cout << "8.Adauga in lista de notificare" << "\n";
		std::cout << "9.Goleste lista de notificare" << "\n";
		std::cout << "10.Random" << "\n";
		std::cout << "11.Afisare Lista de notificare" << "\n";
		std::cout << "12.Export" << "\n";
		std::cout << "13.Dictionar" << "\n";
		std::cout << "14.Undo" << "\n";
		std::cout << "0.Exit" << "\n";

		std::cout << "<<< "; std::cin >> cmd;

		if (cmd == 1) {

			std::cout << "Adauga numar "; std::cin >> apartament;
			std::cout << "Adauga nume "; std::cin >> nume;//getline(std::cin,nume);

			std::cout << "Adauga suprafata "; std::cin >> suprafata;
			std::cout << "Adauga tip "; std::cin >> tip;//getline(std::cin,tip);
			try {
				serv.Add(apartament, nume, suprafata, tip);

			}
			catch (ValidateException& err) {
				std::cout << err;
			}
			std::cout << "\n";
		}


		if (cmd == 2) {

			std::cout << "Adauga  numarul apartamentului "; std::cin >> apartament;

			try {
				serv.Remove(apartament);
			}
			catch (ValidateException& err) {
				std::cout << err;
			}
			catch (RepoException& err) {
				std::cout << err;
			}

			std::cout << "\n";
		}

		if (cmd == 3) {

			try {
				std::cout << "Adauga  numarul apartamentului pe care vrei sa l modifici "; std::cin >> apartament;
				serv.Search(apartament);
				std::cout << "Adauga noile date: \n";
				std::cout << "Numar: "; std::cin >> a;
				std::cout << "Nume: "; std::cin >> n;
				std::cout << "Suprafata: "; std::cin >> s;
				std::cout << "Tip: "; std::cin >> t;
				serv.Update(apartament, a, n, s, t);
			}
			catch (ValidateException& err) {
				std::cout << err;
			}



			std::cout << "\n";
		}

		if (cmd == 4) {
			std::cout << "Adauga  numarul apartamentului pe care il cauti "; std::cin >> apartament;
			try {
				serv.Search(apartament);
				std::cout << serv.GetAll()[serv.Search(apartament)].GetApartament() << "  ";
				std::cout << serv.GetAll()[serv.Search(apartament)].GetNume() << "  ";
				std::cout << serv.GetAll()[serv.Search(apartament)].GetSuprafata() << "  ";
				std::cout << serv.GetAll()[serv.Search(apartament)].GetTip() << "  ";
			}
			catch (ValidateException& err) {
				std::cout << err;
			}

			std::cout << "\n";

		}

		if (cmd == 5) {
			print(serv.GetAll());
			std::cout << "\n";
		}

		if (cmd == 7) {
			int b;
			std::cout << "1.Sortare dupa nume \n";
			std::cout << "2.Sortare dupa suprafata \n";
			std::cout << "3.Sortare dupa tip+suprafata \n";
			std::cin >> a;
			std::cout << "1.Crescator\n";
			std::cout << "2.Descrescator\n";
			std::cin >> b;


			if (a == 1) {

				if (b == 1)
					print(serv.SortByNumeC());
				else print(serv.SortByNume());
			}

			if (a == 2) {
				if (b == 1)
					print(serv.SortBySuprafataC());
				else print(serv.SortBySuprafata());
			}
			if (a == 3) {
				if (b == 1)
					print(serv.SortByTipSuprafata());
				else print(serv.SortByTipSuprafataC());
			}
			std::cout << "\n";
		}

		if (cmd == 6) {

			float spr{ 0 };
			std::cout << "1.Filtru dupa tip \n";
			std::cout << "2.Filtru suprafata  \n";
			std::cin >> a;
			if (a == 1) {
				std::cout << "Adauga tipul\n";
				std::cin >> tip;//getline(std:: cin,tip);
				if (serv.FiltruTip(tip).size() == 0)
					std::cout << "Nu exista elemente!\n";
				else print(serv.FiltruTip(tip));
				std::cout << "\n";



			}
			if (a == 2) {
				std::cout << "Adauga suprafata\n";
				std::cin >> spr;
				if (serv.FiltruSuprafata(spr).size() == 0)
					std::cout << "Nu exista elemente!\n";
				else print(serv.FiltruSuprafata(spr));
				std::cout << "\n";
			}
		}

		if (cmd == 8) {
			std::cout << "Adauga numar "; std::cin >> apartament;
			try {
				serv.AddNotificare(apartament);
			}
			catch (ValidateException& err) {
				std::cout << err;
			}

			std::cout << "In lista exista " << serv.GetAllNotificare().size() << " locatari adaugati" << "\n";
			std::cout << "\n";

		}

		if (cmd == 9) {
			if (serv.GetAllNotificare().size() == 0)
				std::cout << "Lista de notificare este goala" << "\n";
			else
				serv.Delete();

		}


		if (cmd == 10) {
			try {
				int numar{ 0 };
				std::cout << "Adaugati numarul de locatari" << "\n";
				std::cin >> numar;
				if (numar > serv.GetAll().size() || numar > (serv.GetAll().size() - serv.GetAllNotificare().size()))
					std::cout << "valoare invalida!";
				else serv.random(numar);
				std::cout << "\n";
			}
			catch (ValidateException& err) {
				std::cout << err;
			}
		}

		if (cmd == 11) {
			if (serv.GetAllNotificare().size() == 0)
				std::cout << "Lista de notificare este goala" << "\n";
			else
			{
				print(serv.GetAllNotificare());
				std::cout << "In lista exista " << serv.GetAllNotificare().size() << " locatari adaugati" << "\n";
			}
			std::cout << "\n";
		}
		if (cmd == 12) {
			int c;
			std::cout << "1.CSV \n";
			std::cout << "2.HTML\n";
			std::cin >> c;
			if (c == 1)

			{
				try {
					std::cout << "Adauga numele fisierului ";
					std::cin >> nume;
					serv.Export(nume);
				}
				catch (ValidateException& err) {
					std::cout << err;
				}

			}
			if (c == 2) {
				try {
					std::cout << "Adauga numele fisierului ";
					std::cin >> nume;
					serv.ExportHtml(nume);
				}
				catch (ValidateException& err) {
					std::cout << err;
				}
			}
		}



		if (cmd == 13) {
			std::map<string, std::pair<string, int>> dic = serv.dictionar();
			for (auto j = dic.begin(); j != dic.end(); j++) {
				std::cout << j->first << " : " << j->second.first << ":" << j->second.second << '\n';
			}
			std::cout << "\n";
		}

		if (cmd == 14) {
			try {
				serv.Undo();
			}
			catch (ValidateException& err) {
				cout << err << " ";
			}
			cout << endl;
		}

	}
	serv.Delete();
	std::cout << "bye";

}
