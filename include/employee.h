//
// Created by Voicu Ioan Vladut on 03.05.2024.
//

#ifndef CSMS_EMPLOYEE_H
#define CSMS_EMPLOYEE_H


#include <string>

class employee {
    std::string name_;
private:
    float commission_;
protected:
    float earnings_;
public:
    [[nodiscard]] float get_earnings() const;
    void set_commission_(float commission);
    [[nodiscard]] float get_commission() const;
    [[nodiscard]] const std::string &get_name() const;
    employee(std::string name, float commission);
    virtual void earn(unsigned value);
    virtual ~employee() = default;
};

class manager : public employee {
public:
    void earn(unsigned value) override;
    explicit manager(std::string name);
};


#endif //CSMS_EMPLOYEE_H
