/**
 * @file keypadclass.hpp
 * @brief This file contains the keypad class 
 */
#ifndef KEYPADCLASS_HPP
#define KEYPADCLASS_HPP

#include "hwlib.hpp"
#include "reg_game.hpp"
#include "rtos.hpp"

#include "keypadlistener.hpp"
/**
 * @brief This class  is used to receive all keypad presses
 * 
 */
class Keypadclass: public rtos::task<>{
public:
    rtos::clock period_clock;

    KeypadListener* listeners[2];
    int n_listeners = 0;

    hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
    hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
    hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
    hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

    hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
    hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
    hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
    hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );

    hwlib::port_oc_from_pins_t out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    hwlib::port_in_from_pins_t in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    hwlib::matrix_of_switches matrix = hwlib::matrix_of_switches( out_port, in_port );

    const char* message = "123A456B789C*0#D";

    hwlib::keypad<16> keypadmatrix = hwlib::keypad<16>(matrix, message);


    void main(){
        for(;;){
            wait(period_clock);                         // wait for period to check for characters
            if(keypadmatrix.char_available()){          // when there is a character add it to all listeners channels
                auto keypadinput = keypadmatrix.getc();

                for(int i = 0; i < n_listeners; i++) {
                    listeners[i]->write(keypadinput);
                }
            }
        }
    }
/**
 * @brief Construct a new Keypadclass object
 * 
 */
    Keypadclass():
        task(4, "keypad"),
        period_clock(this, 100 * rtos::ms, "Keypadclass periodieke klok")
    {}
    /**
     * @brief Adds a listener to the list of listeners
     * 
     * @param k Keypadlistener to add to the list of listeners
     */
    void addListener(KeypadListener *k) {
        listeners[n_listeners] = k;
        n_listeners++;
    }
};

#endif //KEYPAD_HPP