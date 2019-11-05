#ifndef MSGLISTENER_HPP
#define MSGLISTENER_HPP

#include "rtos.hpp"

class MsgListener {
public:    
    virtual void write(uint16_t msg) = 0;
};

#endif // MSGLISTENER_HPP