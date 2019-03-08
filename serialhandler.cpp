#include "serialhandler.h"
#include <iostream>
#include <regex>
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

    port.open(port_name);
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
    currently_reading = true;
    sensor_thread = boost::thread(boost::bind(&SerialHandler::get_readings, this));
   // currently_reading = false;
}

void SerialHandler::stop_readings()
{
    currently_reading = false;
    sensor_thread.join();
    boost::asio::write(port, boost::asio::buffer(STOP_SENSOR_READINGS, 1));
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
    readings.clear();
    while (currently_reading && is_open())
    {
        int c = 0;
        while (c != 13)
            boost::asio::read(port, boost::asio::buffer(&c, 1));
      //  line[49] = '\0';
        unsigned char line[64];
        std::size_t bytes_read = boost::asio::read(port, boost::asio::buffer(line, 64));
        for (std::size_t i = 0; i != 64; ++i) {
            if (static_cast<int>(line[i]) == 10 || static_cast<int>(line[i]) == 13 )
                std::cout << "{" << static_cast<int>(line[i]) << ", " << "\\n} ";
            else
                std::cout << "{" << static_cast<int>(line[i]) << ", " << static_cast<char>(line[i]) << "} ";
        }
        std::cout << std::endl;
        if (bytes_read)
        {
            std::string results(line, line + sizeof(line));
            std::regex r(SENSOR_PATTERN);
            for (std::sregex_iterator it(results.begin(), results.end(), r), end_it;
                 it != end_it; ++it)
            {
                readings.push_back(
                            std::make_tuple(std::stoi(it->str(1)), std::stoi(it->str(2)),
                                            std::stoi(it->str(3)), std::stoi(it->str(4)))
                            );
                auto tup = readings.front();
                readings.pop_front();
                std::cout << "size: " << readings.size() << "\ntup{" << std::get<0>(tup) << ", " << std::get<1>(tup) << ", "
                          << std::get<2>(tup) << ", " << std::get<3>(tup) << "}" << std::endl;
                break;
            }
        }
    }
}
