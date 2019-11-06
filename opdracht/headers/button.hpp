/**
 * @file button.hpp
 * @brief This file contains the Button class

 * 
 */

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "buttonlistener.hpp"
/**
 * @brief Button class that writes to listners
 * 
 */
class Button : public rtos::task<> {
private:
    rtos::clock period_clock;
    hwlib::pin_in &button;

    Buttonlistener* listeners[2];
    int n_listeners = 0;

    void main() {
        for(;;) {
            wait(period_clock);

            if(!button.read()) {
                for(int i = 0; i < n_listeners; i++) {
                    listeners[i]->buttonPressed();
                }
            }
        }
    }

public:
/**
 * @brief Construct a new Button object
 * 
 * @param button 
 */
    Button(hwlib::pin_in &button):
        task(6, "Button Taak"),
        period_clock(this, 60 * rtos::ms, "Button clock"),
        button(button)
    {}
/**
 * @brief adds a listner to the listner array
 * 
 * @param b 
 */
    void addListener(Buttonlistener *b) {
        listeners[n_listeners] = b;
        n_listeners++;
    }
};

#endif // BUTTON_HPP