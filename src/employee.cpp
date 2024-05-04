//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#include "employee.h"

#include <utility>

float employee::get_earnings() const
{
    return this->earnings_;
}

float employee::get_commission() const
{
    return this->commission_;
}

employee::employee(std::string name, float commission) : name_(std::move(name)), earnings_(0), commission_(commission)
{

}

void employee::set_commission_(float commission)
{
    this->commission_ = commission;
}

void employee::earn(unsigned int value)
{
    this->earnings_ += (float)value * this->commission_;
}

const std::string &employee::get_name() const
{
    return name_;
}

manager::manager(std::string name) : employee(std::move(name), 0.1f)
{

}

void manager::earn(unsigned int value)
{
    this->earnings_ += (float)value;
}
