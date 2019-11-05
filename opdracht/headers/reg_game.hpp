#ifndef REGGAME_HPP
#define REGGAME_HPP

#include "gamerules.hpp"
#include "msglistener.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"


#include "displaycontroller.hpp"
#include "keypadlistener.hpp"

class RegGame : public rtos::task<>, public MsgListener, public KeypadListener {
   private:
    rtos::channel<uint16_t, 10> messages;
    rtos::channel<char, 16> keypadchannel;
    DisplayController &display;

    GameRules &g;

    bool isNumber(char c) { return bool((c >= '0') && (c <= '9')); }

    void main();

   public:
    RegGame(GameRules &g,  DisplayController &display): 
        task(9, "RegGame"),
        messages(this, "Reg game messages channel"),
        keypadchannel(this, "keypadchannel"),
        display( display ),
        g(g)
    {}



   
/*
overrided function for channels


*/

    void write(const char k) override { 
        keypadchannel.write(k); 
    }
    
    void write(uint16_t msg) override {
        messages.write(msg);
    }
};

#endif
