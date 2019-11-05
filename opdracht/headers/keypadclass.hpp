#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "reg_game.hpp"
#include "rtos.hpp"

#include "keypadlistener.hpp"

class Keypadclass: public rtos::task<>{
public:
    rtos::clock period_clock;
    hwlib::istream &keypadmatrix;

    KeypadListener* listeners[2];
    int n_listeners = 0;

    void main(){
        for(;;){
            wait(period_clock);
            if(keypadmatrix.char_available()){
                auto keypadinput = keypadmatrix.getc();

                for(int i = 0; i < n_listeners; i++) {
                    listeners[i]->write(keypadinput);
                }
            }
        }
    }

    Keypadclass(hwlib::istream &keypadconstructor):
        task(4, "keypad"),
        period_clock(this, 100 * rtos::ms, "Keypadclass periodieke klok"),
        keypadmatrix(keypadconstructor)
    {}

    void addListener(KeypadListener *k) {
        listeners[n_listeners] = k;
        n_listeners++;
    }

};

#endif //KEYPAD_HPP