#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <string>
#include <vector>
#include <QDebug>
#include <tuple>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>

extern const std::string USB_PORT;

#define BUFF_SIZE 128

extern const char *ACTIVATE; //1
extern const char *WAIT_FOR_COUPON; //2
extern const char *RUN_MOTOR; //r
extern const char *STOP_MOTOR; //s
extern const char *SENSOR_READINGS; //c
extern const char *STOP_SENSOR_READINGS; //x
extern const char *SENSOR_PATTERN;

class SerialHandler
{
public:
    using readings_deque = std::deque<std::tuple<int,int,int,int>>;
    using readings_item = std::tuple<int, int, int, int>;
    using serial_port = boost::asio::serial_port;
    using io_service = boost::asio::io_service;

    bool open_port();
    bool close_port();
    bool is_open() const { return port.is_open(); }
    void start_readings();
    void stop_readings();
    void wait_for_coupon();
    void start_motor();
    void stop_motor();
    int size() { return readings->size(); }

    std::shared_ptr<readings_deque>readings_ptr() { return readings; }

    static SerialHandler& instance();
    ~SerialHandler() { close_port(); }
protected:
    SerialHandler() :
        io(), port(io),
        readings(std::make_shared<readings_deque>(readings_deque()))
    {
    }
private:
    void get_readings();
    io_service io;
    serial_port port;
    bool currently_reading;
    std::shared_ptr<readings_deque> readings = nullptr;
    boost::thread sensor_thread;
};

#endif // SERIALHANDLER_H
