#pragma once
#include <string>
#include "Service.h"
using namespace std;

class UI {

public:

	void runApplication();

	UI(const medicamentService& service) : service{ service } {

	}

private:

	medicamentService service;


	void UI_printOptions() const;

	void UI_addmedicament();

	void UI_deletemedicament();

	void UI_modifymedicament();

	void UI_searchmedicament();

	void UI_filtermedicaments();

	void UI_sortmedicaments();

	void UI_printData();


};