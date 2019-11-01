#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "send_classes.hpp"
#include "displaycontroller.hpp"

class Initgame : public rtos::task<> {
   private:
    rtos::channel<char, 16> keypadchannel;
    send_controller &send_channel;
    Displaycontroller &display;

    void main();

   public:
    Initgame(send_controller &send_channel, DisplayController &display):
        task(4, "Initgame Task"),
        keypadchannel(this, "Initgame keypad channel"),
        send_channel( send_channel ),
        display( display )
    {}

    void write(const char k) { keypadchannel.write(k); }
};

#endif  // INITGAME_HPP