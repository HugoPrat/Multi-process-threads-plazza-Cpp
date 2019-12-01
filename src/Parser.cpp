/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Parser.cpp
*/

#include <boost/algorithm/string.hpp>
#include "Parser.hpp"

Parser::Parser()
{
}

Parser::Parser(std::string &command)
{
    _cmdLine = command;
}

Parser::~Parser()
{
}

bool Parser::checkListPizza(std::string &name)
{
    static const std::string listPizza[] = {"", "regina", "margarita", "",
                                            "americana", "", "", "", "fantasia"};

    std::transform(name.begin(), name.end(), name.begin(), ::tolower); 
    for (int i = 0 ; i <= 8 ; i++) {
        if (listPizza[i] == name.c_str())
            return _cmd.type = PizzaType (i), true;
    }
    return false;
}

bool Parser::checkSizePizza(std::string &size)
{
    static const std::string pizzaSize[] = {"", "S", "M", "", "L", "", "", "", "XL",
                                    "", "", "", "", "", "", "", "XXL"};
    for (int i = 0 ; i <= 16 ; i++) {
        if (pizzaSize[i] == size.c_str())
            return _cmd.size = PizzaSize (i), true;
    }
    return false;
}

int Parser::checkNbPizza(std::string &nb)
{
    if (nb.at(0) != 'x')
        return 0;
    nb.erase(0, 1);
    if (std::atoi(nb.c_str()) <= 0 || std::atoi(nb.c_str()) > 99)
        return 0;
    return std::atoi(nb.c_str());
}

void Parser::checkCommand(std::queue<Command> &Recep)
{
    boost::split(_split, _cmdLine, [](char c){return c == ';';});

    unsigned y = 0;

    for (auto i = _split.begin() ; i++ != _split.end() ; y++) {
        if (_split.at(y)[0] == ' ')
            _split.at(y).erase(0, 1);

        std::string pizza = _split.at(y).substr(0, _split.at(y).find(" "));
        if (checkListPizza(pizza) == false) {
            std::cout << "Cannot Interpret your command" << std::endl;
            continue;
        }

        std::string size = _split.at(y).substr(pizza.length() + 1, _split.at(y).find(" ", pizza.length() + 1) - pizza.length() - 1);
        if (checkSizePizza(size) == false) {
            std::cout << "Cannot Interpret your command" << std::endl;
            continue;
        }

        std::string nb = _split.at(y).substr(_split.at(y).find_last_of(" ") + 1, _split.at(y).length());
        int number = checkNbPizza(nb);
        if (number == 0) {
            std::cout << "Cannot Interpret your command" << std::endl;
            continue;
        }

        for (int i = 0 ; i < number ; i++)
            Recep.push(_cmd);
    }
}