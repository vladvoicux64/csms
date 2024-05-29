#include <computerbox.h>
#include <computer.h>


template<typename T>
computerbox<T>::computerbox(T product) : contents_(product)
{
}

template<typename T>
T computerbox<T>::checkcontents()
{
    return this->contents_;
}

template
class computerbox<workstation>;

template
class computerbox<server>;