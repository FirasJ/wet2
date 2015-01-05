#include "library2.h"
#include "planet.h"
#include <new> // std::bad_alloc

#define CHECK_NULL(ptr) if (!ptr) return INVALID_INPUT

void* Init(int n) {
	try {
		Planet* DS = new Planet(n);
		return (void*) DS;
	} catch (std::bad_alloc& e) {
		return NULL;
	}
}

StatusType AddCitizen(void* DS, int citizenID) {
	CHECK_NULL(DS);
	try {
		return ((Planet*) DS)->AddCitizen(citizenID);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
}

StatusType MoveToCity(void* DS, int citizenID, int city) {
	CHECK_NULL(DS);
	try {
		return ((Planet*) DS)->MoveToCity(citizenID, city);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
}

StatusType JoinKingdoms(void* DS, int city1, int city2) {
	CHECK_NULL(DS);
	return ((Planet*) DS)->JoinKingdoms(city1, city2);
}

StatusType GetCapital(void* DS, int citizenID, int* capital) {
	CHECK_NULL(DS);

	try {
		return ((Planet*) DS)->GetCapital(citizenID, capital);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
}

StatusType SelectCity(void* DS, int k, int* city) {
	CHECK_NULL(DS);
	if (k < 0 || !city) {
		return INVALID_INPUT;
	}
	try {
		return ((Planet*) DS)->SelectCity(k, city);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
}

StatusType GetCitiesBySize(void* DS, int results[]) {
	CHECK_NULL(DS);
	if (!results) {
		return INVALID_INPUT;
	}
	try {
		return ((Planet*) DS)->GetCitiesBySize(results);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
}

void Quit(void** DS) {
	if (!DS || !*DS)
		return;
	delete (Planet*) *DS;
	*DS = NULL;
}
