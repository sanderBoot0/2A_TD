#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "RegGame.hpp"

class keypadclass: public rtos::task<>{
public:
    // rtos::channel<char, 16 > keypadchannel;
    hwlib::istream &keypadmatrix;
    regGame &gamePar;

    void main(){
        for(;;){
            if(keypadmatrix.char_available()){
                auto keypadinput = keypadmatrix.getc();
                gamePar.write(keypadinput);
            }
            hwlib::wait_ms(60);
        }
    }

    keypadclass(hwlib::istream &keypadconstructor, regGame &gamePar):
        task(2, "keypad"),
        // keypadchannel(this, "keypadchannel"),
        keypadmatrix(keypadconstructor),
        gamePar( gamePar )
    {};

    // char read(){return keypadchannel.read();};

    // void write(auto value) { keypadchannel.write(value); }

};

#endif //KEYPAD_HPP