/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** SafeQueu
*/

#pragma once

#include <queue>
#include <mutex>

template<typename T>
class SafeQueu {
        public:
        	SafeQueu();
            SafeQueu(const SafeQueu &);
        	virtual ~SafeQueu() = default;
            virtual void push(T);
            virtual bool tryPop(T &);
            T pop();

            int getSize() const;
            bool isEmpty();

	private:
            std::mutex m;
            std::queue<T> stock;
};
template<typename T>
SafeQueu<T>::SafeQueu()
{}

template<typename T>
SafeQueu<T>::SafeQueu(const SafeQueu<T> &patron)
{
    this->stock = patron.stock;
}

template<typename T>
int SafeQueu<T>::getSize() const
{
    return stock.size();
}

template<typename T>
void SafeQueu<T>::push(T value)
{
    std::unique_lock<std::mutex> l(this->m);

    this->stock.push(value);
}

template<typename T>
bool SafeQueu<T>::tryPop(T &res)
{
    std::unique_lock<std::mutex> l(this->m);

    if (this->stock.empty())
        return false;
    res = this->stock.front();
    this->stock.pop();
    return true;
}

template<typename T>
bool SafeQueu<T>::isEmpty()
{
    return this->stock.empty();
}

template<typename T>
T SafeQueu<T>::pop()
{
    std::unique_lock<std::mutex> l(this->m);
    T tmp;

    tmp = this->stock.front();
    this->stock.pop();
    return tmp;
}