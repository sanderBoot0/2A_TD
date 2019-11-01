#ifndef DISPLAY_CONTROLLER_HPP
#define DISPLAY_CONTROLLER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "time_entity.hpp"

class displayController: public rtos::task<>
{
   private:
    
    hwlib::terminal_from display;
    
   public:
    
    displayController(hwlib::glcd_oled &oled, hwlib::font_default_16x16 &font):
        task(4, "Display Control Taak"),
        display( oled, font ) 
    {}

    void showTime(time &t);
    
};


#endif