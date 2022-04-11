#pragma once

#include<string>
#include <assert.h>
#include <iostream>
#include <ostream>
using namespace std;


using std::cout;
class Locatar
{
	int apartament;
	std::string nume;
	double suprafata;
	std::string tip;

public:

	friend ostream& operator<<(ostream& os, Locatar& l);
	friend istream& operator>>(istream&, Locatar&);
	/*
		Functie de creare locatar
		apartament- nr. apartament
		nume- nume locatar
		suprafata- suprafata apartament
		tip- tip apartament
		postconditii: obiect de tip Locatar
	*/
	
	

	Locatar() noexcept {
		this->apartament = 0;
		this->nume = "";
		this->suprafata = 0;
		this->tip = "";
	}


	Locatar(int _apartament, const std::string _nume, double _suprafata, const std::string _tip) :
		apartament(_apartament),
		nume(_nume),
		suprafata(_suprafata),
		tip(_tip)
	{}

	Locatar& operator=(const Locatar& other) {
		this->apartament = other.apartament;
		this->nume = other.nume;
		this->suprafata = other.suprafata;
		this->tip = other.tip;
		return *this;
	}

	//Functie de returnare apartament
	int GetApartament() const noexcept;

	//Functie de returnare suprafata apartament
	double GetSuprafata() const noexcept;

	//Functie de returnare nume locatar
	std::string GetNume() const noexcept;

	//Functie de returnare tip apartament
	std::string GetTip() const noexcept;



};
//Funtie de teste Domain
void TesteDomain();
