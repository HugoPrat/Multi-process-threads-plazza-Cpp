/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Cooks
*/

#include <unordered_map>
#include "Cooks.hpp"
#include "Kitchen.hpp"
#include "Pizza/Regina.hpp"
#include "Pizza/Margarita.hpp"
#include "Pizza/Americana.hpp"
#include "Pizza/Fantasia.hpp"

Cooks::Cooks(float multi) :
    _status(NOTHING), _multiplier(multi)
{
}

Cooks::Cooks(const Cooks &cpy)
{
    _status = cpy._status;
    _multiplier = cpy._multiplier;
}

void Cooks::join()
{
    this->_thread.join();
}

enum doing Cooks::getStatus() const
{
    return _status;
}

bool Cooks::isWorking() const
{
    if (this->_thread.joinable())
        return true;
    return false;
}

bool Cooks::haveIngredients(std::vector<food> recipe, Stock_t &stock)
{
    bool flag = true;

    for (auto ingre : recipe) {
        Stock_t tmp = stock;
        flag = true;
        while (!tmp.isEmpty()) {
            auto aliments = tmp.pop();
            if (aliments.first == ingre && aliments.second >= 1)
                flag = false;
        }
        if (flag)
            return false;
    }
    return true;
}

void Cooks::takeIngredients(std::vector<food> recipe, Stock_t &stock)
{
    for (auto ingre : recipe) {
        auto tmp = stock.pop();
        while (tmp.first != ingre) {
            stock.push(tmp);
            tmp = stock.pop();
        }
        tmp.second--;
        stock.push(tmp);
    }
}

void Cooks::makePizza(Stock_t &stock, furnace_t &furnace)
{
    while (!haveIngredients(_hand.get()->getRecipe(), stock));

    this->takeIngredients(_hand.get()->getRecipe(), stock);
    furnace.push(_hand);
    _hand.get()->go_to_furnace();
}

void Cooks::work(Command toDo, Stock_t &stock, furnace_t &furnace)
{
    std::unordered_map<PizzaType, pizza_ctor_t> factory = {
        {Regina, [](PizzaSize size, float mul) {return new Regina_P(size, mul);}},
        {Margarita, [](PizzaSize size, float mul) {return new Margarita_P(size, mul);}},
        {Fantasia, [](PizzaSize size, float mul) {return new Fantasia_P(size, mul);}},
        {Americana, [](PizzaSize size, float mul) {return new Americana_P(size, mul);}}
    };

    this->_status = COOKING;
    _hand = std::shared_ptr<Pizza>(factory[toDo.type](toDo.size, _multiplier));
    this->_thread = std::thread(&Cooks::makePizza, this, std::ref(stock), std::ref(furnace));
    this->_thread.join();
    this->_status = NOTHING;
}