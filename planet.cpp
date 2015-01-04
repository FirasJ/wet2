#include "planet.h"

Planet::Planet(int n) : _n(n) {
	// TODO
}

StatusType Planet::AddCitizen(int citizenID) {
	// TODO
	return SUCCESS;
}

StatusType Planet::MoveToCity(int citizenID, int city) {
	// TODO
	return SUCCESS;
}

StatusType Planet::JoinKingdoms(int city1, int city2) {
	// TODO
	return SUCCESS;
}

StatusType Planet::GetCapital(int citizenID, int* capital) {
	// TODO
	return SUCCESS;
}

StatusType Planet::SelectCity(int k, int* city) {
	// TODO
	return SUCCESS;
}

StatusType Planet::GetCitiesBySize(int results[]) {
	// TODO
	return SUCCESS;
}

Planet::~Planet() {
	// TODO
}

Planet::City::City(int id) : _id(id), _size(0), _capital(NULL) {

}
