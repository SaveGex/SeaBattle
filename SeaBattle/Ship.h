#pragma once

using namespace System::Collections::Generic;
using namespace System;

ref class Ship abstract {

private:
	static int number = 0;

protected:
	//+---------------------description of the class----------------------------+
	//|i will make that for understanding where are ship.						|
	//|left and bottom point for coordinates.									|
	//|and perhaps will need to do right abd top point for more precision. -made|
	//+-------------------------------------------------------------------------+

	int length;
	String^ name;
	size_t name_size;
	//+--------ALWAYS---------+
	//|first is x, second is y|
	//+-----------------------+
	List<List<int>^>^ coordinates;
	List<List<int>^>^ hitted_coords;
	//+-----------------------------------------------+
	//|dir = 0 means directory isn't initialized	  |
	//|dir = X means the ship is set along the X-axis.|
	//|dir = Y Y-axis.								  |
	//+-----------------------------------------------+
	Char direction;
	//+--------------------------------------------------------------+
	//|generating for help of name + number(number of existing ships)|
	//+--------------------------------------------------------------+
	String^ identifier{};
	bool alive{};

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
	virtual ~Ship() {/* nothing */ }
public:
	Ship(List<List<int>^>^ coords_X_Y, int length, String^ name) : length{ length }, name{ name }, coordinates{ coords_X_Y } {
		direction = definition_of_axiss();
		name_size = name->Length;
		identifier = name + System::Convert::ToString(number);
		hitted_coords = gcnew List<List<int>^>();

		addition_number();
		are_you_alive();
	}
	Ship::Ship(Ship^ other) {
		this->length = other->length;
		this->name = other->name;
		this->name_size = other->name_size;

		this->coordinates = gcnew List<List<int>^>();
		for each (List<int> ^ innerList in other->coordinates) {
			this->coordinates->Add(gcnew List<int>(innerList));
		}
		hitted_coords = gcnew List<List<int>^>();


		this->direction = other->direction;
		this->identifier = other->identifier;
		addition_number();
		are_you_alive();
	}

	virtual Ship^ Clone() abstract;

	List<List<int>^>^ your_hitted_coords() {
		return hitted_coords;
	}
	String^ get_identifier() {
		return identifier;
	}
	Char get_Direction() {
		return direction;
	}
	virtual int get_number_of_ships() {
		return number;
	}
	int get_Length() {
		return length;
	}
	bool are_you_alive() {
		int exact_coords{};

		for each (List<int>^ one_dim_hit_arr in hitted_coords) {
			if (is_that_your_coord(one_dim_hit_arr[0], one_dim_hit_arr[1]) ) {
				exact_coords++;
			}
		}
		if (exact_coords == length) {
			alive = false;
			return false;
		}
		alive = true;
		return true;
	}


	// and there check array of coordinates the ship for return "true" if coordinates is equal or false if coords isn't equal
	virtual bool is_that_your_coord(int X, int Y) {
		for each (List<int> ^ X_and_Y in coordinates) {
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
		direction = (direction == 'X') ? 'Y' : 'X';
	}
	virtual bool operator==(Ship^ comparing_ship) {
		if (identifier == comparing_ship->get_identifier()) {
			return true;
		}
		return false;
	}
	//////void operator()(int coordX, int coordY, int length, char* name);
	//virtual void operator=(Ship Robj) = 0;
	// i want to do parent class where was that variables and info about him hits. 
	// if he still alive i should can find out about it
	virtual bool was_hitted(int X, int Y) {
		if (is_that_your_coord(X, Y)) {
			List<int>^ buf = gcnew List<int>;

			buf->Add(X);
			buf->Add(Y);

			hitted_coords->Add(buf);
			return true;
		}
		
		return false;
	}
	virtual List<List<int>^>^ your_coords() {
        return coordinates;
	}
	virtual String^ get_Name() {
		return name;
	}
};

