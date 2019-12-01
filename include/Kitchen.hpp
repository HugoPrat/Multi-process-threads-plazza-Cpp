/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen
*/

#pragma once

#include "interface/IKitchen.hpp"
#include "Reception.hpp"
#include "SafeQueu.hpp"


using furnace_t = SafeQueu<std::shared_ptr<Pizza>>;

class Kitchen : public IKitchen {
	public:
		Kitchen(const Data &);
		~Kitchen();

        std::string getStatus();
        void refill() final;
        void PizzaDone(Pizza *) final;

        /* GETTER */
        std::vector<Cooks> getCooks() const;
        SafeQueu<Command> getCommands() const;
        furnace_t getPizza() const;
        int getKill() const;
        fd_t getFd() const;

        void pushCommand(Command) final;
        bool check_inactif() final;
        void Work() final;
        void check_refill() final;
        void check_cooking() final;
        void communication(fd_t&);
        void startComm(fd_t&);

        void killMe() final;

    private:
        std::vector<Cooks> _cooks;
        Stock_t _stock;
        SafeQueu<Command> _commands;
        furnace_t _furnace;
        timing_t _actif_timing;
        timing_t _refill_timing;
        bool _actif;
        std::shared_ptr<int> _closing;
        Data _values;
        std::thread _communication;
};
