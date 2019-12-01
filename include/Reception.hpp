/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Reception
*/

#pragma once

#include <vector>
#include <memory>
#include <netinet/in.h>
#include <array>
#include "interface/IReception.hpp"
#include "Parser.hpp"

using sock_t = struct sockaddr_in;
using fd_t = int;
using pair_t = std::array<fd_t, 2>;

class Kitchen;

class Reception : public IReception {
    public:
        Reception(char **av);
        ~Reception();

        /* GETTER */
        Data getStruct() const;
        bool isOpen() const;
        void addKitchen();

        /* SETTER */
        void setIsOpen(bool);

        void checkStruct(Data &) const override;
        void infinitLoop() override;
        void loadBalancing() override;
        void status() override;
        int getPlaceInKit(fd_t &);
        void checkPair();
        void acceptKitchen();

    protected:
    private:
        Data _get;
        bool _isOpen;
        std::unique_ptr<Parser> _parsing;
        std::string _cmdLine;
        std::queue<Command> _cmd;
        sock_t _sock;
        std::vector<pair_t> _pairs;
};
