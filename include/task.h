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

class employee_task : public task {
    employee *employee_;
    computer *computer_;
public:
    explicit employee_task(computer *computer, employee *employee);
    void complete() override;
};

class managerial_task : public task {
    employee *employee_;
    manager *manager_;
public:
    explicit managerial_task(employee* manager, employee *employee);
    void complete() override;
};

class employee_query : public task {
    employee *employee_;
public:
    explicit employee_query(employee *employee);
    void complete() override;
};

class computer_query : public task {
    computer *computer_;
public:
    explicit computer_query(computer *computer);
    void complete() override;
};

class stock_query : public task {
public:
    void complete() override;
};

class AlreadySold : public std::exception {
    std::string emp_name_;
    unsigned computer_serial_;
public:
    explicit AlreadySold(std::string emp_name, unsigned computer_serial);
    const char * what();
};

class ManagerMissing : public std::exception {
    std::string emp_name_;
public:
    explicit ManagerMissing(std::string emp_name);
    const char * what();
};

class TypeMismatch : public std::exception {
    std::string emp_name_;
public:
    explicit TypeMismatch(std::string emp_name);
    const char * what();

};

#endif //CSMS_TASK_H
