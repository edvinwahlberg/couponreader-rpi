#ifndef SERIALDAO_H
#define SERIALDAO_H

#include <deque>
#include <tuple>
#include <memory>
class SerialHandler;

class SerialDao
{
public:
    SerialDao() :
     readings(){ }
private:
    std::deque<std::tuple<int,int,int,int>> readings;
};

#endif // SERIALDAO_H
