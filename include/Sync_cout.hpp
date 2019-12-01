/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Sync_cout
*/

#pragma once

#include <mutex>
#include <iostream>

class Sync_cout {
	public:
		Sync_cout();
		~Sync_cout();

        void print_sync(std::string );
    
    private:
        std::mutex m;
};