#ifndef SERIALCOM_IO_H
#define SERIALCOM_IO_H

#include "serialcom_base.h"
#include <map>
#include <utility>
#include <iostream>
#include <chrono>
#include <thread>
#include <regex>
#include <iterator>

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#define QUEUE_CAPACITY 1024
#define BUFF_SIZE 64

template <typename T>
class Serialcom_io : virtual public Serialcom_base<T>
{
    using commands_map = std::map<const std::string, const unsigned char>;
    using command_type = std::pair<const std::string, const unsigned char>;
    using spsc_queue = boost::lockfree::spsc_queue<T, boost::lockfree::capacity<QUEUE_CAPACITY> >;

    using spsc_size_type = typename spsc_queue::size_type;

    using Serialcom_base<T>::close;
    using Serialcom_base<T>::open;
    using Serialcom_base<T>::is_open;
    using Serialcom_base<T>::port_;
public:
    void add_to_commands(command_type &command)
    {
        commands_.insert(command);
    }
    void add_to_commands(std::initializer_list<command_type> il)
    {
        commands_.insert(il.begin(), il.end());
    }
protected:
    Serialcom_io() = default;
    Serialcom_io(std::initializer_list<command_type> il) : commands_(il) { }

    void negate_read_flag() { read_flag = !read_flag; }
    bool write_command(const std::string, std::size_t sleep_ms = 100);
    bool write_command(const std::initializer_list<const std::string>, std::size_t sleep_ms = 500);

    void get_readings(const std::string start_command, const std::string stop_command, const std::string regex_pattern);

    spsc_size_type num_available_reads() { return readings_.read_available(); }
private:
    commands_map commands_;
    spsc_queue readings_;
    bool read_flag = false;
};

template <typename T>
bool Serialcom_io<T>::write_command(const std::string command, std::size_t sleep_ms)
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
bool Serialcom_io<T>::write_command(const std::initializer_list<const std::string> commands, std::size_t sleep_ms)
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

template <typename T>
void Serialcom_io<T>::get_readings(const std::string start_command, const std::string stop_command, const std::string regex_pattern)
{
    //TODO: fixa sa att om den når maxkapaciteten att den på något sätt signalerar och säger att den är färdig. annars kommer start-knappen vara låst för alltid.
    if (is_open()) {
        close();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        open();
    }
    else {
        open();
    }
    std::cerr << regex_pattern << std::endl;
    auto c = commands_.at(start_command);
    boost::asio::write( port_, boost::asio::buffer(&c, 1) );
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::regex r(regex_pattern);
    while ( read_flag && is_open() && readings_.write_available()) {
        unsigned char read_buff[BUFF_SIZE];

       // while (test != '\n') { boost::asio::read(port_, boost::asio::buffer(&test, 1)); }

        auto bytes_read = boost::asio::read(port_, boost::asio::buffer(&read_buff, BUFF_SIZE));

        std::string buff_str(read_buff, read_buff + bytes_read);

       // std::cerr << buff_str << std::endl;

        for ( std::sregex_iterator beg_it(buff_str.begin(), buff_str.end(), r), end_it;
              beg_it != end_it; ++beg_it)
        {
           // std::cerr << beg_it->str() << std::endl;
         //   T new_item(beg_it->str());
          //  std::cerr << "{" << beg_it->str(1) << ", " << beg_it->str(2) << ", " << beg_it->str(3) << ", " << beg_it->str(4) << "}" << std::endl;
           // readings_.push(new_item);
            readings_.push(T(beg_it->str()));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    c = commands_.at(stop_command);
    boost::asio::write( port_, boost::asio::buffer(&c, 1) );
    if (is_open()) close();
}
#endif // SERIALCOM_IO_H
