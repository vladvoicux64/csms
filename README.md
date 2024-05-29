# Description
This is a mock project for my object-oriented programming class. The aim is to provide a 
management solution for a computer store.

# Structure
At the heart of the project is an event loop responsible for fulfilling the user's requests
to the system. At the backend, there are multiple classes that represent different entities,
computers, employees and tasks that also split in multiple subclasses. In the following section
I'll focus on explaining the task hierarchy, as it interacts with all the components.

# Tasks
Tasks are at the backbone of the system. There are 5 types of tasks:

- sales tasks: represented in the system as "employee" type tasks, these represent a computer sale done by an employee,
who will earn part of the sale's value in commission;
- managerial tasks: these tasks represent the provision of a premium in value of 10% to the commission earned by an employee
while also paying the manager a 500 monetary units reward for accomplishing the task (boss makes a dollar I make a dime);
- queries (computer, employee and stock): these return information about the selected entity or the stock of computers that
the store holds;

# Usage
The interface provided is a custom command interpreter:

- there is the `new <enitity> <type>` command, where entities are `computer`, `employee`, `task`;
    - the types for computers are `server` and `workstation`;
    - the types for employee are `regular` and `manager`;
    - the types for tasks are `employee`, `managerial`, `employee_query`, `computer_query`, `stock_query`;
- the `remove <entity>` command, which can remove a computer (`computer`) or employee (`employee`) from the system;
- the `skip` command skips the first command in the queue of commands;
- the `run` command, executes all tasks in the queue in order;
- `exit`: exits the program;



