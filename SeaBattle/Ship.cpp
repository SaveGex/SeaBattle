#include "Ship.h"

Ship::Ship(List<List<int>^>^ coords_X_Y, int length, char* name) : length{ length }, name{ name }, coordinates{ coords_X_Y } {
	name_size = strlen(name);
	// i suppose what strlen begin counting including zero. Such as "123" 1-0 2-1 3-2 (value - index);
	addition_number();
}

Ship::~Ship() {
	delete[] name;
}

