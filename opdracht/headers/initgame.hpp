/**
 * @file initgame.hpp
 * @brief this file contains the InitGame class and function declaration
 */

#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "send_classes.hpp"
#include "displaycontroller.hpp"
#include "keypadlistener.hpp"

class Initgame : public rtos::task<>, public KeypadListener {
   private:
    rtos::channel<char, 16> keypadchannel;
    send_controller &send_channel;
    DisplayController &display;

    void main();

    /**
     * @brief function to encode data into usable sendable messages
     * 
     * @param data Data you want to get encoded
     * @return uint16_t the part of the message that's done encoding
     */
    uint16_t encodeMsg( uint8_t data );

   public:
    Initgame(send_controller &send_channel, DisplayController &display):
        task(7, "Initgame Task"),
        keypadchannel(this, "Initgame keypad channel"),
        send_channel( send_channel ),
        display( display )
    {}

    /**
     * @brief write function that writes in the keypadchannel. To be used with a listener
     * 
     * @param k Const character you want to write into the keypadchannel
     */
    void write(const char k) override { keypadchannel.write(k); }
};

#endif  // INITGAME_HPP