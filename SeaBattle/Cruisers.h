#pragma once
#include "Ship.h"
ref class Cruisers : public Ship {
private:
    static int number;
public:
    Cruisers(List<List<int>^>^ coords_X_Y, int length, String^ name) : Ship(coords_X_Y, length, name) {}

#pragma region virtual functions

    bool was_hitted(int X, int Y) override {
        List<List<int>^>^ buffer = get_coord();
        for (int i = 0; i < buffer->Count; i++) {
            if (buffer[i]->default[0] == X && buffer[i]->default[1] == Y) {
                return true;
            }
        }
        return false;
    }


    static void addition_number() {
        number++;
    }
    int get_number_of_ships() {
        return number;
    }
    bool is_that_coord(int X, int Y) override {
        return true;
    }

    List<List<int>^>^ where_are_you() override {
        return coordinates;
    }
    String^ getName() override {
        return name;
    }


#pragma endregion



};
