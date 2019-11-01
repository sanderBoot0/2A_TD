#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "RegGame.hpp"

class keypadclass: public rtos::task<>{
public:
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
        keypadmatrix(keypadconstructor),
        gamePar( gamePar )
    {};

};

#endif //KEYPAD_HPP