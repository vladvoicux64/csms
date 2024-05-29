//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#include <iostream>
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
    float comission = this->employee_->get_commission() * (float)this->computer_->get_price();
    std::cout << this->employee_->get_name() << " sold computer " << this->computer_->get_serial() << " and earned " << comission << " in comission.\n";
}

void managerial_task::complete()
{
    this->employee_->set_commission_(this->employee_->get_commission() + 0.1f);
    this->manager_->earn(500);
    std::cout << this->employee_->get_name() << " got a 0.1 comission raise and manager " << this->manager_->get_name() << " earned 500 for that.\n";

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
        ".\n" << "Is sold: " << (this->computer_->is_assembled() ? "true.\n" : "false.\n");
    std::cout << buff.str();
}

void stock_query::complete()
{
    std::cout << "There are " << computer::get_stock_count() << " computers in stock.\n";
}

employee_query::employee_query(employee *employee) : employee_(employee)
{

}

void employee_query::complete()
{
    std::stringstream buff;
    buff << "Name: " << this->employee_->get_name() << ".\n" << "Commission: " <<
         this->employee_->get_commission() << ".\n" << "Total earnings: " << this->employee_->get_earnings() <<
         ".\n";
    std::cout << buff.str();
}

const char *TypeMismatch::what()
{
    return message_.c_str();
}

TypeMismatch::TypeMismatch(std::string emp_name) : message_(emp_name + " cannot be assigned as an employee in a sales task, as he/she is a manager. Operation aborted.")
{

}

const char *ManagerMissing::what()
{
    return message_.c_str();
}

ManagerMissing::ManagerMissing(std::string emp_name) : message_(emp_name + " cannot be assigned as a manager in a task, because his/her type is not manager. Operation aborted.")
{

}

const char *AlreadySold::what()
{
    return message_.c_str();
}

AlreadySold::AlreadySold(std::string emp_name, unsigned int computer_serial) : message_(emp_name + " cannot sell computer with serial " + std::to_string(computer_serial) + ". It is assembled so it must have already been sold. Operation aborted.")
{

}
