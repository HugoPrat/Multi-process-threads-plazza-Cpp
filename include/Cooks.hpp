/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Cooks
*/

#pragma once

#include <thread>
#include <memory>
#include "SafeQueu.hpp"
#include "Pizza/Pizza.hpp"

using Stock_t = SafeQueu<std::pair<food, short>>;

enum doing {
    NOTHING,
    COOKING
};

struct Command
{
    PizzaType type;
    PizzaSize size;
};

const std::string DOING[] = {"NOTHING", "COOKING"};

class Cooks {
    public:
        Cooks(float);
        Cooks(const Cooks &);
        ~Cooks() = default;

        bool isWorking() const;
        void join();
        enum doing getStatus() const;
        bool haveIngredients(std::vector<food>, Stock_t &);
        void takeIngredients(std::vector<food>, Stock_t &);
        void work(Command, Stock_t &, SafeQueu<std::shared_ptr<Pizza>> &);
        void makePizza(Stock_t &, SafeQueu<std::shared_ptr<Pizza>> &);

    private:
        std::thread _thread;
        enum doing _status;
        float _multiplier;
        std::shared_ptr<Pizza> _hand;
};
