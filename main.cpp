#include <iostream>
#include "Testing.h"
#include "Console.h"
#include <crtdbg.h>
#include <assert.h>
#define _CRTDBG_MAP_ALLOC
using namespace std;

void start() {
	medicamentRepo repo;
	Validator valid;
	medicamentService service{ repo, valid };
	UI console{ service };
	console.runApplication();
}

int main() {
	test_all();
	start();
	_CrtDumpMemoryLeaks();
}

