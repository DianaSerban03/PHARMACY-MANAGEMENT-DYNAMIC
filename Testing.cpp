#include "Testing.h"
#include "Domain.h"
#include "Repository.h"
#include "Errors.h"
#include "Validator.h"
#include "Service.h"
#include "VectorTemplate.h"
#include <iostream>
#include <assert.h>

//DOMAIN TESTS
void test_domain() {
	medicament d1 = { "I", 20, "R", "I" };
	assert(d1.get_denumire() == "I");
	assert(d1.get_pret() == 20);
	assert(d1.get_producator() == "R");
	assert(d1.get_subst_activ() == "I");

	d1.set_pret(40);
	d1.set_denumire("E");
	d1.set_producator("U");
	d1.set_subst_activ("S");

	assert(d1.get_denumire() == "E");
	assert(d1.get_pret() == 40);
	assert(d1.get_producator() == "U");
	assert(d1.get_subst_activ() == "S");
}

void test_operator() {
	medicament d1{ "I", 30, "R", "S" };
	medicament d2{ "I", 40, "S", "D" };
	assert(d1 == d2);
}


//REPOSITORY TESTS
void test_add_repo() {
	medicamentRepo repo;
	medicament d1{ "I", 20, "R", "G" };
	repo.addmedicament(d1);
	auto list = repo.getAll();
	assert(list.size() == 1);
	try {
		repo.addmedicament(d1);
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "Already added!\n");
	}
}

void test_delete_repo() {
	medicament d1{ "I", 20, "R", "G" };
	medicament d2{ "R", 30, "U", "P" };
	medicament d3{ "C", 10, "S", "N" };

	medicamentRepo repo;

	repo.addmedicament(d1);
	repo.addmedicament(d2);
	repo.addmedicament(d3);

	try {
		repo.deletemedicament("B");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "medicament not found!\n");
	}

	repo.deletemedicament("I");
	auto list = repo.getAll();
	assert(list.size() == 2);
	assert(list.at(0).get_denumire() == "R");
	assert(list.at(1).get_denumire() == "C");

}

void test_modify_repo() {
	medicamentRepo repo;
	medicament d1{ "I", 20, "R", "N" };
	medicament d2{ "I", 30, "U", "O" };
	medicament d3{ "C", 12, "s", "S" };
	repo.addmedicament(d1);
	repo.modifymedicament(d2);
	auto list = repo.getAll();
	assert(list.size() == 1);
	assert(list.at(0).get_pret() == 30);
	assert(list.at(0).get_subst_activ() == "O");
	try {
		repo.modifymedicament(d3);
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "medicament not found!\n");
	}
}

void test_find_repo() {
	medicament d1{ "I", 20, "R", "G" };
	medicament d2{ "R", 30, "U", "P" };
	medicament d3{ "C", 10, "S", "N" };

	medicamentRepo repo;

	repo.addmedicament(d1);
	repo.addmedicament(d2);
	repo.addmedicament(d3);

	assert(repo.findmedicament("R") == d2);
	try {
		repo.findmedicament("s");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "medicament not found!\n");
	}

}


//VALIDATOR TEST
void test_validator() {
	Validator validator;
	validator.validateData("Nume", 10, "producatorValid", "asdasd");
	try {
		validator.validateData("", -5, "", "");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "denumire is invalid!\npret invalid!\nproducator is invalid!\nsubst_activ denumire invalid!\n");
	}
}


//SERVICE TESTS
void test_add_service() {
	medicamentRepo repo;
	Validator valid;
	medicamentService service{ repo, valid };
	assert(repo.length() == 0);
	service.addmedicament("i", 20, "r", "L");
	service.addmedicament("m", 10, "r", "B");
	try {
		service.addmedicament("i", 11, "s", "d");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "Already added!\n");
	}
	try {
		service.addmedicament("", 22, "", "");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "denumire is invalid!\nproducator is invalid!\nsubst_activ denumire invalid!\n");
	}
}

void test_modify_service() {
	medicamentRepo repo;
	Validator validator;
	medicamentService service{ repo, validator };
	service.addmedicament("I", 20, "CS", "SS");
	service.addmedicament("M", 30, "CSS", "SSS");
	service.modifymedicament("I", 10, "s", "C");
	assert(service.getAll().at(0).get_pret() == 10);
	try {
		service.modifymedicament("I", -2, "123", "456");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "pret invalid!\nproducator is invalid!\nsubst_activ denumire invalid!\n");
	}

	try {
		service.modifymedicament("w", 60, "a", "b");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "medicament not found!\n");
	}


}

