#include "Ship.h"

Ship::Ship(List<List<int>^>^ coords_X_Y, int length, char* name) :  length{ length }, name{ name } {
	where_hits = gcnew List<List<int>^>;

	for (int i = 0; i < this->length; i++) {
		where_hits[i] = gcnew List<int>();
	}
	
	coordinates = gcnew List<List<int>^>;
	for (int i = 0; i < coords_X_Y->Count; i++) {
		coordinates[i] = gcnew List<int>;
		for (int j = 0; j < 2; j++) {
			//first always is X. And after X will be Y!
			coordinates[i]->AddRange(coords_X_Y[i]);
		}
	}

	name_size = strlen(name);
	// i suppose what strlen begin counting including zero. Such as "123" 1-0 2-1 3-2 (value - index);
	addition_number();
}

Ship::~Ship() {
	delete[] name;
	delete[] where_hits;
}

//////void Ship::operator()(int coordX, int coordY, int length, char* name) {
//////	this->LPositionX = coordX;
//////	this->LPositionY = coordY;
//////	this->length = length;
//////	this->name = name;
//////	this->name_size = strlen(name);
//////}

//void Ship::operator=(Ship Robj) {
//	this->LPositionX = Robj.LPositionX;
//	this->LPositionY = Robj.LPositionY;
//	this->length = Robj.length;
//	this->name = Robj.name;
//	this->name_size = strlen(this->name);
//}

