/*
** EPITECH PROJECT, 2018
** CCP_plazza_2018
** File description:
** Reception.cpp
*/

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>
#include "Kitchen.hpp"
#include "Parser.hpp"
#include "Reception.hpp"

#include <sys/types.h>


#include <signal.h>

Reception::Reception(char **av) :
    _get{std::atof(av[1]), std::atoi(av[2]), std::atof(av[3]) / 1000},
    _isOpen(true),
    _parsing()
{
    checkStruct(_get);
}

Reception::~Reception()
{
}

void Reception::checkStruct(Data &_get) const
{
    if (_get.multiplier < 0)
        throw "Multiplier to low";
    if (_get.CookByKitchen <= 0 )
        throw "Number of Cook per kitchen insufficient";
    if (_get.refillTime < 0 )
        throw "refillTime to low";
}

int Reception::getPlaceInKit(fd_t &fils)
{
    char buff[1024];

    write(fils, "pizza", 5);
    read(fils, buff, sizeof(buff));
    if (!buff) {
        return 0;
    }
    return atoi(buff);
}

void Reception::status()
{
    size_t nbr = 1;


    if (_pairs.empty()) {
        std::cout << "No kitchen open" << std::endl;
        return;
    }
    for (auto i : _pairs) {
        std::cout << "Kitchen n'" << nbr++ << std::endl;
        write(i[1], "status", 6);
        std::cout << std::endl;
    }
}

void Reception::checkPair()
{
    for (std::vector<pair_t>::iterator it = _pairs.begin();
         it != _pairs.end(); ) {
        if (write(it->back(), "", 0) == -1)
            it = _pairs.erase(it);
        else
            ++it;
    }
}

void Reception::infinitLoop()
{
    while (isOpen()) {
        std::getline(std::cin, _cmdLine);
        checkPair();
        if (_cmdLine == "exit") {
            setIsOpen(false);
            continue;
        }
        if (_cmdLine == "status") {
            status();
            continue;
        }
        _parsing = std::make_unique<Parser>(_cmdLine);
        _parsing->checkCommand(_cmd);
        loadBalancing();
    }
}

void Reception::addKitchen()
{
    fd_t fd[2];

    if (socketpair(PF_LOCAL, SOCK_STREAM, 0, fd) < 0)
        throw "Error in socket pair";
    Kitchen kit(_get);
    _pairs.push_back(pair_t{{fd[0], fd[1]}});
    pid_t pid = fork();

    if (pid == -1)
        return;
    if (pid == 0) {
        close(fd[1]);
        kit.startComm(std::ref(fd[0]));
        while (kit.check_inactif()) {
            kit.check_refill();
            kit.check_cooking();
            kit.Work();
        }
        kit.killMe();
        std::cout << "CLOSING A KITCHEN" << std::endl;
        close(fd[0]);
        exit(0);
    } else {
        close(fd[0]);
        loadBalancing();
    }
}

void Reception::loadBalancing()
{
    std::string tmp;

    if (_cmd.empty())
        return;
    if (_pairs.size() == 0)
        addKitchen();
    for (auto kit : _pairs) {
        while (getPlaceInKit(kit[1]) < _get.CookByKitchen * 2 && !_cmd.empty()) {
            tmp = "[" + std::to_string(_cmd.front().type) + "," + std::to_string(_cmd.front().size) + "]";
            write(kit[1], tmp.c_str(), tmp.size());
            usleep(100);
            _cmd.pop();
        }
    }
    if (!_cmd.empty())
        addKitchen();
}

Data Reception::getStruct() const
{
    return _get;
}

bool Reception::isOpen() const
{
    return _isOpen;
}

void Reception::setIsOpen(bool get)
{
    this->_isOpen = get;
}