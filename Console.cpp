#include "Console.h"
#include "Errors.h"
#include <iostream>

//LAMBDA functions
int sortBydenumire(const medicament& d1, const medicament& d2) {
	return d1.get_denumire().compare(d2.get_denumire());
}

int sortBypret(const medicament& d1, const medicament& d2) {
	return d1.get_pret() > d2.get_pret();
}

int sortBysubst_activAndproducator(const medicament& d1, const medicament& d2) {
	if (d1.get_subst_activ().compare(d2.get_subst_activ()) == 0) {
		return (d1.get_producator().compare(d2.get_producator()));
	}
	else {
		return d1.get_subst_activ().compare(d2.get_subst_activ());
	}
}

bool Equalpret(const medicament& medicament, const string& pret) {
	return to_string(medicament.get_pret()) == pret;
}

bool Equalsubst_activs(const medicament& medicament, const string& subst_activ) {
	return medicament.get_subst_activ() == subst_activ;
}

string toString(const medicament& m) {
	string text;
	text.append("Denumire: ");
	text.append(m.get_denumire());
	text.append(" | Pret: ");
	text.append(to_string(m.get_pret()));
	text.append(" | Producator: ");
	text.append(m.get_producator());
	text.append(" | Substanta activa: ");
	text.append(m.get_subst_activ());
	return text;
}

void printList(TemplateVector <medicament> list) {
	if (list.size() == 0) std::cout << "Empty!\n";
	else {
		for (int i = 0; i < list.size(); i++) {
			std::cout << toString(list.at(i)) << endl;
		}
	}
	std::cout << endl;
}


//UI functions
void UI::UI_printOptions() const {
	std::cout << "\n";
	std::cout << "Console menu\n";
	std::cout << "1. Add medicament\n";
	std::cout << "2. Modify medicament\n";
	std::cout << "3. Delete medicament\n";
	std::cout << "4. Search medicament\n";
	std::cout << "5. Filter medicaments\n";
	std::cout << "6. Sort medicaments\n";
	std::cout << "7. Print data\n";
	std::cout << "0. Exit\n";
	std::cout << "\n";
}

void UI::UI_addmedicament() {
	string denumire, producator, subst_activ, pret;
	//int pret;
	std::cout << "denumire: ";
	std::cin >> denumire;
	std::cout << "pret: ";
	std::cin >> pret;
	std::cout << "producator: ";
	std::cin >> producator;
	std::cout << "subst_activ: ";
	std::cin >> subst_activ;
	int p;
	try
	{
		p = stoi(pret);
	}
	catch (...)
	{
		std::cout << "Valoare invalida";
	}
	try {
		service.addmedicament(denumire, p, producator, subst_activ);
		std::cout << "Added!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_modifymedicament() {
	string denumire, producator, subst_activ;
	int pret;
	std::cout << "denumire: ";
	std::cin >> denumire;
	std::cout << "New pret: ";
	std::cin >> pret;
	std::cout << "New producator: ";
	std::cin >> producator;
	std::cout << "New subst_activ: ";
	std::cin >> subst_activ;
	try {
		service.modifymedicament(denumire, pret, producator, subst_activ);
		std::cout << "Modified!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_deletemedicament() {
	string denumire;
	std::cout << "denumire: ";
	std::cin >> denumire;
	try {
		service.deletemedicament(denumire);
		std::cout << "Deleted!\n";
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_searchmedicament() {
	string denumire;
	std::cout << "denumire: ";
	std::cin >> denumire;
	try {
		medicament found = service.findmedicament(denumire);
		std::cout << toString(found) << endl;
	}
	catch (Exception ex) {
		std::cout << ex.getMessage() << endl;
	}
}

void UI::UI_filtermedicaments() {
	std::cout << "Filter by:\n1.pret\n2.subst_activ\n>>> ";
	string command;
	cin >> command;
	if (command == "1") {
		string pret;
		cout << "Hrs/Week: ";
		cin >> pret;
		auto list = service.filtermedicaments(pret, Equalpret);
		printList(list);
	}
	else if (command == "2") {
		string subst_activ;
		cout << "subst_activ: ";
		cin >> subst_activ;
		auto list = service.filtermedicaments(subst_activ, Equalsubst_activs);
		printList(list);
	}
	else {
		std::cout << "Invalid command!\n";
	}
}

void UI::UI_sortmedicaments() {
	std::cout << "Sort by:\n1.Denumire\n2.Pret\n3.subst_activ+producator\n>>> ";
	string command;
	std::cin >> command;
	if (command == "1") {
		auto list = service.sortmedicaments(sortBydenumire);
		printList(list);
	}
	else if (command == "2") {
		auto list = service.sortmedicaments(sortBypret);
		printList(list);
	}
	else if (command == "3") {
		auto list = service.sortmedicaments(sortBysubst_activAndproducator);
		printList(list);
	}
	else {
		std::cout << "Invalid command!\n";
	}
}

void UI::UI_printData() {
	auto list = service.getAll();
	for (int i = 0; i < list.size(); i++) {
		std::cout << toString(list.at(i)) << endl;
	}
}

void UI::runApplication() {
	bool runProgram = true;
	string command;
	while (runProgram) {
		UI_printOptions();
		std::cout << ">>>";
		std::cin >> command;
		if (command == "0") {
			std::cout << "Program ended!\n";
			runProgram = false;
		}
		else if (command == "1") {
			UI_addmedicament();
		}
		else if (command == "2") {
			UI_modifymedicament();
		}
		else if (command == "3") {
			UI_deletemedicament();
		}
		else if (command == "4") {
			UI_searchmedicament();
		}
		else if (command == "5") {
			UI_filtermedicaments();
		}
		else if (command == "6") {
			UI_sortmedicaments();
		}
		else if (command == "7") {
			UI_printData();
		}
		else {
			std::cout << "Invalid command!\n";
		}

	}
}