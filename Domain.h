#pragma once
#include <iostream>
#include <string>
using namespace std;

class medicament {

private:

	int pret;
	string denumire;
	string subst_activ;
	string producator;


public:

	medicament(const string& med_denumire, const int& med_pret, const string& med_producator, const string& med_s_a);

	medicament() = default;

	medicament(const medicament& ot) : denumire{ ot.get_denumire() }, producator{ ot.get_producator() }, subst_activ{ ot.get_subst_activ() }, pret{ ot.get_pret() } {
		std::cout << "*";
	}

	string get_denumire() const;

	string get_producator() const;

	string get_subst_activ() const;

	int get_pret() const;

	void set_pret(int new_value) noexcept;

	void set_producator(const string& new_prod);

	void set_subst_activ(const string& new_s_s);

	void set_denumire(const string& new_denumire);

	bool operator==(const medicament& m1);

};