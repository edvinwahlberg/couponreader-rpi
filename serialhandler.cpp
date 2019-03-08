#include "serialhandler.h"
#include <iostream>
#include <regex>

const std::string USB_PORT{"/dev/ttyUSB0"};
const char *ACTIVATE = "1";
const char *WAIT_FOR_COUPON = "2";
const char *RUN_MOTOR = "r";
const char *STOP_MOTOR ="s";
const char *SENSOR_READINGS = "c";
const char *STOP_SENSOR_READINGS = "x";

const char *SENSOR_PATTERN = "\\r?[[:space:]]*([[:digit:]]+)[[:space:]]+([[:digit:]]+)[[:space:]]+([[:digit:]]+)[[:space:]]+([[:digit:]]+)\\n";

bool SerialHandler::open_port()
{
    if (port.is_open())
        return true;

    port.open(USB_PORT);
    port.set_option(boost::asio::serial_port_base::baud_rate(9600));

    return port.is_open();
}

bool SerialHandler::close_port()
{
    if (port.is_open())
        port.close();

    return !port.is_open();
}

void SerialHandler::start_readings() {
    open_port();
    port.set_option(boost::asio::serial_port_base::baud_rate(9600));
    currently_reading = true;
    sensor_thread = boost::thread(boost::bind(&SerialHandler::get_readings, this));
}

void SerialHandler::stop_readings()
{
    currently_reading = false;
    sensor_thread.join();
    close_port();
}

SerialHandler& SerialHandler::instance()
{
    static SerialHandler lone_handler;
    return lone_handler;
}

void SerialHandler::get_readings()
{
    boost::asio::write(port, boost::asio::buffer(SENSOR_READINGS, 1));
    readings->clear();
    while (currently_reading && is_open())
    {
        int c = 0;
        while (c != 13)
            boost::asio::read(port, boost::asio::buffer(&c, 1));

        unsigned char line[BUFF_SIZE];
        std::size_t bytes_read = boost::asio::read(port, boost::asio::buffer(line, BUFF_SIZE));

        if (bytes_read)
        {
            std::string results(line, line + bytes_read);
            std::regex r(SENSOR_PATTERN);
            for (std::sregex_iterator it(results.begin(), results.end(), r), end_it;
                 it != end_it; ++it)
            {
                readings->push_back(
                            std::make_tuple(std::stoi(it->str(1)), std::stoi(it->str(2)),
                                            std::stoi(it->str(3)), std::stoi(it->str(4)))
                            );
            }
        }
    }
    if (is_open())
        boost::asio::write(port, boost::asio::buffer(STOP_SENSOR_READINGS, 1));
}
