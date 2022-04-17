#include "Domain.h"

//CREAREA entitatii MEDICAMENT
medicament::medicament(const string& med_denumire, const int& med_pret, const string& med_producator, const string& med_s_a) {
	this->pret = med_pret;
	this->producator = med_producator;
	this->denumire = med_denumire;
	this->subst_activ = med_s_a;
}

//Functii GET
string medicament::get_denumire() const {
	return this->denumire;
}

string medicament::get_subst_activ() const {
	return this->subst_activ;
}

string medicament::get_producator() const {
	return this->producator;
}

int medicament::get_pret() const {
	return this->pret;
}

//Functii SET

void medicament::set_denumire(const string& new_denumire) {
	this->denumire = new_denumire;
}

void medicament::set_pret(int new_value) noexcept {
	this->pret = new_value;
}

void medicament::set_subst_activ(const string& new_subst_activ) {
	this->subst_activ = new_subst_activ;
}

void medicament::set_producator(const string& new_producator) {
	this->producator = new_producator;
}

bool medicament::operator==(const medicament& other) {
	return this->denumire == other.get_denumire();
}
