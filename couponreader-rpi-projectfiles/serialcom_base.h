#ifndef SERIALCOM_BASE_H
#define SERIALCOM_BASE_H

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <mutex>

template <typename T>
class Serialcom_base
{
    using serial_port = boost::asio::serial_port;
    using io_service = boost::asio::io_service;
protected:
    Serialcom_base() :
        io_(), port_(io_), port_name_("/dev/ttyUSB0"){ }

    Serialcom_base(const std::string &port_name) :
        io_(), port_(io_), port_name_(port_name){ }
    ~Serialcom_base() { if (is_open()) close();}
    bool open() {
        port_.open(port_name_);
        return port_.is_open();
    }
    bool close() {
        port_.close();
        return !port_.is_open();
    }
    bool is_open() const
    {
        return port_.is_open();
    }
    io_service io_;
    serial_port port_;
    std::string port_name_;
};

#endif // SERIALCOM_BASE_H
