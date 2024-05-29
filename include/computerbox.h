#ifndef CSMS_COMPUTERBOX_H
#define CSMS_COMPUTERBOX_H


template<typename T>
class computerbox
{
    T contents_;
public:
    explicit computerbox(T product);

    template<typename L>
    L set_shipping_label(L label);

    T checkcontents();
};

template<typename T>
template<typename L>
L computerbox<T>::set_shipping_label(L label)
{
    return label;
}

#endif //CSMS_COMPUTERBOX_H
