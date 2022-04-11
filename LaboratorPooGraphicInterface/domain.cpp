#include "domain.h"


/*
	Functie de returnare apartament
*/
int Locatar::GetApartament() const noexcept
{
	return apartament;
}

/*
	Functia de returnare suprafata apartament
*/
double Locatar::GetSuprafata() const noexcept
{
	return suprafata;
}

/*
	Functia de returnare nume locatar
*/
std::string Locatar::GetNume() const noexcept
{
	return nume;
}

/*
	Functia de returnare tip apartament
*/

std::string Locatar::GetTip() const noexcept
{
	return tip;
}

//ostream& operator<<(ostream& os, Locatar& l){os << l.apartament << " " << l.nume << " " << l.suprafata << " " << l.tip; return os;}

/*
	Functie pentru teste domain
*/
void TesteDomain() {


	Locatar l = Locatar(2, "popescu", 125, "open space");
	assert(l.GetApartament() == 2);
	assert(l.GetNume() == "popescu");
	assert(l.GetSuprafata() == 125);
	assert(l.GetTip() == "open space");
}