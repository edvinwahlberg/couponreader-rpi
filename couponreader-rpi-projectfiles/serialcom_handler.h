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
    using Serialcom_io<T, Container>::write_command;
    using Serialcom_io<T, Container>::negate_read_flag;
    using Serialcom_io<T, Container>::get_readings;
    using Serialcom_io<T, Container>::num_available_reads;
    using Serialcom_io<T, Container>::consumer_read_spsc;
public:
    static Serialcom_handler<T, Container>& instance() { static Serialcom_handler<T, Container> singleton; return singleton; }

    void write (const std::string command, const std::size_t sleep_ms = 100) { write_command(command, sleep_ms); }
    void write (std::initializer_list<const std::string> commands, const std::size_t sleep_ms = 100) { write_command(commands, sleep_ms); }

    //Denna funktion borde också spawna tråden som läser IFRÅN SPSC också.
    void start_readings (const std::string, const std::string, const std::string, Container<T>&);

    //Denna funktion kommer döda båda så borde därför joina båda.
    void stop_readings () { negate_read_flag(); producer_thread.join(); consumer_thread.join(); } // consumer_thread.join(); }

    //Denna behövs inte
    //void start_read_spsc (Container<T>& v) { write_thread = std::thread(&Serialcom_handler<T, Container>::read_all, this, v); }
    //T pop_if_available () { spsc_queue->pop(); }
protected:
    Serialcom_handler() :
        Serialcom_base<T>::Serialcom_base("/dev/ttyUSB0")
    { }
    ~Serialcom_handler() = default;
    Serialcom_handler(const Serialcom_handler<T, Container>&) = delete;
    Serialcom_handler<T, Container>& operator=(const Serialcom_handler<T, Container>&) = delete;
private:
    void start(const std::string& start_command, const std::string& stop_command, const std::string& regex_pattern)
    {  get_readings(start_command, stop_command, regex_pattern); }
    void read_all(Container<T>& v) { consumer_read_spsc(v); }
    std::thread consumer_thread; // TODO: implement
    std::thread producer_thread; // TODO: implement
};

template <typename T, template <typename, typename...> class Container>
void Serialcom_handler<T, Container>::start_readings
(const std::string start_command, const std::string stop_command, const std::string regex_pattern, Container<T> &v)
{
    negate_read_flag();
    producer_thread = std::thread(&Serialcom_handler<T, Container>::start,
                                  this, start_command, stop_command, regex_pattern);
    consumer_thread = std::thread(&Serialcom_handler<T, Container>::read_all,
                                  this, std::ref(v));
}

#endif // SERIALCOM_HANDLER_H
