#pragma once
#include "Domain.h"
#include "VectorTemplate.h"
#include <vector>
using std::vector;


class medicamentRepo {

private:
	TemplateVector<medicament> medicamentList;

public:

	TemplateVector<medicament> getAll() {
		return medicamentList;
	}

	medicament findmedicament(const string& denumire);

	void addmedicament(const medicament& medicament);

	void deletemedicament(const string& denumire);

	void modifymedicament(const medicament& medicament);

	int length() {
		return int(medicamentList.size());
	}


};