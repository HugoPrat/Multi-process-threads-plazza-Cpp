/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Fantasia
*/


#include "Pizza/Fantasia.hpp"

Fantasia_P::Fantasia_P(PizzaSize size, float multi) :
    Pizza(Fantasia, size, 4 * multi)
{
    this->_recipe.push_back(DOE);
    this->_recipe.push_back(TOMATO);
    this->_recipe.push_back(EGGPLANT);
    this->_recipe.push_back(GOAT_CHEESE);
}