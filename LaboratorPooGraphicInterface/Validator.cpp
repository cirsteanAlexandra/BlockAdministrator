#include "validator.h"

void Validator::ValidateLocatar(const Locatar& l) {
	std::vector <std::string> messages;


	if (l.GetApartament() <= 0) messages.push_back("Numar apartament invalid!");
	if (l.GetNume().size() == 0) messages.push_back("Nume invalid!");
	if (l.GetSuprafata() < 0) messages.push_back("Suprafata invalida!");
	if (l.GetTip().size() == 0) messages.push_back("Tip invalid!");
	if (messages.size() > 0)  throw ValidateException(messages);
	
}

void Validator::ValidateAdaugare(const Locatar& l, std::vector<Locatar> list) {
	std::vector <std::string> messages;
	for (const auto& loc : list)
		if (loc.GetApartament() == l.GetApartament())
			messages.push_back("Acest locatar deja exista!");
	if (messages.size() > 0)
		throw ValidateException(messages);
}


void Validator::ValidateSearch(int nr, std::vector<Locatar> list) {

	for (const auto& loc : list)
		if (loc.GetApartament() == nr)
			return;
	std::vector <std::string> messages;
	messages.push_back("Acest Locatar nu exista!");
	throw ValidateException(messages);}


void Validator::TestAfisare() {
	std::vector <std::string> messages;

	messages.push_back("");
	throw ValidateException(messages);}

std::ostream& operator<<(std::ostream& out, const ValidateException& err) {
	for (const auto& message : err.messages)
		out << message << "\n";
	return out;
}



void TestValidator() {

	Validator val;
	
	Locatar l(1, "ana", -123, "open_space");
	try { val.ValidateLocatar(l); }
	catch (ValidateException&err)
	{
		assert(true);
		err.GetMessages();
	}
	

	Locatar l2(-1, "ana", 123, "open_space");
	try { val.ValidateLocatar(l2); }
	catch (ValidateException&) {
		assert(true);


	}

	Repository repo;
	Locatar l1(1, "vlad", 123, "open_space"); repo.StoreLocatar(l1);
	try { val.ValidateAdaugare(l1, repo.GetAll()); }
	catch (ValidateException&) {
		assert(true);


	}
	try { val.ValidateSearch(3, repo.GetAll()); }
	catch (ValidateException&) {
		assert(true);
	}
	try { val.TestAfisare(); }
	catch (ValidateException& message) {
		std::cout << message;
		
	}
}
