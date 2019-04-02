#ifndef SENSOR_READING_H
#define SENSOR_READING_H

#include <regex>
#include <iostream>

extern const std::string g_PATTERN;
struct sensor_reading {
    friend std::ostream& operator<<(std::ostream& out, const sensor_reading& printer);
    sensor_reading() : sensor_reading(-1, -1, -1, -1) { }
    sensor_reading(const std::string &s) {
        std::regex r(g_PATTERN);
        std::smatch m;
        if (std::regex_search(s, m, r)) {
            s1_ = std::stoi(std::regex_replace(m.str(1), std::regex("([\\D])"), ""));
            s2_ = std::stoi(std::regex_replace(m.str(2), std::regex("([\\D])"), ""));
            s3_ = std::stoi(std::regex_replace(m.str(3), std::regex("([\\D])"), ""));
            s4_ = std::stoi(std::regex_replace(m.str(4), std::regex("([\\D])"), ""));
        } else {
            s1_ = -1;
            s2_ = -1;
            s3_ = -1;
            s4_ = -1;
        }
    }
    sensor_reading(int s1, int s2, int s3, int s4) : s1_(s1), s2_(s2), s3_(s3), s4_(s4) { }
    sensor_reading(const sensor_reading& orig) : s1_(orig.s1_), s2_(orig.s2_), s3_(orig.s3_), s4_(orig.s4_) { }
    sensor_reading& operator=(const sensor_reading&) = default;
    sensor_reading(sensor_reading&& orig) noexcept :
        s1_(std::move(orig.s1_)), s2_(std::move(orig.s2_)), s3_(std::move(orig.s3_)), s4_(std::move(orig.s4_))
    { }
    sensor_reading& operator=(sensor_reading&& rhs)
    {
        s1_ = rhs.s1_;
        s2_ = rhs.s2_;
        s3_ = rhs.s3_;
        s4_ = rhs.s4_;
        return *this;
    }
    ~sensor_reading() = default;

    int s1_, s2_, s3_, s4_;
};

std::ostream& operator<<(std::ostream& out, const sensor_reading& printer);

#endif // SENSOR_READING_H
