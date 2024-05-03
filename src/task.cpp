//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#include "task.h"

task::task(employee *employee) : employee_(employee)
{

}

employee_task::employee_task(computer *computer, employee *employee) : task(employee), computer_(computer)
{

}

void employee_task::complete()
{
    if (!this->computer_->is_assembled()) {
        this->computer_->prepare_for_sale();
        this->employee_->earn(this->computer_->get_price());
    }
    //TODO throw exception because assembled => has already been sold
}

void managerial_task::complete()
{
    this->employee_->set_commission_(this->employee_->get_commission() + 0.1f);
    this->manager_->earn(500);
}

managerial_task::managerial_task(employee *manager, employee *employee) : task(employee)
{
   auto *temp = dynamic_cast<class manager *>(manager);
   if (temp) this->manager_ = temp;
   //TODO throw otherwise
}
