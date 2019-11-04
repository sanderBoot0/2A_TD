#include "../headers/displaycontroller.hpp"

void DisplayController::showTime(time &t) {
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

void DisplayController::showCommand(const char *p) {
    display << '\f' ;

    do{
        display << *p++;

    }while(*p != '\0');

    flushScreen();
}

void DisplayController::addChar(const char c){
    display << c;
}

void DisplayController::flushScreen(){
    display << hwlib::flush;
}

void DisplayController::clearScreen(){
    display << '\f';
    flushScreen();
}
