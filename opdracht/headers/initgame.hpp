#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
//#include <string>

#include "send_classes.hpp"
#include "displaycontroller.hpp"

class Initgame : public rtos::task<> {
   private:
    rtos::channel<char, 16> keypadchannel;
    send_controller &send_channel;
    DisplayController &display;

    void main();

   public:
    Initgame(send_controller &send_channel, DisplayController &display):
        task(6, "Initgame Task"),
        keypadchannel(this, "Initgame keypad channel"),
        send_channel( send_channel ),
        display( display )
    {}

    void write(const char k) { keypadchannel.write(k); }
    uint16_t encodeMsg( uint8_t data );
    char* appendCharToCharArray(char* array, char a);


};

#endif  // INITGAME_HPP