#include "Service.h"

//ALL medicines
TemplateVector<medicament> medicamentService::getAll() {
	return repo.getAll();
}


//ADD medicine
void medicamentService::addmedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ) {
	valid.validateData(denumire, pret, producator, subst_activ);
	medicament newmedicament{ denumire, pret, producator, subst_activ };
	repo.addmedicament(newmedicament);
}

//MODIFY medicine
void medicamentService::modifymedicament(const string& denumire, const int& pret, const string& producator, const string& subst_activ) {
	valid.validateData(denumire, pret, producator, subst_activ);
	medicament modifiedmedicament{ denumire, pret, producator, subst_activ };
	repo.modifymedicament(modifiedmedicament);
}

//FIND medicine
medicament medicamentService::findmedicament(const string& denumire) {
	valid.validateData(denumire, 1, "a", "a");
	return repo.findmedicament(denumire);
}


//DELETE medicine
void medicamentService::deletemedicament(const string& denumire) {
	int validpret = 1;
	string validdenumire = "A";
	string validproducator = "T";
	valid.validateData(denumire, validpret, validproducator, validdenumire);
	repo.deletemedicament(denumire);
}


//FILTER -> find all medicines with a certain request
TemplateVector<medicament> medicamentService::filtermedicaments(const string& filterParameter, Compare function) {
	TemplateVector <medicament> result;
	TemplateVector <medicament> list = repo.getAll();
	for (int i = 0; i < list.size(); i++) {
		medicament currentD;
		currentD.set_pret(list.at(i).get_pret());
		currentD.set_denumire(list.at(i).get_denumire());
		currentD.set_producator(list.at(i).get_producator());
		currentD.set_subst_activ(list.at(i).get_subst_activ());
		if (function(currentD, filterParameter)) result.push_back(currentD);
	}
	return result;
}


//SORT medicines by customer requirement
TemplateVector <medicament> medicamentService::sortmedicaments(Sort sortFunction) {
	TemplateVector <medicament> result;
	TemplateVector<medicament> list = repo.getAll();
	for (int i = 0; i < list.size(); i++) {
		result.push_back(medicament(list.at(i)));
	}
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 0; i < result.size() - 1; i++) {
			if (sortFunction(result.at(i), result.at(i + 1)) > 0) {
				result.exchange(i, i + 1);
				sorted = false;
			}
		}
	}
	return result;
}

