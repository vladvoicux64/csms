//
// Created by Voicu Ioan Vladut on 05.05.2024.
//

#include "handler.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

std::unordered_map<std::string, command_type> handler::command_map = {{"new", NEW},
                                                                    {"remove", REMOVE},
                                                                    {"skip", SKIP},
                                                                    {"exit", EXIT},
                                                                    {"run", RUN}
};
std::unordered_map<std::string, entity_type> handler::entity_map = {{"employee", EMPLOYEE},
                                                                   {"computer", COMPUTER},
                                                                   {"task", TASK},
};
std::unordered_map<std::string, employee_type> handler::employee_map = {{"regular", REGULAR},
                                                                       {"manager", MANAGER},
};
std::unordered_map<std::string, computer_type> handler::computer_map = {{"workstation", WORKSTATION},
                                                                       {"server", SERVER},
};
std::unordered_map<std::string, task_type> handler::task_map = {{"employee", EMPLOYEE_TASK},
                                                               {"managerial", MANAGERIAL_TASK},
                                                               {"computer_query", COMP_QUERY_TASK},
                                                               {"employee_query", EMPLOYEE_QUERY_TASK},
                                                               {"stock_query", STOCK_QUERY_TASK},
};

//In urmatoarele functii, fiecare apel al metodei .emplace() este un caz de upcasting.
void handler::create_employee(employee_type type)
{
    std::string name;
    std::cout << "Enter name and press Enter:\n";
    std::cin >> name;
    switch (type) {
        case REGULAR:
        {
            float commission = 0;
            while (commission > 1 || commission < 0.1) {
                std::cout << "Enter commission (float value between 0.1 and 1) and press Enter:\n";
                std::cin >> commission;
            }
            //UPCASTING
            this->employees_.emplace(name, std::make_unique<employee>(name, commission));
        }
        break; case MANAGER:
        {
            //UPCASTING
            this->employees_.emplace(name, std::make_unique<manager>(name));
        }
    }
    std::cout << "\n";
}

void handler::create_computer(computer_type type)
{
    unsigned price;
    std::cout << "Enter price (natural number) and press Enter:\n";
    std::cin >> price;
    switch (type) {
        case WORKSTATION:
        {
            float freq = 0;
            unsigned core_count = 0;
            while (core_count > 128 || core_count < 4) {
                std::cout << "Enter CPU core count (natural number between 4 and 128) and press Enter:\n";
                std::cin >> core_count;
            }
            while (freq > 6.5 || freq < 1) {
                std::cout << "Enter CPU frequency (float value between 1 and 6.5) and press Enter:\n";
                std::cin >> freq;
            }
            this->computers_.emplace(computer::get_next_serial(), std::make_unique<workstation>(price, freq, core_count));
        }
        break; case SERVER:
        {
            unsigned tflops = 0;
            unsigned ram_cap = 0;
            unsigned storage_cap = 0;
            while (tflops > 1350 || tflops < 10) {
                std::cout << "Enter TFLOPs (natural number between 10 and 1350) and press Enter:\n";
                std::cin >> tflops;
            }
            while (ram_cap > 4096 || ram_cap < 32) {
                std::cout << "Enter RAM capacity in GBs (natural number between 32 and 4096) and press Enter:\n";
                std::cin >> ram_cap;
            }
            while (storage_cap > 32768 || storage_cap < 1024) {
                std::cout << "Enter storage capacity in GBs (natural number between 1024 and 32768) and press Enter:\n";
                std::cin >> storage_cap;
            }
            this->computers_.emplace(computer::get_next_serial(), std::make_unique<server>(price, storage_cap, ram_cap, tflops));
        }
    }
    std::cout << "\n";
}

