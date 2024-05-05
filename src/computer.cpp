//
// Created by Voicu Ioan Vladut on 28.04.2024.
//

#include "computer.h"

unsigned computer::stock_count_ = 0;

computer::computer(unsigned int price) : price_(price), performance_rating_(0), assembled_(false), serial_(computer::generate_new_serial())
{
}

void computer::assemble()
{
    this->assembled_ = true;
}

unsigned computer::get_performance_rating() const
{
    return this->performance_rating_;
}

unsigned computer::get_price() const
{
    return this->price_;
}

bool computer::is_assembled() const
{
    return this->assembled_;
}

void computer::prepare_for_sale()
{
    this->assemble();
    this->compute_performance();
}

unsigned computer::get_stock_count()
{
    return computer::stock_count_;
}

unsigned computer::get_serial() const
{
    return this->serial_;
}

unsigned computer::generate_new_serial()
{
    return ++computer::stock_count_;
}

unsigned computer::get_next_serial()
{
    return computer::stock_count_ + 1;
}

void workstation::compute_performance()
{
    this->performance_rating_ = core_count_ * cpu_freq_ * 10;
}

workstation::workstation(unsigned int price, unsigned int cpu_freq, unsigned int core_count) : computer(price), cpu_freq_(cpu_freq), core_count_(core_count)
{
}

void server::compute_performance()
{
    this->performance_rating_ = this->ram_capacity_ * 10 + this->storage_ + this->tflops_ * 100;
}

server::server(unsigned int price, unsigned int storage, unsigned int ram_capacity, unsigned int tflops) : computer(price), storage_(storage), ram_capacity_(ram_capacity), tflops_(tflops)
{
}
