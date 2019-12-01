/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Pizza
*/

#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include <chrono>

enum food {
    DOE,
    TOMATO,
    GRUYERE,
    HAM,
    MUSHROOMS,
    STEAK,
    EGGPLANT,
    GOAT_CHEESE
};

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

using timing_t = std::chrono::time_point<std::chrono::steady_clock>;

const std::string NAME[] = {"", "REGINA", "MARGARITA","","AMERICANA","","","","FANTASIA"};
const std::string SIZE[] = {"","S", "M","","L","","","","XL","","","","","","","","XXL"};
const std::string FOODNAME[] = {"DOE", "TOMATO", "GRUYERE", "HAM", "MUSHROOMS", "STREAK", "EGGPLANT", "GOAT_CHEESE"};

class Pizza {
	public:
        Pizza();
		Pizza(PizzaType, PizzaSize, float);
        Pizza(const Pizza &);
        Pizza operator=(const Pizza &);
		virtual ~Pizza() = default;

        //GETTER
        short getCookingTime() const;
        PizzaType getType() const;
        PizzaSize getSize() const;
        std::vector<food> getRecipe() const;
        //

        bool isReady();
        void go_to_furnace();

	protected:
        PizzaType _type;
        PizzaSize _size;
        timing_t _timing;
        std::vector<food> _recipe;
        float _cooked_time;
        bool _cooking;
        std::mutex m;
};

using pizza_ctor_t = std::function<Pizza *(PizzaSize, float)>;