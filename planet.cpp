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
		_size(n), _citiesTree(n), _kingdoms(n) {
	City* cities = new City[n];
	_cities = cities;

	for (int i = 0; i < n; ++i) {
		cities[i] = City(i);
	}
	FillTree func(cities);
	_citiesTree.inOrder(func);
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
	if (citizen == NULL
			|| (citizen->inCity() != -1 && citizen->inCity() != city)) {
		return FAILURE;
	}
	if (citizen->inCity() == city) {
		return SUCCESS;
	}

	City& c2 = _cities[city];
	_citiesTree.remove(c2);
	c2._size++;
	int kingdom = _kingdoms.Find(city);
	int cap = _cities[kingdom]._capital;

	if (_cities[cap]._size < c2._size || (_cities[cap]._size == c2._size
			&& _cities[cap]._id > city)) {
		_cities[kingdom]._capital = city;
	}

	_citiesTree.insert(c2);
	citizen->joinCity(city);
	return SUCCESS;
}

StatusType Planet::JoinKingdoms(int city1, int city2) {

	int root1 = _kingdoms.Find(city1);
	int root2 = _kingdoms.Find(city2);

	City& cap1 = _cities[_cities[root1]._capital];
	City& cap2 = _cities[_cities[root2]._capital];

	if (city1 != cap1._id || city2 != cap2._id || cap1._id == cap2._id) {
		return FAILURE;
	}
	_kingdoms.Union(root1, root2);
	int newKingdom = _kingdoms.Find(city1);
	if (cap1._size > cap2._size) {
		_cities[newKingdom]._capital = cap1._id;
	} else if (cap1._size == cap2._size) {
		_cities[newKingdom]._capital = (cap1._id < cap2._id) ? cap1._id : cap2._id;
	} else {
		_cities[newKingdom]._capital = cap2._id;
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
	int kingdom = _kingdoms.Find(city);
	*capital = _cities[kingdom]._capital;
	return SUCCESS;
}

StatusType Planet::SelectCity(int k, int* city) {
	assert(city);
	if (k < 0) {
		return INVALID_INPUT;
	}
	if (k >= _size) {
		return FAILURE;
	}
	*city = _citiesTree.select(k + 1)._id;
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
	_citiesTree.inOrder(convert);
	return SUCCESS;
}

Planet::~Planet() {
	delete[] _cities;
}

Planet::City::City() :
		_id(-1), _size(0), _capital(-1) {
}

Planet::City::City(int id, int size) :
		_id(id), _size(size), _capital(_id) {
}

bool operator<(const Planet::City& city1, const Planet::City& city2) {
	if (city1._size < city2._size)
		return true;
	if (city1._size == city2._size) {
		if (city1._id < city2._id) {
			return true;
		}
	}
	return false;
}

bool operator>(const Planet::City& city1, const Planet::City& city2) {
	return city2 < city1;
}

bool operator==(const Planet::City& city1, const Planet::City& city2) {
	return city1._id == city2._id;
}

bool operator!=(const Planet::City& city1, const Planet::City& city2) {
	return !(city1 == city2);
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
