//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#include <iostream>
#include <utility>
#include "task.h"


class AlreadySold : std::exception {
    std::string emp_name_;
    unsigned computer_serial_;
public:
    explicit AlreadySold(std::string emp_name, unsigned computer_serial) : emp_name_(std::move(emp_name)), computer_serial_{computer_serial} {};
    const char * what() {
        return (this->emp_name_ + " cannot sell computer with serial " + this->computer_serial_ + ". It is assembled so it must have already been sold.").c_str();
    }
};

class ManagerMissing : std::exception {
    std::string emp_name_;
public:
    explicit ManagerMissing(std::string emp_name) : emp_name_(std::move(emp_name)) {};
    const char * what() {
        return (this->emp_name_ + " cannot be assigned as a manager in a task, because his type is not manager.").c_str();
    }
};

task::task(employee *employee) : employee_(employee)
{

}

employee_task::employee_task(computer *computer, employee *employee) : task(employee), computer_(computer)
{

}

void employee_task::complete()
{
    try {
        if (!this->computer_->is_assembled()) {
            //POLIMORFISM
            this->computer_->prepare_for_sale();
            this->employee_->earn(this->computer_->get_price());
        } else
        throw AlreadySold(this->employee_->get_name(), this->computer_->get_serial());
    }
    catch (AlreadySold &excp)
    {
        std::cerr << excp.what();
        throw;
    }
}

void managerial_task::complete()
{
    this->employee_->set_commission_(this->employee_->get_commission() + 0.1f);
    this->manager_->earn(500);
}

managerial_task::managerial_task(employee *manager, employee *employee) : task(employee)
{
    try {
        auto *temp = dynamic_cast<class manager *>(manager);
        if (temp) this->manager_ = temp;
        else throw ManagerMissing(manager->get_name());
    }
    catch (ManagerMissing &excp)
    {
        std::cerr << excp.what();
        throw;
    }
}