void handler::create_task(task_type type)
{
    try {
        switch (type) {
            case EMPLOYEE_TASK:
            {
                if (this->employees_.empty() && this->computers_.empty()) throw InsufficientData(1, 1, 0, 0);
                else
                {
                    std::string name;
                    unsigned serial = 0;
                    while(this->employees_.find(name) == this->employees_.end())
                    {
                        std::cout << "Enter an existing employee name and press Enter:\n";
                        std::cin >> name;
                    }
                    while(this->computers_.find(serial) == this->computers_.end())
                    {
                        std::cout << "Enter an existing serial for a computer and press Enter:\n";
                        std::cin >> serial;
                    }
                    this->tasks_.emplace(std::make_unique<employee_task>(this->computers_.at(serial).get(), this->employees_.at(name).get()));
                }
            }
            break; case MANAGERIAL_TASK:
            {
                if (this->employees_.size() < 2) throw InsufficientData(2, 0, this->employees_.size(), this->computers_.size());
                else
                {
                    std::string emp_name, man_name;
                    while(this->employees_.find(emp_name) == this->employees_.end())
                    {
                        std::cout << "Enter an existing employee name and press Enter:\n";
                        std::cin >> emp_name;
                    }
                    while(this->employees_.find(man_name) == this->employees_.end())
                    {
                        std::cout << "Enter an existing manager name and press Enter:\n";
                        std::cin >> man_name;
                    }
                    this->tasks_.emplace(std::make_unique<managerial_task>(this->employees_.at(man_name).get(), this->employees_.at(emp_name).get()));
                }
            }
            break; case EMPLOYEE_QUERY_TASK:
            {
                if (this->employees_.empty()) throw InsufficientData(1, 0, 0, this->computers_.size());
                else
                {
                    std::string name;
                    while(this->employees_.find(name) == this->employees_.end())
                    {
                        std::cout << "Enter an existing employee name and press Enter:\n";
                        std::cin >> name;
                    }
                    this->tasks_.emplace(std::make_unique<employee_query>(this->employees_.at(name).get()));
                }
            }
            break; case COMP_QUERY_TASK:
            {
                if (this->computers_.empty()) throw InsufficientData(0, 1, this->employees_.size(), 0);
                else
                {
                    unsigned serial;
                    while(this->computers_.find(serial) == this->computers_.end())
                    {
                        std::cout << "Enter an existing serial for a computer and press Enter:\n";
                        std::cin >> serial;
                    }
                    this->tasks_.emplace(std::make_unique<computer_query>(this->computers_.at(serial).get()));
                }
            }
            break; case STOCK_QUERY_TASK:
            {
                this->tasks_.emplace(std::make_unique<stock_query>());
            }
        }
    }
    catch (InsufficientData &excp)
    {
        std::cerr << excp.what();
    }
    catch (AlreadySold &excp)
    {
        std::cerr << excp.what();
    }
    catch (TypeMismatch &excp)
    {
        std::cerr << excp.what();
    }
    catch (ManagerMissing &excp)
    {
        std::cerr << excp.what();
    }
    std::cout << "\n";
}

void handler::remove_employee(const std::string& name)
{
    try {
        if (this->employees_.find(name) == this->employees_.end()) throw InexistingEmployee(name);
        else this->employees_.erase(name);
    }
    catch (InexistingEmployee &excp) {
        std::cerr << excp.what();
    }
}

void handler::remove_computer(unsigned int serial)
{
    try {
        if (this->computers_.find(serial) == this->computers_.end()) throw InexistingComputer(serial);
        else this->computers_.erase(serial);
    }
    catch (InexistingComputer &excp) {
        std::cerr << excp.what();
    }
}

void handler::skip_task()
{
    try {
        if(!this->tasks_.empty()) this->tasks_.pop();
        else throw NoTasks();
    }
    catch (NoTasks &excp) {
        std::cerr << excp.what();
    }
}

std::vector<std::string> split_by_whitespace(std::string s){
    std::vector<std::string> ans;
    size_t pos = 0;
    while(pos < s.size()){
        pos = s.find("%20");
        ans.push_back(s.substr(0,pos));
        s.erase(0,pos+3); // 3 is the length of the delimiter, "%20"
    }
    return ans;
}

