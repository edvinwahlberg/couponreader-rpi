#ifndef SERIALCOM_INPUT_H
#define SERIALCOM_INPUT_H

#include "serialcom_base.h"
#include <map>
#include <utility>
#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>

template <typename T>
class Serialcom_input : virtual public Serialcom_base<T>
{
    using commands_map = std::map<const std::string, const unsigned char>;
    using command_type = std::pair<const std::string, const unsigned char>;
    using Serialcom_base<T>::close;
    using Serialcom_base<T>::open;
    using Serialcom_base<T>::is_open;
    using Serialcom_base<T>::port_;
public:
    Serialcom_input() = default;
    Serialcom_input(std::initializer_list<command_type> il) : commands_(il) { }
    bool write_command(const std::string&, std::size_t);
    bool write_command(const std::initializer_list<const std::string>, std::size_t);
    void add_to_commands(command_type &command)
    {
        commands_.insert(command);
    }
    void add_to_commands(std::initializer_list<command_type> il)
    {
        commands_.insert(il.begin(), il.end());
    }
private:
    commands_map commands_;
};

template <typename T>
bool Serialcom_input<T>::write_command(const std::string & command, std::size_t sleep_ms)
{
    if (!is_open())
        open();
    try {
        auto result = commands_.at(command);
        std::cerr << "command: " << command << ", result: " << result << std::endl;
        if (is_open()) {
            boost::asio::write( port_, boost::asio::buffer(&result, 1) );
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
        }
        return close();
    } catch (std::out_of_range e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        throw;
    }
    return false;
}

template <typename T>
bool Serialcom_input<T>::write_command(const std::initializer_list<const std::string> commands, std::size_t sleep_ms)
{
    if (!is_open())
        open();
    try {
        for (auto &command : commands){
            auto result = commands_.at(command);
            std::cerr << "command: " << command << ", result: " << result << std::endl;
            if (is_open()) {
                boost::asio::write( port_, boost::asio::buffer(&result, 1) );
                std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
            }
            else {
                return false;
            }
        }
        return true;
    } catch (std::out_of_range e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        throw;
    }
    return false;
}
#endif // SERIALCOM_INPUT_H
