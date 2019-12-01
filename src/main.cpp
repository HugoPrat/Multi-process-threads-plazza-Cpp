/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** main.cpp
*/

#include <iostream>
#include "Reception.hpp"
#include "signal.h"
#include "Kitchen.hpp"

int print_help(char *bin_name)
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t" << bin_name << " Multiplier Cook Stock" << std::endl;
    std::cout << "\n\t" << "-Multiplier => multiplier for the cooking time of the pizzas." << std::endl;
    std::cout << "\t" << "-Cook => number of cooks per kitchen." << std::endl;
    std::cout << "\t" << "-Stock => the time in milliseconds, used by the kitchen stock to replace ingredients." << std::endl;
    std::cout << "\n\t" << "Example: ./plazza 2 5 2000" << std::endl;
    return 84;
}

int main(int ac, char **av)
{
    signal(SIGPIPE, SIG_IGN);

    if (ac == 2 && (av[1] == std::string("-h") || av[1] == std::string("--help")))
        return (print_help(av[0]));
    if (ac != 4) {
        std::cout << av[0] << ": Invalid arguments. Try again with -h or --help" << std::endl;
        return 84;
    }
    try {
        Reception recep(av);
        recep.infinitLoop();
    } catch (const char *msg) {
        std::cerr << msg << std::endl;
        return 84;
    }
    return 0;
}