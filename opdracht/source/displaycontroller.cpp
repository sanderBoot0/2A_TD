#include "../headers/displaydontroller.hpp"

void displayController::showTime(time &t) {
    display << '\f';

    unsigned int minutes = t.getMinutes();
    unsigned int seconds = t.getSeconds();

    if(minutes < 10) 
        display << '0';

    display << minutes << ':';

    if(seconds < 10) 
        display << '0';

    display << seconds << hwlib::flush;

}