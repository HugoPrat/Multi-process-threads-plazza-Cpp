/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Sync_cout
*/

#include "Sync_cout.hpp"

Sync_cout::Sync_cout()
{
}

Sync_cout::~Sync_cout()
{
}

void Sync_cout::print_sync(std::string buff)
{
    std::unique_lock<std::mutex> l(this->m);

    std::cout << buff << std::endl;
}