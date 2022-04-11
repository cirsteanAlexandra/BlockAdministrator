#pragma once

#include"repository.h"
#include "domain.h"
#include "Validator.h"
class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {  };

};
class UndoAdauga : public UndoAction
{
	Locatar locatarAdaugat;
	AbstractRepo& repo;

public:
	UndoAdauga(AbstractRepo& repo, const Locatar& l) : repo{ repo }, locatarAdaugat{ l }{}
	void doUndo() override {
		repo.DeleteLocatar(locatarAdaugat.GetApartament());
	}
};


class UndoSterge : public UndoAction
{
	Locatar locatarSterge;
	AbstractRepo& repo;

public:
	UndoSterge(AbstractRepo& repo, const Locatar& l) : repo{ repo }, locatarSterge{ l }{}
	void doUndo() override {
		repo.StoreLocatar(locatarSterge);
	}
};


class UndoModifica : public UndoAction
{
	Locatar locatarModifica;
	AbstractRepo& repo;
	const int apartament;

public:
	UndoModifica(AbstractRepo& repo, const Locatar& l, const int apartament) : repo{ repo }, locatarModifica{ l }, apartament{ apartament }{}
	void doUndo() override {
		repo.UpdateLocatar(apartament, locatarModifica);
	}
};
