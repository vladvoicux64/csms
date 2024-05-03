//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#ifndef CSMS_EMPLOYEE_H
#define CSMS_EMPLOYEE_H


#include <string>

class employee {
    std::string name_;
    float commission_;
    void set_commission_(float commission);
protected:
    float earnings_;
    virtual void earn(unsigned value);
public:
    [[nodiscard]] float get_earnings() const;
    [[nodiscard]] float get_commission() const;
    employee(std::string name, float commission);
    virtual ~employee() = default;
};

class manager : employee {
    void earn(unsigned value) override;
public:
    explicit manager(std::string name);
};


#endif //CSMS_EMPLOYEE_H
