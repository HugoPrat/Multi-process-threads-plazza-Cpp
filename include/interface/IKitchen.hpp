/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** IKitchen.hpp
*/

#pragma once

#include "Cooks.hpp"
#include "Pizza/Pizza.hpp"

class IKitchen {
    public:
        virtual ~IKitchen() = default;

        virtual void refill() = 0;
        virtual void PizzaDone(Pizza *) = 0;

        virtual void pushCommand(Command) = 0;
        virtual void Work() = 0;

        virtual bool check_inactif() = 0;
        virtual void check_refill() = 0;
        virtual void check_cooking() = 0;
        virtual void killMe() = 0;
    
    protected:

};