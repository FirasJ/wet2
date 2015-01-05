#include "planet.h"

class FillTree {
	Planet::City* cities;
	int index;
public:
	FillTree(Planet::City* cities) :
			cities(cities), index(0) {
	}
	void operator()(Planet::City& city) {
		city = cities[index++];
	}
};

Planet::Planet(int n) :
		_size(n), _cities(n) {
	City* cities = new City[n];
	for (int i = 0; i < n; ++i) {
		cities[i] = City(i);
	}
	_kingdoms = UnionFind<City>(cities, n);
	FillTree func(cities);
	_cities.inOrder(func);

	delete[] cities;
}

StatusType Planet::AddCitizen(int citizenID) {
	if (citizenID < 0) {
		return INVALID_INPUT;
	}
	_citizens.insert(citizenID);
	return SUCCESS;
}

StatusType Planet::MoveToCity(int citizenID, int city) {
	if (citizenID < 0 || city < 0 || city >= _size) {
		return INVALID_INPUT;
	}
	Citizen* citizen = _citizens.find(Citizen(citizenID));
	if (citizen == NULL || citizen->inCity() != city) {
		return FAILURE;
	}
	if(citizen->inCity() == city) {
		return SUCCESS;
	}
	City c1 = _cities.find(city)->getData(); // city in AVL
	_cities.remove(c1);
	c1._size++;
	_cities.insert(c1);

	City c2 = _kingdoms.get(city); // city in UnionFind
	c2._size++;
	City kingdom = _kingdoms.Find(city); // kingdom of city

	if(c2 > *(kingdom._capital)) {
		kingdom._capital = &c2;
	}

	citizen->joinCity(city);
	return SUCCESS;
}

StatusType Planet::JoinKingdoms(int city1, int city2) {
	City cap1 = *(_kingdoms.Find(city1)._capital);
	City cap2 = *(_kingdoms.Find(city2)._capital);
	_kingdoms.Union(city1, city2);
	City kingdom = _kingdoms.Find(city1);
	if(cap2 < cap1) {
		kingdom._capital = &cap1;
	} else {
		kingdom._capital = &cap2;
	}
	return SUCCESS;
}

StatusType Planet::GetCapital(int citizenID, int* capital) {
	assert(capital);
	Citizen* citizen = _citizens.find(Citizen(citizenID));
	if (citizen == NULL) {
		return FAILURE;
	}
	int city = citizen->inCity();
	City c = *(_kingdoms.Find(city)._capital);
	*capital = c._id;
	return SUCCESS;
}

StatusType Planet::SelectCity(int k, int* city) {
	assert(city);
	if (k >= _size) {
		return INVALID_INPUT;
	}
	*city = _cities.select(k)._id;
	return SUCCESS;
}

class TreeToArray {
	int* results;
	int index;
public:
	TreeToArray(int results[]) :
			results(results), index(0) {
	}
	void operator()(const Planet::City& data) {
		results[index++] = data._id;
	}
};

StatusType Planet::GetCitiesBySize(int results[]) {
	assert(results);
	TreeToArray convert(results);
	_cities.inOrder(convert);
	return SUCCESS;
}

Planet::~Planet() {

}

Planet::City::City() :
		_id(-1), _size(0), _capital(this) {
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

bool operator==(const Planet::City& city1, const Planet::City& city2) {
	return (city1._size == city2._size) && (city1._id == city2._id);
}

bool operator!=(const Planet::City& city1, const Planet::City& city2) {
	return !(city1 == city2);
}

bool operator>(const Planet::City& city1, const Planet::City& city2) {
	return city2 < city1;
}

Planet::Citizen::Citizen(int id) :
		_id(id), _city(-1) {
}

int Planet::Citizen::inCity() const {
	return _city;
}

bool operator<(const Planet::Citizen& citizen1,
		const Planet::Citizen& citizen2) {
	return citizen1._id < citizen2._id;
}

bool operator>(const Planet::Citizen& citizen1,
		const Planet::Citizen& citizen2) {
	return citizen2 < citizen1;
}

bool operator==(const Planet::Citizen& citizen1,
		const Planet::Citizen& citizen2) {
	return citizen1._id == citizen2._id;
}

bool operator!=(const Planet::Citizen& citizen1,
		const Planet::Citizen& citizen2) {
	return !(citizen1 == citizen2);
}

int Planet::Citizen::operator %(int i) const {
	return _id % i;
}

void Planet::Citizen::joinCity(int city) {
	_city = city;
}
