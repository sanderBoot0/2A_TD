#ifndef DISPLAY_CONTROLLER_HPP
#define DISPLAY_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "time_entity.hpp"

class DisplayController{// : public rtos::task<>{
   private:
    
    // rtos::pool<char*> commandpool;
    // rtos::flag commandflag;

    // rtos::pool<> gameinfopool;
    // rtos::flag gameinfoflag;

    hwlib::terminal_from display;


    // void main(){
        

    // }
    
   public:
    
    DisplayController(hwlib::glcd_oled &oled, hwlib::font_default_16x16 &font):
        // task(7,"DisplayController"),
        // flag(this,"commandflag"),
        // commandpool("commandpool"),
        display( oled, font ) 
    {
        display << '\f' << hwlib::flush;
    }

    void showTime(time &t);

    void showCommand(const char *p);

    void addChar(const char);

    void flushScreen();
    
    void clearScreen();

//    void writePool();

};


#endif