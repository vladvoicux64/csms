//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#ifndef CSMS_TASK_H
#define CSMS_TASK_H


#include "computer.h"
#include "employee.h"

class task {
public:
    virtual ~task() = default;
    virtual void complete() = 0;
};

class employee_task : task {
    employee *employee_;
    computer *computer_;
public:
    explicit employee_task(computer *computer, employee *employee);
    void complete() override;
};

class managerial_task : task {
    employee *employee_;
    manager *manager_;
public:
    explicit managerial_task(employee* manager, employee *employee);
    void complete() override;
};


#endif //CSMS_TASK_H
