#pragma once
#include <string>
#include <vector>
using namespace std;

ref class Ship {

private:

protected:
	int coordX;
	int coordY;
	int length;
	char* name = nullptr;
	unsigned int name_size : 8;
	int** where_hits;
	//or char* const? nah... i am joke
	Ship(int coordX, int coordY, int length, char* name, int coord_hitX, int coord_hitY) : coordX{ coordX }, coordY{ coordY }, length{ length }, name{ name } {
		name_size = strlen(name);
		// i suppose what strlen begin counting including zero. Such as "123" 1-0 2-1 3-2 (value - index);

	}
	Ship() : Ship(0, 0, 0, nullptr, 0, 0) {}
	~Ship() {
		delete[] name;
		delete[] where_hits;
	}

public:
	void operator()(int coordX, int coordY, int length, char* name) {
		this->coordX = coordX;
		this->coordY = coordY;
		this->length = length;
		this->name = name;
		this->name_size = strlen(name);
	}
	void operator=(Ship Robj) {
		this->coordX = Robj.coordX;
		this->coordY = Robj.coordY;
		this->length = Robj.length;
		this->name = Robj.name;
		this->name_size = strlen(this->name);
	}
	// i want to do parent class where was that variables and info about him hits. 
	// if he still alive i should can find out about it
};

