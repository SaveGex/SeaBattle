#pragma once
#include "Ship.h"

ref class Battleship : public Ship{
private:
    static int number;
public:
	Battleship(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name){}
    bool was_hitted(int X, int Y) override {
        List<List<int>^>^ buffer = get_coord();
        for (int i = 0; i < buffer->Count; i++) {
            if (buffer[i]->default[0] == X && buffer[i]->default[1] == Y) {
                return true;
            }
        }
        return false;
    }

	bool is_that_coord(int X, int Y) override {
		return true;
	}
};