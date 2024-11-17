#pragma once
#include "Ship.h"
ref class Cruisers : public Ship {
private:
    static int number;
public:
    Cruisers(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name) {}
    Cruisers(Cruisers^ some_cruisers) : Ship(some_cruisers) {
        this->number = some_cruisers->number;
    }
#pragma region virtual functions

    virtual Ship^ Clone() override {
        return gcnew Cruisers(this);
    }
    static void addition_number() {
        number++;
    }
    int get_number_of_ships() override{
        return number;
    }
  
#pragma endregion



};
