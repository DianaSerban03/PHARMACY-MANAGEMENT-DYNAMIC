#pragma once
#include "Domain.h"
#include "Repository.h"
#include "Validator.h"


typedef bool(*Compare)(const medicament&, const string&);
typedef int(*Sort)(const medicament&, const medicament&);



class medicamentService {

private:
	medicamentRepo repo;
	Validator valid;

public:

	medicamentService(const medicamentRepo& repo, const Validator& valid) : repo{ repo }, valid{ valid } {}

	TemplateVector<medicament> getAll();

	void addmedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ);

	void modifymedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ);

	medicament findmedicament(const string& denumire);

	void deletemedicament(const string& denumire);

	TemplateVector<medicament> filtermedicaments(const string& filterParameter, Compare function);

	TemplateVector<medicament> sortmedicaments(Sort sortFunction);





};