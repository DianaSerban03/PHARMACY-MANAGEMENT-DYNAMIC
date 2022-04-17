#include "Repository.h"
#include "Errors.h"


// FIND medicine function
medicament medicamentRepo::findmedicament(const string& denumire) {
	for (int i = 0; i < medicamentList.size(); i++) {
		if (medicamentList.at(i).get_denumire() == denumire) return medicamentList.at(i);
	}
	throw Exception("medicament not found!\n");
}


//ADD medicine function
void medicamentRepo::addmedicament(const medicament& m) {
	for (int i = 0; i < medicamentList.size(); i++) {
		if (medicamentList.at(i).get_denumire() == m.get_denumire()) {
			throw Exception("Already added!\n");
		}
	}
	medicamentList.push_back(medicament(m));
}


//DELETE medicine function
void medicamentRepo::deletemedicament(const string& denumire) {
	int i = 0;
	while (i < medicamentList.size() && medicamentList.at(i).get_denumire() != denumire) {
		i++;
	}
	if (i < medicamentList.size()) medicamentList.erase(i);
	else throw Exception("medicament not found!\n");
}


//MODIFY medicine function(UPDATE)
void medicamentRepo::modifymedicament(const medicament& medicament) {
	int i = 0;
	while (i < medicamentList.size() && !(medicamentList.at(i) == medicament)) i++;
	if (i < medicamentList.size()) {
		medicamentList.at(i).set_subst_activ(medicament.get_subst_activ());
		medicamentList.at(i).set_pret(medicament.get_pret());
		medicamentList.at(i).set_producator(medicament.get_producator());
	}
	else throw Exception("medicament not found!\n");
}