void test_find_service() {
	medicamentRepo repo;
	Validator validator;
	medicamentService service{ repo, validator };

	medicament d1{ "I", 20, "R", "G" };
	medicament d2{ "M", 30, "U", "P" };
	medicament d3{ "C", 10, "S", "N" };

	service.addmedicament("I", 20, "CS", "SS");
	service.addmedicament("M", 30, "CSS", "SSS");

	assert(service.findmedicament("M") == d2);

	try {
		service.findmedicament("Fake1");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "denumire is invalid!\n");
	}

	try {
		service.findmedicament("Fake");
		//assert(false);
	}
	catch (Exception ex) {
		assert(ex.getMessage() == "medicament not found!\n");
	}

}

void test_delete_service() {
	medicamentRepo repo;
	Validator validator;
	medicamentService service{ repo, validator };
	service.addmedicament("I", 20, "CS", "SS");
	service.addmedicament("M", 30, "CSS", "SSS");
	service.addmedicament("L", 5, "H", "J");

	service.deletemedicament("M");
	assert(service.getAll().size() == 2);

	try {
		service.deletemedicament("111");
		//assert(false);
	}
	catch (Exception ex) {
		assert("denumire is invalid!\n");
	}

	try {
		service.deletemedicament("A");
		//assert(false);
	}
	catch (Exception ex) {
		assert("medicament not found!\n");
	}
}

bool EqualpretTest(const medicament& medicament, const string& pret) {
	return to_string(medicament.get_pret()) == pret;
}

bool Equalsubst_activsTest(const medicament& medicament, const string& subst_activ) {
	return medicament.get_subst_activ() == subst_activ;
}

void test_filter_service() {
	medicamentRepo repo;
	Validator valid;
	medicamentService service{ repo, valid };
	service.addmedicament("I", 10, "CS", "I");
	service.addmedicament("S", 20, "CS", "I");
	service.addmedicament("L", 10, "CS", "HELLO");
	service.addmedicament("A", 20, "CS", "HELLO");

	auto list = service.filtermedicaments("I", Equalsubst_activsTest);

	assert(list.size() == 2);
	assert(list.at(0).get_denumire() == "I");

	auto list2 = service.filtermedicaments("20", EqualpretTest);

	assert(list2.size() == 2);
	assert(list2.at(0).get_denumire() == "S");
}

int sortBydenumireTest(const medicament& d1, const medicament& d2) {
	return d1.get_denumire().compare(d2.get_denumire());
}

int sortBypretTest(const medicament& d1, const medicament& d2) {
	return d1.get_pret() > d2.get_pret();
}

int sortBysubst_activAndproducatorTest(const medicament& d1, const medicament& d2) {
	if (d1.get_subst_activ().compare(d2.get_subst_activ()) == 0) {
		return (d1.get_producator().compare(d2.get_producator()));}
	else {
		return d1.get_subst_activ().compare(d2.get_subst_activ());
	}
}

void test_sort_service() {
	medicamentRepo repo;
	Validator valid;
	medicamentService service{ repo, valid };
	service.addmedicament("I", 10, "A", "B");
	service.addmedicament("S", 30, "B", "D");
	service.addmedicament("L", 40, "D", "A");
	service.addmedicament("A", 20, "C", "B");

	auto list = service.sortmedicaments(sortBydenumireTest);
	auto list2 = service.sortmedicaments(sortBypretTest);
	auto list3 = service.sortmedicaments(sortBysubst_activAndproducatorTest);

	assert(list.size() == 4);
	assert(list.at(0).get_denumire() == "A");
	assert(list.at(3).get_denumire() == "S");

	assert(list2.size() == 4);
	assert(list2.at(1).get_denumire() == "A");
	assert(list2.at(2).get_denumire() == "S");

	assert(list3.size() == 4);
	assert(list3.at(0).get_denumire() == "L");
	assert(list3.at(1).get_denumire() == "I");

}


//DYNAMIC TEST
void test_dynamic_vector() {
	TemplateVector<int> intregi;
	assert(intregi.size() == 0);
	for (int i = 0; i < 20; i++) {
		intregi.push_back(i);
	}
	assert(intregi.size() == 20);
	assert(intregi.at(3) == 3);

}


void test_all() {
	std::cout << "Started testing..\n";
	test_domain();
	test_operator();
	test_add_repo();
	test_delete_repo();
	test_modify_repo();
	test_find_repo();
	test_validator();
	test_add_service();
	test_modify_service();
	test_find_service();
	test_delete_service();
	test_filter_service();
	test_sort_service();
	test_dynamic_vector();
	std::cout << "Finished testing!\n";
}
