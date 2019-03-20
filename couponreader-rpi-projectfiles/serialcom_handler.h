#ifndef SERIALCOM_HANDLER_H
#define SERIALCOM_HANDLER_H

#include "serialcom_io.h"
#include "serialcom_base.h"

#include <functional>
#include <utility>
#include <thread>

#include <iostream>
#include "sensor_reading.h"

#include <QVector>


template <typename T, template <typename, typename...> class Container = QVector>
class Serialcom_handler : public Serialcom_io<T>
{
    using Serialcom_io<T>::write_command;
    using Serialcom_io<T>::negate_read_flag;
    using Serialcom_io<T>::get_readings;
    using Serialcom_io<T>::num_available_reads;
public:
    static Serialcom_handler<T, Container>& instance() { static Serialcom_handler<T, Container> singleton; return singleton; }

    void write (const std::string command, const std::size_t sleep_ms = 100) { write_command(command, sleep_ms); }
    void write (std::initializer_list<const std::string> commands, const std::size_t sleep_ms = 100) { write_command(commands, sleep_ms); }

    void start_readings(const std::string start_command, const std::string stop_command, const std::string regex_pattern)
    { negate_read_flag(); read_thread = std::thread(&Serialcom_handler<T, Container>::start, this, start_command, stop_command, regex_pattern); }
    void stop_readings() { negate_read_flag(); read_thread.join(); }
    void read_available(Container<T>&) { std::cerr << num_available_reads(); }
protected:
    Serialcom_handler() :
        Serialcom_base<T>::Serialcom_base("/dev/ttyUSB0")
    { }
    ~Serialcom_handler() = default;
    Serialcom_handler(const Serialcom_handler<T, Container>&) = delete;
    Serialcom_handler<T, Container>& operator=(const Serialcom_handler<T, Container>&) = delete;
private:
    void start(const std::string& start_command, const std::string& stop_command, const std::string& regex_pattern) {  get_readings(start_command, stop_command, regex_pattern); }
    std::thread write_thread; // TODO: implement
    std::thread read_thread; // TODO: implement
};

#endif // SERIALCOM_HANDLER_H
