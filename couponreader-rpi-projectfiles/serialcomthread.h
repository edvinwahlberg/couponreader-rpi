#ifndef SERIALCOMTHREAD_H
#define SERIALCOMTHREAD_H

#include <thread>
#include <future>
#include <boost/system/error_code.hpp>

class SerialcomThread
{
    using error_code = boost::system::error_code;
public:
    SerialcomThread() = default;
    template <typename Callable, typename... Args>
    explicit SerialcomThread(Callable&& fun, Args&& ... args)
    {
        t_(std::forward<Callable>(fun), std::forward<Args>(args) ...);
    }
    ~SerialcomThread()
    {
        if (joinable())
            join();
    }
    bool joinable() { return t_.joinable(); }
    void join() { t_.join(); }

    std::thread& thread() noexcept { return t_; }
    const std::thread& thread() const noexcept { return t_; }

private:
    std::thread t_;
    std::future<error_code> err_;
    std::future<bool> halt_;
};

#endif // SERIALCOMTHREAD_H
