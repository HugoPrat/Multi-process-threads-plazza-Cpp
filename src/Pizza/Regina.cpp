/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Regina
*/

#include "Pizza/Regina.hpp"

Regina_P::Regina_P(PizzaSize size, float multi) :
    Pizza(Regina, size, 2 * multi)
{
    this->_recipe.push_back(DOE);
    this->_recipe.push_back(TOMATO);
    this->_recipe.push_back(GRUYERE);
    this->_recipe.push_back(HAM);
    this->_recipe.push_back(MUSHROOMS);
}