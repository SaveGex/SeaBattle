#include "Ship.h"

Ship::Ship(int length, char* name) :  length{ length }, name{ name } {
	// need to allocate memory
	where_hits = gcnew List<List<int>^>();
	List<int>^ CordArray = gcnew List<int>();

	CordArray->Add(coordX);
	CordArray->Add(coordY);

	where_hits->Add(CordArray);
	name_size = strlen(name);
	// i suppose what strlen begin counting including zero. Such as "123" 1-0 2-1 3-2 (value - index);
	addition_number();
}

//////Ship::Ship() : Ship::Ship(0, 0, 0, nullptr, 0, 0) {
//////	addition_number();
//////}

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

