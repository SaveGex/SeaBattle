#pragma once
#include <string>
#include "Field.h"

using namespace System::Collections::Generic;


ref class Ship {

private:

protected:
	//i will make that for understanding where are ship.
	//left and bottom point for coordinates.
	//and perhaps will need to do right abd top point for more precision. -made


	int length;
	char* name = nullptr;
	//or char* const? nah... i am joke
	size_t name_size;
	List<List<int>^>^ coordinates;
	// first is x, second is y

	static int number = 0;
	static void addition_number() {
		number++;
	}
	List<List<int>^>^ get_coord() {
		return coordinates;
	}
	virtual ~Ship();
public:
	Ship(List<List<int>^>^ coords_X_Y, int length, char* name);
	virtual bool is_that_coord(int X, int Y) = 0; // and there check array of coordinates the ship for return "true" if coordinates is equal or false if coords isn't equal
	Field field;
	//////void operator()(int coordX, int coordY, int length, char* name);
	//virtual void operator=(Ship Robj) = 0;
	// i want to do parent class where was that variables and info about him hits. 
	// if he still alive i should can find out about it
	virtual bool was_hitted(int X, int Y) = 0;
};

