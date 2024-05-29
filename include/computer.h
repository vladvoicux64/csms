//
// Created by Voicu Ioan Vladut on 28.04.2024.
//

#ifndef CSMS_COMPUTER_H
#define CSMS_COMPUTER_H

#include <computerbox.h>

class computer {
private:
    static unsigned stock_count_;
    unsigned serial_;
    unsigned price_;
    bool assembled_;
    void assemble();

    virtual void packbox() = 0;
protected:
    unsigned performance_rating_;
    virtual void compute_performance() = 0;
    static unsigned generate_new_serial();
    explicit computer(unsigned price);
public:
    static unsigned get_stock_count();
    static unsigned get_next_serial();
    [[nodiscard]] unsigned get_serial() const;
    void prepare_for_sale();
    virtual ~computer() = default;
    [[nodiscard]] unsigned get_performance_rating() const;
    [[nodiscard]] unsigned get_price() const;
    [[nodiscard]] bool is_assembled() const;
};

class workstation : public computer {
    unsigned cpu_freq_;
    unsigned core_count_;
    void compute_performance() override;

    void packbox() override;
public:
    workstation(unsigned price, unsigned cpu_freq, unsigned core_count);
};

class server : public computer {
    unsigned storage_;
    unsigned ram_capacity_;
    unsigned tflops_;

    void packbox() override;
    void compute_performance() override;
public:
    server(unsigned price, unsigned storage, unsigned ram_capacity, unsigned tflops);
};

// these classes only contain attributes i considered important for the performance rating per each class

#endif //CSMS_COMPUTER_H
