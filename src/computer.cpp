//
// Created by Voicu Ioan Vladut on 28.04.2024.
//

#include "computer.h"

computer::computer(unsigned int price) : price_(price), performance_rating_(0), assembled_(false)
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

unsigned workstation::compute_performance() const
{
    return core_count_ * cpu_freq_ * 10;
}

workstation::workstation(unsigned int price, unsigned int cpu_freq, unsigned int core_count) : computer(price), cpu_freq_(cpu_freq), core_count_(core_count)
{
    this->performance_rating_ = this->compute_performance();
}

unsigned server::compute_performance() const
{
    return this->ram_capacity_ * 10 + this->storage_ + this->tflops_ * 100;
}

server::server(unsigned int price, unsigned int storage, unsigned int ram_capacity, unsigned int tflops) : computer(price), storage_(storage), ram_capacity_(ram_capacity), tflops_(tflops)
{
    this->performance_rating_ = this->compute_performance();
}
