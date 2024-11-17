#pragma once
#include "Ship.h"
ref class Submarines : public Ship {
private:
    static int number;
public:
    Submarines(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name) {}
    Submarines(Submarines^ some_submarines) : Ship(some_submarines) {
        this->number = some_submarines->number;
    }
#pragma region virtual functions

    virtual Ship^ Clone() override {
        return gcnew Submarines(this);
    }
    static void addition_number() {
        number++;
    }
    int get_number_of_ships() override {
        return number;
    }

#pragma endregion



};