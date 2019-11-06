/**
 * @file msglistener.hpp
 * @brief This file contains the MsgListener class

 */
#ifndef MSGLISTENER_HPP
#define MSGLISTENER_HPP

#include "rtos.hpp"
/**
 * @brief This class is used to write all incomming messages to all listeners
 * 
 */
class MsgListener {
public:    
/**
 * @brief Virtual write function to write to all the listener subclasses
0 * 
 * @param msg message to write to the listener subclasses 
 */
    virtual void write(uint16_t msg) = 0;
};

#endif // MSGLISTENER_HPP