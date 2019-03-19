#ifndef SERIALCOM_OUTPUT_H
#define SERIALCOM_OUTPUT_H

#include "serialcom_base.h"

template <typename T>
class Serialcom_output : virtual public Serialcom_base<T> {
public:
    Serialcom_output() { }
private:
};

#endif // SERIALCOM_OUTPUT_H
