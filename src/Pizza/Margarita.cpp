/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Margarita
*/

#include "Pizza/Margarita.hpp"

Margarita_P::Margarita_P(PizzaSize size, float multi) :
    Pizza(Margarita, size, 1 * multi)
{
    this->_recipe.push_back(DOE);
    this->_recipe.push_back(TOMATO);
    this->_recipe.push_back(GRUYERE);
}