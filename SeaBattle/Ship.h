#pragma once
#include "Field.h"

using namespace System::Collections::Generic;
using namespace System;

ref class Ship abstract{

private:
	static int number = 0;

protected:
	//+-------------------------------------------------------------------------+
	//|i will make that for understanding where are ship.						|
	//|left and bottom point for coordinates.									|
	//|and perhaps will need to do right abd top point for more precision. -made|
	//+-------------------------------------------------------------------------+

	int length;
	String^ name;
	size_t name_size;
	//+-----------------------+
	//|first is x, second is y|
	//+-----------------------+
	List<List<int>^>^ coordinates;
	//+-----------------------------------------------+
	//|dir = 0 means directory isn't initialized	  |
	//|dir = X means the ship is set along the X-axis.|
	//|dir = Y Y-axis.								  |
	//+-----------------------------------------------+
	Char direction;

	static void addition_number() {
		number++;
	}
	List<List<int>^>^ get_coord() {
		return coordinates;
	}
	Char definition_of_axiss() {// used only at initializing time
		Tuple<int, int>^ root_coordinate = Tuple::Create(coordinates[0]->default[0], coordinates[0]->default[1]);

		Char answer = '0';
		for (int i = 0; i < coordinates->Count; i++) {//just one
			if ((root_coordinate->Item1 + i == coordinates[i]->default[0] || 
				root_coordinate->Item1 - i == coordinates[i]->default[0]) &&
				root_coordinate->Item2 == coordinates[i]->default[1]
				) {
				answer = 'X';
			}
			else if ((root_coordinate->Item2 + i == coordinates[i]->default[1] || 
				root_coordinate->Item2 - i == coordinates[i]->default[1]) &&
				root_coordinate->Item1 == coordinates[i]->default[0]
				) {
				answer = 'Y';
			}
			else {
				answer = '0';
			}
		}
		
		return answer;
		
	}
	virtual ~Ship() {

	}
public:
	Ship(List<List<int>^>^ coords_X_Y, int length, String^ name) : length{ length }, name{ name }, coordinates{ coords_X_Y } {
		direction = definition_of_axiss();
		name_size = name->Length;
		
		addition_number();
	}
	Char get_Direction() {
		return direction;
	}
	int get_number_of_ships() {
		return number;
	}
	int get_Length() {
		return length;
	}
	// and there check array of coordinates the ship for return "true" if coordinates is equal or false if coords isn't equal
	virtual bool is_that_your_coord(int X, int Y) {
		for each (List<int>^ X_and_Y in coordinates) {
			if (X_and_Y[0] == X && X_and_Y[1] == Y) {
				return true;
			}
		}
		return false;
	}
	void change_coordinates(List<List<int>^>^ some_coords) {
		coordinates = some_coords;
	}
	void change_direction() {
		direction = (direction = 'X') ? 'Y' : 'X';
	}
	//////void operator()(int coordX, int coordY, int length, char* name);
	//virtual void operator=(Ship Robj) = 0;
	// i want to do parent class where was that variables and info about him hits. 
	// if he still alive i should can find out about it
	virtual bool was_hitted(int X, int Y) abstract;
	virtual List<List<int>^>^ your_coords() abstract;
	virtual String^ get_Name() abstract;
};

