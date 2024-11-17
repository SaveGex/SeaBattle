#pragma once
#include "Ship.h"
ref class Destroyers : public Ship {
private:
    static int number;
public:
    Destroyers(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name) {}
    Destroyers(Destroyers^ some_destroyers) : Ship(some_destroyers) {
        this->number = some_destroyers->number;
    }
#pragma region virtual functions



    virtual Ship^ Clone() override {
        return gcnew Destroyers(this);
    }
    static void addition_number() {
        number++;
    }
    int get_number_of_ships() override {
        return number;
    }

#pragma endregion



};

