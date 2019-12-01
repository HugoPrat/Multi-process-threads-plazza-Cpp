/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Americana
*/

#include "Pizza/Americana.hpp"

Americana_P::Americana_P(PizzaSize size, float multi) :
    Pizza(Americana, size, 2 * multi)
{
    this->_recipe.push_back(DOE);
    this->_recipe.push_back(TOMATO);
    this->_recipe.push_back(GRUYERE);
    this->_recipe.push_back(STEAK);
}