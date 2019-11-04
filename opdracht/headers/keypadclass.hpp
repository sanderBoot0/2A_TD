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
    Initgame &initGame;

    void main(){
        for(;;){
            wait(period_clock);
            if(keypadmatrix.char_available()){
                auto keypadinput = keypadmatrix.getc();
                gamePar.write(keypadinput);
                initGame.write(keypadinput);

            }
        }
    }

    Keypadclass(hwlib::istream &keypadconstructor, RegGame &gamePar, Initgame &initGame):
        task(3, "keypad"),
        period_clock(this, 100 * rtos::ms, "Keypadclass periodieke klok"),
        keypadmatrix(keypadconstructor),
        gamePar( gamePar ),
        initGame( initGame )
    {};

};

#endif //KEYPAD_HPP