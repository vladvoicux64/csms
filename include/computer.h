//
// Created by Voicu Ioan Vladut on 28.04.2024.
//

#ifndef CSMS_COMPUTER_H
#define CSMS_COMPUTER_H


class computer {
private:
    unsigned price_;
    bool assembled_;
protected:
    unsigned performance_rating_;
    [[nodiscard]] virtual unsigned compute_performance() const = 0;
    explicit computer(unsigned price);
public:
    void assemble();
    virtual ~computer() = default;
    [[nodiscard]] unsigned get_performance_rating() const;
    [[nodiscard]] unsigned get_price() const;
    [[nodiscard]] bool is_assembled() const;
};

class workstation : computer {
    unsigned cpu_freq_;
    unsigned core_count_;
    [[nodiscard]] unsigned compute_performance() const override;
public:
    workstation(unsigned price, unsigned cpu_freq, unsigned core_count);
};

class server : computer {
    unsigned storage_;
    unsigned ram_capacity_;
    unsigned tflops_;
    [[nodiscard]] unsigned compute_performance() const override;
public:
    server(unsigned price, unsigned storage, unsigned ram_capacity, unsigned tflops);
};

// these classes only follow attributes i considered important for the performance rating per each class

#endif //CSMS_COMPUTER_H
