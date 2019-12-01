/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen
*/

#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Reception.hpp"
#include "Kitchen.hpp"

Kitchen::Kitchen(const Data &values) :
    _actif_timing(std::chrono::steady_clock::now()),
    _refill_timing(std::chrono::steady_clock::now()),
     _actif(false), _closing(std::make_shared<int>(0)),
     _values(values)
{
    for(int i = 0; i != values.CookByKitchen; i++)
        this->_cooks.push_back(Cooks(values.multiplier));

    this->_stock.push(std::make_pair(DOE, 5));
    this->_stock.push(std::make_pair(TOMATO, 5));
    this->_stock.push(std::make_pair(GRUYERE, 5));
    this->_stock.push(std::make_pair(HAM, 5));
    this->_stock.push(std::make_pair(MUSHROOMS, 5));
    this->_stock.push(std::make_pair(STEAK, 5));
    this->_stock.push(std::make_pair(EGGPLANT, 5));
    this->_stock.push(std::make_pair(GOAT_CHEESE, 5));
    std::cout << "OPEN" << std::endl;
}

Kitchen::~Kitchen()
{
}

std::vector<Cooks> Kitchen::getCooks() const
{
    return _cooks;
}

void Kitchen::communication(fd_t &_Serv)
{
    std::string tmp;
    char buff[1024];
    Command cmdtmp;

    while (!*_closing.get()) {
        read(_Serv, buff, sizeof(buff));
        if (!buff)
            continue;
        tmp = buff;
        if (tmp == "status")
            std::cout << getStatus() << std::endl;
        else if (tmp == "pizza") {
            std::string size = std::to_string(getPizza().getSize() + getCommands().getSize());
            write(_Serv, size.c_str(), size.length());
        } else {
            cmdtmp.type = (PizzaType)std::atoi(tmp.substr(1, tmp.find(",") - 1).c_str());
            cmdtmp.size = (PizzaSize)std::atoi(tmp.substr(tmp.find(",") + 1, tmp.find("]") - tmp.find(",") - 1).c_str());
            std::cout << "created command :" << NAME[cmdtmp.type] << " " << SIZE[cmdtmp.size] << std::endl;
            pushCommand(cmdtmp);
        }
        for (int i = 0 ; buff[i] ; i++)
            buff[i] = '\0';
    }
}

void Kitchen::startComm(fd_t &fd)
{
    _communication = std::thread(&Kitchen::communication, this, std::ref(fd));
}

SafeQueu<Command> Kitchen::getCommands() const
{
    return _commands;
}

furnace_t Kitchen::getPizza() const
{
    return _furnace;
}

bool Kitchen::check_inactif()
{
    timing_t tmp = std::chrono::steady_clock::now();

    if (_commands.getSize() > 0 || _furnace.getSize() > 0) {
        _actif = true;
        return true;
    }
    if (_commands.getSize() == 0 && _furnace.getSize() == 0 && _actif) {
        _actif = false;
        _actif_timing = tmp;
        return true;
    }
    if (std::chrono::duration_cast<std::chrono::seconds>(tmp - _actif_timing).count() >= 5)
        return false;
    return true;
}

void Kitchen::Work()
{
    for (Cooks chief : _cooks) {
        if (_commands.isEmpty())
            return;
        if (chief.getStatus() == NOTHING)
            chief.work(_commands.pop(), _stock, _furnace);
    }
}

int Kitchen::getKill() const
{
    return *_closing.get();
}

std::string Kitchen::getStatus()
{
    std::stringstream ss;
    size_t size = _stock.getSize();
    int nbr = 0;

    for(size_t i = 0; i < size; i++) {
        auto tmp = _stock.pop();
        ss << FOODNAME[tmp.first] << " : " << tmp.second << std::endl;
        _stock.push(tmp);
    }
    ss << "NUMBER OF COMMANDS :" << _commands.getSize() << std::endl;
    for (auto chief : _cooks)
        ss << "Cook " << nbr++ << " : " << DOING[chief.getStatus()] << std::endl;
    return ss.str();
}

void Kitchen::pushCommand(Command add)
{
    _commands.push(add);
}

void Kitchen::refill()
{
    size_t size = _stock.getSize();

    for(size_t i = 0; i < size; i++) {
        auto tmp = _stock.pop();
        tmp.second++;
        _stock.push(tmp);
    }
}

void Kitchen::check_refill()
{
    timing_t tmp = std::chrono::steady_clock::now();

    if (std::chrono::duration_cast<std::chrono::seconds>(tmp - _refill_timing).count() >= _values.refillTime) {
        _refill_timing = tmp;
        refill();
    }
}

void Kitchen::killMe()
{
    _closing = std::make_shared<int>(1);
}

void Kitchen::PizzaDone(Pizza *yourPizza)
{
    std::cout << "Your pizza " << NAME[yourPizza->getType()] << " " << SIZE[yourPizza->getSize()] << " is ready" << std::endl;
}

void Kitchen::check_cooking()
{
    size_t size = _furnace.getSize();

    for(size_t i = 0; i < size; i++) {
        auto pizza = _furnace.pop();
        if (pizza.get()->isReady()) {
            PizzaDone(pizza.get());
            continue;
        }
        _furnace.push(pizza);
    }
}