void handler::event_loop()
{
    while(true) {
        std::string command;
        std::cin >> command;
        auto cargs = split_by_whitespace(command);
        try{
            if (handler::command_map.find(cargs[0]) == handler::command_map.end()) throw BadCommand(cargs[0]);
            switch (handler::command_map.at(cargs[0])) {
                case NEW: {
                    if (handler::entity_map.find(cargs[1]) == entity_map.end()) throw BadCommand(cargs[1]);
                    create_entity(handler::entity_map.at(cargs[1]), cargs[2]);
                }
                break; case REMOVE:
                {
                    if (handler::entity_map.find(cargs[1]) == entity_map.end() || cargs[1] == "task") throw BadCommand(cargs[1]);
                    remove_entity(handler::entity_map.at(cargs[1]));
                }
                break; case EXIT:
                {
                    std::cout << "Goodbye!\n\n";
                    return;
                }
                case RUN:
                {
                    while (!this->tasks_.empty()){
                        //POLIMORFISM
                        this->tasks_.front()->complete();
                        this->tasks_.pop();
                    }
                }
                break; case SKIP:
                {
                    this->skip_task();
                }
            }
        }
        catch (BadCommand &excp)
        {
            std::cerr << excp.what();
        }
    }
}

void handler::create_entity(entity_type type, const std::string& type_to_forward)
{
    switch (type) {
        case EMPLOYEE:
        {
            if (handler::employee_map.find(type_to_forward) == handler::employee_map.end()) throw BadCommand(type_to_forward);
            create_employee(handler::employee_map.at(type_to_forward));
        }
        break; case COMPUTER:
        {
            if (handler::computer_map.find(type_to_forward) == handler::computer_map.end()) throw BadCommand(type_to_forward);
            create_computer(handler::computer_map.at(type_to_forward));
        }
        break; case TASK:
        {
            if (handler::task_map.find(type_to_forward) == handler::task_map.end()) throw BadCommand(type_to_forward);
            create_task(handler::task_map.at(type_to_forward));
        }
    }
}

void handler::remove_entity(entity_type type)
{
    switch (type) {
        case EMPLOYEE:
        {
            if(!this->employees_.empty()) {
                std::string name;
                std::cout << "Enter an existing employee name and press Enter:\n";
                std::cin >> name;
                remove_employee(name);
            }
            else std::cout << "Nothing to remove!\n\n";
        }
        break; case COMPUTER:
        {
            if(!this->computers_.empty()) {
                unsigned serial;
                std::cout << "Enter an existing serial for a computer and press Enter:\n";
                std::cin >> serial;
                remove_computer(serial);
            }
            else std::cout << "Nothing to remove!\n\n";
        }
        break; case TASK: break;
    }
    std::cout << "\n";
}

const char *InsufficientData::what()
{
    return ("Insufficient data to create the selected type task. Needed " + std::to_string(this->needed_emp_) + " employees and " + std::to_string(this->needed_comp_) + " computers stored, but there are only " +
            std::to_string(this->emp_) + " employees and " + std::to_string(comp_) + " in the data storage. Operation aborted.").c_str();
}

InsufficientData::InsufficientData(unsigned int needed_emp, unsigned int needed_comp, unsigned int emp,
                                   unsigned int comp)  : needed_emp_(needed_emp), needed_comp_(needed_comp), emp_(emp), comp_(comp)
{

}

InexistingEmployee::InexistingEmployee(std::string name) : emp_name_(std::move(name))
{

}

const char *InexistingEmployee::what()
{
    return ("Employee named " + this->emp_name_ + " not found. Operation aborted.").c_str();
}

InexistingComputer::InexistingComputer(unsigned int serial) : serial_(serial)
{

}

const char *InexistingComputer::what()
{
    return ("Computer with serial " + std::to_string(this->serial_) + " not found. Operation aborted.").c_str();
}

const char *NoTasks::what()
{
    return "No tasks to skip. Operation aborted.";
}

const char *BadCommand::what()
{
    return ("Bad command: " + command_ + ". Operation aborted.").c_str();
}

BadCommand::BadCommand(std::string command) : command_(std::move(command))
{

}
