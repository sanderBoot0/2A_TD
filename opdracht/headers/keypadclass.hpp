#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "reg_game.hpp"
#include "rtos.hpp"

class Keypadclass: public rtos::task<>{
public:
    rtos::clock period_clock;
    hwlib::istream &keypadmatrix;
    RegGame &gamePar;

    void main(){
        for(;;){
            wait(period_clock);
            if(keypadmatrix.char_available()){
                auto keypadinput = keypadmatrix.getc();
                gamePar.write(keypadinput);
            }
        }
    }

    Keypadclass(hwlib::istream &keypadconstructor, RegGame &gamePar):
        task(4, "keypad"),
        period_clock(this, 100 * rtos::ms, "Keypadclass periodieke klok"),
        keypadmatrix(keypadconstructor),
        gamePar( gamePar )
    {};

};

#endif //KEYPAD_HPP