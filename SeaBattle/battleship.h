#pragma once
#include "Ship.h"

ref class Battleship : public Ship{
private:
    static int number;
public:
	Battleship(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name){}
    Battleship(Battleship^ some_battleship) : Ship(some_battleship) {
        this->number = some_battleship->number;
    }
#pragma region virtual functions

    virtual Ship^ Clone() override {
        return gcnew Battleship(this);
    }
    static void addition_number() {
        number++;
    }
    int get_number_of_ships() override {
        return number;
    }
#pragma endregion



};