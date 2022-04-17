#include "Validator.h"
#include "Errors.h"
#include <string>

bool validString(string str) {
	if (str.size() == 0) return false;
	for (int i = 0; i < str.size(); i++) {
		if (!((str.at(i) >= 'a' && str.at(i) <= 'z') || (str.at(i) >= 'A' && str.at(i) <= 'Z'))) return false;
	}
	return true;
}

void Validator::validateData(string denumire, int pret, string producator, string subst_activ) {
	string errors;

	if (validString(denumire) == false) errors.append("denumire is invalid!\n");
	if (pret <= 0) errors.append("pret invalid!\n");
	if (validString(producator) == false) errors.append("producator is invalid!\n");
	if (validString(subst_activ) == false) errors.append("subst_activ denumire invalid!\n");
	if (errors.size() != 0) throw Exception(errors);
}