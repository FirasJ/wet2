#ifndef PLANET_H_
#define PLANET_H_

#include "library2.h"
#include "tree.h"
#include "hashTable.h"
#include "unionFind.h"

class Planet {
public:
	/* Empty constructor :
	 * Description:   Initializes the planet with n cities.
	 * Input:         n - Number of cities in the planet.
	 * Output:        None.
	 * Return Values: A new object of the data structure.
	 * Time Complexity: O(n).
	 */
	explicit Planet(int n);

	/* Description:   A citizen was added to the planet.
	 * Input:         citizenID - The ID of the citizen.
	 * Output:        None.
	 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
	 *                INVALID_INPUT - If citizenID<0.
	 *                FAILURE - If a citizen with citizenID already lives in
	 *                the planet, or in the case of any other problem.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(1) in amortized average.
	 */
	StatusType AddCitizen(int citizenID);

	/* Description:   A citizen with ID citizenID decides to live in city.
	 * Input:         citizenID - The ID of the citizen.
	 *                city - The ID of the city.
	 * Output:        None.
	 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
	 *                INVALID_INPUT - If citizenID<0 or city is not
	 *                an illegal city number.
	 *                FAILURE - If a citizen with same ID already lives in a
	 *                city,there is no citizen in the planet with this ID or in
	 *                case of any other error.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(log n) in average.
	 */
	StatusType MoveToCity(int citizenID, int city);

	/* Description:   Joins two kingdoms of city1 and city2 together.
	 *				  This can happen only if the cities are the kingdoms' capitals.
	 * Input:         city1 - The identifier of the 1st city.
	 *                city2 - The identifier of the 2nd city.
	 * Output:        None.
	 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
	 *                INVALID_INPUT - If either city2 or city1 are
	 *                illegal city numbers.
	 *                FAILURE - If either cities is not a kingdom capital,
	 *                both cities belong to the same capital, or in case of any
	 *                other error.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(log* n) amortized.
	 */
	StatusType JoinKingdoms(int city1, int city2);

	/* Description:   Returns the capital of the kingdom in which citizen with
	 * 					ID citizenID lives.
	 *                The capital is the city which has the maximal number of
	 *                citizens in the kingdom. In case more than one of the
	 *                cities in the kingdom have the maximal number of
	 *                citizens, the one with the
	 *                smallest index will be chosen.
	 * Input:         citizenID - The identifier of the citizen.
	 * Output:        capital - The identifier of the capital city.
	 * Return Values: INVALID_INPUT - If citizenID<0 or capital==NULL.
	 *                FAILURE - If there is no citizen in the planet with this
	 *                ID or in case of any other error.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(log* n) in amortized average.
	 */
	StatusType GetCapital(int citizenID, int* capital);

	/* Description:   Returns the city ranked in the k-th place when all the
	 * cities in the planet are ordered by size.
	 * Input:         k - The rank.
	 * Output:        city - The identifier of the k-th city.
	 * Return Values: INVALID_INPUT - If k<0 or city==NULL.
	 *                FAILURE - If there is no city in the required rank or in
	 *                case of any other error.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(log n).
	 */
	StatusType SelectCity(int k, int* city);

	/* Description:   Returns an array of the cities in the capital ranked by size.
	 * Input:         None.
	 * Output:        results - An array of size n where the cities will be written.
	 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
	 *                INVALID_INPUT - If results==NULL.
	 *                FAILURE - In case of an error.
	 *                SUCCESS - Otherwise.
	 * Time Complexity: O(n).
	 */
	StatusType GetCitiesBySize(int results[]);

	/* Destructor :
	 * Description:   Deletes the database.
	 * Input:         None.
	 * Output:        None.
	 * Return Values: None.
	 * Time Complexity: O(m+n) whereas n is the number of cities and m is the
	 * 					number of the citizens.
	 */
	~Planet();

	class City;
	class Citizen;

private:
	int _size;
	Tree<City> _cities;
	HashTable<Citizen> _citizens;
	UnionFind<City> _kingdoms;

};

class Planet::City {
public:
	City();
	City(int id);
	friend bool operator<(const City& city1, const City& city2);
	friend bool operator==(const City& city1, const City& city2);
	friend class TreeToArray;
	friend class Planet;
private:
	int _id;
	int _size;
	City* _capital;
};
/*
bool operator!=(const typename Planet::City& city1, const typename Planet::City& city2);
bool operator<(const Planet::City& city1, const Planet::City& city2);
*/
class Planet::Citizen {
public:
	Citizen(int id);
	int  inCity() const;
	void joinCity(int city);
	int operator%(int i) const;
	friend bool operator<(const Citizen& citizen1, const Citizen& citizen2);
	friend bool operator==(const Citizen& citizen1, const Citizen& citizen2);
private:
	int _id;
	int _city;
};
/*
bool operator>(const Planet::Citizen& citizen1, const Planet::Citizen& citizen2);
bool operator!=(const Planet::Citizen& citizen1, const Planet::Citizen& citizen2);
*/
#endif /* PLANET_H_ */
