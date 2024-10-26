#pragma once
#include "Ship.h"

using namespace std;

ref class Battleship : public Ship{
private:

public:
	Battleship(List<List<int>^>^ coords_X_Y, int length, char* name) : Ship(coords_X_Y, length, name){}
	bool was_hitted() override {
		return true;
	}

};

