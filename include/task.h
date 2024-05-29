//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#ifndef CSMS_TASK_H
#define CSMS_TASK_H


#include "computer.h"
#include "employee.h"
#include "computerbox.h"
#include <memory>

class task {
public:
    virtual ~task() = default;
    virtual void complete() = 0;
};

class employee_task : public task {
    std::shared_ptr<employee> employee_;
    std::shared_ptr<computer> computer_;
public:
    explicit employee_task(const std::shared_ptr<computer>& computer, const std::shared_ptr<employee>& employee);
    void complete() override;
};

class managerial_task : public task {
    std::shared_ptr<employee> employee_;
    std::shared_ptr<manager> manager_;
public:
    explicit managerial_task(const std::shared_ptr<employee>& manager, std::shared_ptr<employee> employee);
    void complete() override;
};

class employee_query : public task {
    std::shared_ptr<employee> employee_;
public:
    explicit employee_query(std::shared_ptr<employee> employee);
    void complete() override;
};

class computer_query : public task {
    std::shared_ptr<computer> computer_;
public:
    explicit computer_query(std::shared_ptr<computer> computer);
    void complete() override;
};

class stock_query : public task {
public:
    void complete() override;
};

class AlreadySold : public std::exception {
    std::string message_;
public:
    explicit AlreadySold(std::string emp_name, unsigned computer_serial);
    const char * what();
};

class ManagerMissing : public std::exception {
    std::string message_;
public:
    explicit ManagerMissing(std::string emp_name);
    const char * what();
};

class TypeMismatch : public std::exception {
    std::string message_;
public:
    explicit TypeMismatch(std::string emp_name);
    const char * what();

};

#endif //CSMS_TASK_H
