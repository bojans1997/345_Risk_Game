#include "Map.h"
#include <iostream>
#include <list>

Country::Country() {

	name = NULL;
	countryKey = NULL;
	owner = NULL;
	continentKey = NULL;
	neighbourArray = NULL;
	neighbourNum = NULL;
	army = NULL;
}

Country::Country(string name, int countryK, int* neighbourA, int continentK, int neighbourN) {

	continentKey = new int(continentK);
	Country::name = &name;
	countryKey = new int(countryK);
	owner = new string();
	neighbourNum = new int(neighbourN);
	neighbourArray = new int[neighbourN];
	army = new int(0);

	for (int i = 0; i < neighbourN; i++) {
		neighbourArray[i] = neighbourA[i];
	}

}
int Country::getNeighbourNum() {

	int x = *neighbourNum;
	return x;
}
Country::~Country() {
	delete name, countryKey, continentKey, owner, neighbourNum,army;
	delete[] neighbourArray;

}


Map::Map() {

	countryCount = NULL;
	continentCount = NULL;
	matrix = NULL;
	array1 = NULL;
	array2 = NULL;

}
Map::Map(Continent* arr1, int size1, Country* arr2, int size2) {   //size is the length of the arrays


	countryCount = new int(size2);
	continentCount = new int(size1);
	array1 = new Continent[size1];

	for (int i = 0; i < size1; i++) {

		array1[i] = arr1[i];

	}

	array2 = new Country[size2];

	for (int i = 0; i < size2; i++) {

		array2[i] = arr2[i];
	}


	matrix = new int* [size2];
	for (int i = 0; i < size2; i++)
		matrix[i] = new int[size2];
	//filling matrix with 0

	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size2; j++) {

			matrix[i][j] = 0;
		}
	}
}

void Map::setMatrix() {


	for (int i = 0; i < *countryCount; i++) {

		int* neighArray = array2[i].getNeighbours();    //getting array of neighbors
		int len = array2[i].getNeighbourNum();              //array length

		for (int j = 0; j < len; j++) {

			int key = neighArray[j];         //getting neighbor country key
			matrix[i][key] = 1;     //setting index i(current country), key(neighbor) of matrix; 1.

		}

	}


}

//checks if country1 can attack country2
bool Map::checkNeighbors(Country country1, Country country2) {

	int key1 = country1.getCountryKey();
	int key2 = country2.getCountryKey();

	if (matrix[key1][key2] == 1) {
		return true; //should be returning true here
	}
	else return false;

}
//method to print matrix
void Map::printMatrix() {

	for (int i = 0; i < *countryCount; i++) {
		std::cout << "Country" << i << ": ";
		for (int j = 0; j < *countryCount; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << endl;
	}
}
//private helper method
void Map::check(int i, int* arr) {

	arr[i] = 1;

	list<int> queue;

	for (int j = 0; j < *countryCount; j++) {

		if (matrix[i][j] == 1) {
			queue.push_front(j);
		}

	}

	while (queue.size() != 0) {
		int x = queue.back();
		queue.pop_back();
		if (arr[x] == 0) {
			check(x, arr);
		}
	}
}

//checkMap to check all countries( uses private method check)
bool Map::checkMap() {
	bool valid = true;
	int* arr;

	for (int i = 0; i < *countryCount; i++) {

		arr = new int[*countryCount];
		for (int i = 0; i < *countryCount; i++) {
			arr[i] = 0;
		}

		Map::check(i, arr);     //check method for each country

		cout << "Country " << i << ":";

		for (int k = 0; k < *countryCount; k++) {
			if (arr[k] == 0) {
				valid = false;
			}

			cout << " " << arr[k];  //printing( 1's means it can go to that country)
		}
		cout << endl;
		
		delete[] arr;
	
	}

	return valid;
}

//destructor
Map::~Map() {


	for (int i = 0; i < *countryCount; i++) {

		delete matrix[i];
	}
	
	delete[] matrix;
	delete[] array1;
	delete[]array2;
	delete countryCount;
	delete continentCount;

}

Continent::Continent() {

	name = NULL;
	conquered = NULL;
	owner = NULL;
	continentKey = NULL;
	countryNum = NULL;

}

Continent::Continent(int key, string name, int num) {

	Continent::name = new string(name);
	countryNum = new int(num);
	continentKey = new int(key);
	owner = new string();
	conquered = new bool();

}
Continent::~Continent() {

	delete countryNum;
	delete conquered;
	delete owner;
	delete name;
	delete continentKey;

}