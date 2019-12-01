/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Parser.hpp
*/

#pragma once

#include <string>
#include <iostream>
#include "Cooks.hpp"

class Parser {
    public:
        Parser();
        Parser(std::string&);
        ~Parser();

        void checkCommand(std::queue<Command> &);
        bool checkListPizza(std::string &);
        bool checkSizePizza(std::string &);
        int checkNbPizza(std::string &);

    private:
        std::string _cmdLine;
        std::vector<std::string> _split;
        Command _cmd;
    protected:
};