#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <regex>
#include <iostream>

struct sensor_reading {
    sensor_reading() : sensor_reading(-1, -1, -1, -1) { }
    sensor_reading(const std::string &s) {
        std::regex r("[\\n]{1}[\\s]*([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]+([\\d]+)[\\s]*[\\r]{1}");
        std::smatch m;
        std::regex_search(s, m, r);
        s1_ = std::stoi(m.str(1));
        s2_ = std::stoi(m.str(2));
        s3_ = std::stoi(m.str(3));
        s4_ = std::stoi(m.str(4));
        std::cout << "sensor_reading{" << s1_ << ", " << s2_ << ", " << s3_ << ", " << s4_ << "}" << std::endl;
    }
    sensor_reading(int s1, int s2, int s3, int s4) : s1_(s1), s2_(s2), s3_(s3), s4_(s4) { }
    sensor_reading(const sensor_reading& orig) : s1_(orig.s1_), s2_(orig.s2_), s3_(orig.s3_), s4_(orig.s4_) { }
    sensor_reading& operator=(const sensor_reading&) = default;
    ~sensor_reading() = default;

    int s1_, s2_, s3_, s4_;
};

#endif // SENSOR_READING_H
