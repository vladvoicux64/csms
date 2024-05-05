//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#include <iostream>
#include <utility>
#include <sstream>
#include "task.h"

employee_task::employee_task(computer *computer, employee *employee) : employee_(employee), computer_(computer)
{
    if (dynamic_cast<manager *>(employee)) throw TypeMismatch(employee->get_name());
    if (computer->is_assembled()) throw AlreadySold(this->employee_->get_name(), this->computer_->get_serial());

}

void employee_task::complete()
{
    //POLIMORFISM
    this->computer_->prepare_for_sale();
    this->employee_->earn(this->computer_->get_price());
}

void managerial_task::complete()
{
    this->employee_->set_commission_(this->employee_->get_commission() + 0.1f);
    this->manager_->earn(500);
}

managerial_task::managerial_task(employee *manager, employee *employee) : employee_(employee)
{
    auto *temp = dynamic_cast<class manager *>(manager);
    if (temp) this->manager_ = temp;
    else throw ManagerMissing(manager->get_name());
}

computer_query::computer_query(computer *computer) : computer_(computer)
{

}

void computer_query::complete()
{
    std::stringstream buff;
    buff << "Serial: " << this->computer_->get_serial() << ".\n" << "Price: " <<
        this->computer_->get_price() << ".\n" << "Perf. rating: " << this->computer_->get_performance_rating() <<
        ".\n\n";
    std::cout << buff.str();
}

void stock_query::complete()
{
    std::cout << computer::get_stock_count();
}

employee_query::employee_query(employee *employee) : employee_(employee)
{

}

void employee_query::complete()
{
    std::stringstream buff;
    buff << "Name: " << this->employee_->get_name() << ".\n" << "Commission: " <<
         this->employee_->get_commission() << ".\n" << "Total earnings: " << this->employee_->get_earnings() <<
         ".\n\n";
    std::cout << buff.str();
}

const char *TypeMismatch::what()
{
    return (this->emp_name_ + " cannot be assigned as an employee in a sales task, as he is a manager. Operation aborted.").c_str();
}

TypeMismatch::TypeMismatch(std::string emp_name) : emp_name_(std::move(emp_name))
{

}

const char *ManagerMissing::what()
{
    return (this->emp_name_ + " cannot be assigned as a manager in a task, because his type is not manager. Operation aborted.").c_str();
}

ManagerMissing::ManagerMissing(std::string emp_name) : emp_name_(std::move(emp_name))
{

}

const char *AlreadySold::what()
{
    return (this->emp_name_ + " cannot sell computer with serial " + std::to_string(this->computer_serial_) + ". It is assembled so it must have already been sold. Operation aborted.").c_str();
}

AlreadySold::AlreadySold(std::string emp_name, unsigned int computer_serial) : emp_name_(std::move(emp_name)), computer_serial_{computer_serial}
{

}
