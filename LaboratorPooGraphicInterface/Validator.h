#pragma once
#include <cctype>
#include <iostream>
#include <vector>
#include "repository.h"

class ValidateException {
	std::vector<std::string> messages;
public:
	explicit ValidateException(const std::vector<std::string>& errors) :
		messages{ errors } {};
    std::vector<std::string> GetMessages() {
		return messages;}
	friend std::ostream& operator<<(std::ostream& out, const ValidateException& err);
};
std::ostream& operator<<(std::ostream& out, const ValidateException& err);

class Validator {
public:
	void ValidateLocatar(const Locatar& l);
	void ValidateAdaugare(const Locatar& l, const std::vector<Locatar> list);
	void ValidateSearch(int nr, std::vector<Locatar> list);
	void TestAfisare();
};

// Functie de testare validator
void TestValidator();
