#pragma once
#include <vector>
#include "domain.h"
#include<algorithm>
#include <fstream>
#include"Validator.h"
#include<map>



class RepoException {
	std::vector<std::string> messages;

public:
	explicit RepoException(const std::vector<std::string>& errors) :
		messages{ errors } {};
	friend std::ostream& operator<<(std::ostream& out, const RepoException& err);
};



class AbstractRepo {
public:

	virtual void StoreLocatar(const Locatar& l) = 0;
	virtual void DeleteLocatar(const int apartamnet) = 0;
	virtual void UpdateLocatar(const int apartament, Locatar& l) = 0;
	virtual int SearchLocatar(const int apartament) = 0;
	virtual const std::vector<Locatar>& GetAll() noexcept = 0;
	virtual Locatar getLocatar(int apartament) = 0;


};


class ExceptionRepo : public AbstractRepo
{
private:
	std::map<int, Locatar> repo;
	std::vector<Locatar> vec;
	float probabilitate = 0;

public:

	ExceptionRepo(float  prob1) : probabilitate{ prob1 } {}
	void StoreLocatar(const Locatar& l) override;
	void DeleteLocatar(const int apartament)override;
	void UpdateLocatar(const int apartament, Locatar& l)override;
	int SearchLocatar(const int apartament)override;
	const std::vector<Locatar>& GetAll()  noexcept override;
	Locatar getLocatar(int apartament);

};


class Repository : public AbstractRepo
{

protected:
	std::vector <Locatar> repo;

public:
	Repository()  noexcept = default;
	Repository(const Repository& repo) = delete;

	virtual const std::vector<Locatar>& GetAll() noexcept override;
	Locatar getLocatar(const int apartament);
	virtual void StoreLocatar(const Locatar& l) override;
	virtual void UpdateLocatar(const int apartament, Locatar& l)  override;
	virtual int SearchLocatar(const int apartament) noexcept override;
	virtual void DeleteLocatar(const int apartament) override;

};
class RepoFile : public Repository
{
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();

public:
	RepoFile(std::string fName) :Repository(), fName{ fName }{
		loadFromFile();
	}

	void StoreLocatar(const Locatar& l) override {
		Repository::StoreLocatar(l);
		writeToFile();
	}

	void DeleteLocatar(const int apartament) override {
		Repository::DeleteLocatar(apartament);
		writeToFile();
	}
	void UpdateLocatar(const int apartament, Locatar& l) override {
		Repository::UpdateLocatar(apartament, l);
		writeToFile();
	}

	const std::vector<Locatar>& GetAll()  noexcept {
		
		return Repository::GetAll();
	}
	int SearchLocatar(const int apartament) noexcept override {
		return Repository::SearchLocatar(apartament);
	}
};


//Functie teste repository
void TesteRepo();
void TesteRepofile();
void TesteExceptionRepo();


