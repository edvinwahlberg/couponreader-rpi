#ifndef SERIALCOM_HANDLER_H
#define SERIALCOM_HANDLER_H

#include "serialcom_input.h"
#include "serialcom_output.h"
#include "serialcom_base.h"

#include <functional>
#include <utility>
#include <thread>

template <typename T>
class Serialcom_handler : public Serialcom_input<T>, public Serialcom_output<T>
{
    using Serialcom_input<T>::write_command;
public:
    static Serialcom_handler<T>& instance() { static Serialcom_handler<T> singleton; return singleton; }
    void write (const std::string command, const std::size_t sleep_ms = 100) { write_command(command, sleep_ms); }
    void write (std::initializer_list<const std::string> commands, const std::size_t sleep_ms = 100) { write_command(commands, sleep_ms); }
protected:
    Serialcom_handler() :
        Serialcom_base<T>::Serialcom_base("/dev/ttyUSB0")
    { }
    ~Serialcom_handler() = default;
    Serialcom_handler(const Serialcom_handler<T>&) = delete;
    Serialcom_handler<T>& operator=(const Serialcom_handler<T>&) = delete;
private:
    std::thread write_thread; // TODO: implement
    std::thread read_thread; // TODO: implement
};

#endif // SERIALCOM_HANDLER_H
