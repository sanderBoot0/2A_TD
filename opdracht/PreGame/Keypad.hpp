#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"

class keypad: public rtos::task<>{
public:
    rtos::pool<char> keypadpool;
    rtos::flag keypadflag;
    hwlib::istream &keyinput;
    void test(){
        if(keyinput.char_available()){
            hwlib::cout << keyinput.getc();
            // keypadpool.write(key.getc());
            // keypadflag.set();
        }
    }

    keypad(hwlib::istream &keyinput):
        task("keypad"),
        keypadpool("keypadpool"),
        keypadflag(this, "keypadflag" ),
        keyinput(keyinput)
        {};

};

#endif //KEYPAD_HPP