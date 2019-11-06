/**
 * @file reg_game.hpp
 * @brief This file contains the declaration of the RegGame class and its functions, see the cpp file for the definiton of the functions
 * 
 */
#ifndef REGGAME_HPP
#define REGGAME_HPP

#include "gamerules.hpp"
#include "msglistener.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"


#include "displaycontroller.hpp"
#include "keypadlistener.hpp"

/**
 * @brief This class registers the game_paramereters trough the keyboard input so that the RunGame class 
 * has the neccesary data to start the game
 * 
 */
class RegGame : public rtos::task<>, public MsgListener, public KeypadListener {
   private:
   
    rtos::channel<uint16_t, 10> messages;
    rtos::channel<char, 16> keypadchannel;
    DisplayController &display;

    GameRules &g;

    /**
     * @brief Checks is given char is between 0 and 9
     * 
     * @param c  the char you want to check 
     * @return bool 
     */
    bool isNumber(char c) { return bool((c >= '0') && (c <= '9')); }

    void main();

   public:
   /**
    * @brief Constructor which initialises the objects and sets the taskpriority to 9
    * 
    * @param g Gamerules class you want to set the values 
    * @param display The display  
    */
    RegGame(GameRules &g,  DisplayController &display): 
        task(9, "RegGame"),
        messages(this, "Reg game messages channel"),
        keypadchannel(this, "keypadchannel"),
        display( display ),
        g(g)
    {}
    /**
     * @brief writes a char value to the keypadchannel
     * 
     * @param k given char 
     */
    void write(const char k) override { 
        keypadchannel.write(k); 
    }
    
    /**
     * @brief Writes a 16 bit value to the messagechannel
     * 
     * @param msg 16 bit message you want to send 
     */
    void write(uint16_t msg) override {
        messages.write(msg);
    }
};

#endif
