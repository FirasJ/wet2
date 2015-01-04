#include "planet.h"

Planet::Planet(int n) :
		_cities(n) {
	City** cities = new City*[n];
	for (int i = 0; i < n; ++i) {
		cities[i] = new City(i);
	}

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

Planet::City::City(int id) :
		_id(id), _size(0), _capital(this) {
}

bool operator<(const Planet::City& city1, const Planet::City& city2) {
	if (city1._size < city2._size)
		return true;
	if (city1._size == city2._size) {
		if (city1._id > city2._id) {
			return true;
		}
	}
	return false;
}

bool operator>(const Planet::City& city1, const Planet::City& city2) {
	if (city1._size > city2._size)
		return true;
	if (city1._size == city2._size) {
		if (city1._id < city2._id) {
			return true;
		}
	}
	return false;
}

Planet::Citizen::Citizen(int id) :
		_id(id), _isCitizen(false) {
}

bool Planet::Citizen::inCity() const {
	return _isCitizen;
}
