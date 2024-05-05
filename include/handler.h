//
// Created by Voicu Ioan Vladut on 05.05.2024.
//

#ifndef CSMS_HANDLER_H
#define CSMS_HANDLER_H


#include <unordered_map>
#include <utility>
#include <queue>
#include <string>
#include "task.h"
#include "computer.h"
#include "employee.h"

typedef enum commands {
    NEW,
    REMOVE,
    SKIP,
    EXIT,
    RUN
} command_type;

typedef enum entities {
    EMPLOYEE,
    COMPUTER,
    TASK
} entity_type;

typedef enum computers {
    WORKSTATION,
    SERVER
} computer_type;

typedef enum employees {
    REGULAR,
    MANAGER
} employee_type;

typedef enum tasks {
    EMPLOYEE_TASK,
    MANAGERIAL_TASK,
    EMPLOYEE_QUERY_TASK,
    COMP_QUERY_TASK,
    STOCK_QUERY_TASK
} task_type;

class handler {
    static std::unordered_map<std::string, command_type> command_map;
    static std::unordered_map<std::string, entity_type> entity_map;
    static std::unordered_map<std::string, employee_type> employee_map;
    static std::unordered_map<std::string, computer_type> computer_map;
    static std::unordered_map<std::string, task_type> task_map;
    std::unordered_map<std::string, std::unique_ptr<employee>> employees_;
    std::unordered_map<unsigned, std::unique_ptr<computer>> computers_;
    std::queue<std::unique_ptr<task>> tasks_;
    void create_employee(employee_type type);
    void create_computer(computer_type type);
    void create_task(task_type type);
    void create_entity(entity_type type, const std::string& type_to_forward);
    void remove_entity(entity_type type);
    void remove_employee(const std::string& name);
    void remove_computer(unsigned serial);
    void skip_task();
public:
    handler() = default;
    void event_loop();
};

class InsufficientData : public std::exception {
    unsigned needed_emp_;
    unsigned needed_comp_;
    unsigned emp_;
    unsigned comp_;
public:
    InsufficientData(unsigned needed_emp, unsigned needed_comp, unsigned emp, unsigned comp);
    const char * what();
};

class InexistingEmployee : public std::exception {
    std::string emp_name_;
public:
    explicit InexistingEmployee(std::string name);
    const char * what();
};

class InexistingComputer : public std::exception {
    unsigned serial_;
public:
    explicit InexistingComputer(unsigned serial);
    const char * what();
};

class NoTasks : public std::exception
{
public:
    const char * what();
};

class BadCommand : public std::exception {
    std::string message_;
public:
    explicit BadCommand(std::string command);
    const char * what();
};

#endif //CSMS_HANDLER_H
