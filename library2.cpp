#include "library2.h"
#include "planet.h"
#include <new> // std::bad_alloc

#define CHECK_NULL(ptr) if (!ptr) return INVALID_INPUT

void* Init(int n) {
	Planet* DS = new Planet(n);
	return (void*)DS;
}

StatusType AddCitizen(void* DS, int citizenID) {
	CHECK_NULL(DS);
	try {
		return ((Planet*)DS)-> AddCitizen(citizenID);
	} catch(std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType MoveToCity(void* DS, int citizenID, int city) {
	CHECK_NULL(DS);
	return ((Planet*)DS)-> MoveToCity(citizenID, city);
}

StatusType JoinKingdoms(void* DS, int city1, int city2) {
	CHECK_NULL(DS);
	return ((Planet*)DS)-> JoinKingdoms(city1, city2);
}

StatusType GetCapital(void* DS, int citizenID, int* capital) {
	CHECK_NULL(DS);
	return ((Planet*)DS)-> GetCapital(citizenID, capital);
}

StatusType SelectCity(void* DS, int k, int* city) {
	CHECK_NULL(DS);
	return ((Planet*)DS)-> SelectCity(k, city);
}

StatusType GetCitiesBySize(void* DS, int results[]) {
	CHECK_NULL(DS);
	return ((Planet*)DS)-> GetCitiesBySize(results);
}

void Quit(void** DS) {
	if ( !DS || !*DS ) return;
	delete (Planet*)*DS;
	*DS = NULL;
}
