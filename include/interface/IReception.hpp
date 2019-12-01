/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** IReception.hpp
*/

#pragma once

struct Data
{
    double multiplier;
    int CookByKitchen;
    double refillTime;
};

class IReception {
    public:
        virtual ~IReception() = default;

        virtual void checkStruct(Data &) const = 0;
        virtual void infinitLoop() = 0;

        virtual void status() = 0;

        virtual void loadBalancing() = 0;

    protected:
};