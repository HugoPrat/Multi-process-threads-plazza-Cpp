/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Pizza
*/

#include "Pizza/Pizza.hpp"

Pizza::Pizza(PizzaType type, PizzaSize size, float time) :
    _type(type), _size(size), _cooked_time(time), _cooking(false)
{
}

Pizza::Pizza()
{}

Pizza::Pizza(const Pizza &a)
{
    _type = a._type;
    _size = a._size;
    _timing = a._timing;
    _recipe = a._recipe;
    _cooked_time = a._cooked_time;
    _cooking = a._cooking;
}

Pizza Pizza::operator=(const Pizza &a)
{
    Pizza tmp(a);
    return tmp;
}

short Pizza::getCookingTime() const
{
    return _cooked_time;
}

PizzaType Pizza::getType() const
{
    return _type;
}

PizzaSize Pizza::getSize() const
{
    return _size;
}

std::vector<food> Pizza::getRecipe() const
{
    return _recipe;
}

void Pizza::go_to_furnace()
{
    std::unique_lock<std::mutex> l(this->m);

    _timing = std::chrono::steady_clock::now();
    _cooking = true;
}

bool Pizza::isReady()
{
    auto tmp = std::chrono::steady_clock::now();

    if (!_cooking)
        return false;

    if (std::chrono::duration_cast<std::chrono::seconds>(tmp - _timing).count() >= _cooked_time)
        return true;
    return false;
}