#include "sensor_reading.h"
std::ostream& operator<<(std::ostream& out, const sensor_reading& printer)
{
    out << "{" << printer.s1_ << ", " << printer.s2_ << ", "
        << printer.s3_ << ", " << printer.s4_ << "}";
    return out;
}
