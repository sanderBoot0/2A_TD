/**
 * @file run_game.hpp
 * @brief This file contains the declaration of the RunGame class and its functions
 */

#ifndef RUN_GAME_HPP
#define RUN_GAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "gamerules.hpp"

#include "button.hpp"
#include "buttonlistener.hpp"

#include "send_classes.hpp"
#include "msglistener.hpp"

#include "beeperCtrl.hpp"

#include "displaycontroller.hpp"

#include "score.hpp"

#include "transferHits.hpp"
/**
 * @brief This class is used to control the state of the game when running
 * 
 */
class Rungame : public rtos::task<>, public MsgListener, public Buttonlistener {
   private:
    rtos::channel<uint16_t, 10> messages;

    rtos::clock second_clock;
    rtos::timer shoot_timer;
    rtos::timer hit_timer; // Timeout when you get hit
    rtos::flag button_pressed_flag;

    send_controller &sender;

    GameRules &game_par;

    Beeper &beeper;

    DisplayController &display;

    score &score_hit_entity;

    TransferHits &transferHitCtrl;

    bool shoot_available = true;
    bool can_be_hit = true;

    void main();

    /**
     * @brief Sends the playername and weapontype to the sender channel
     * 
     * @param playername your playername which has been set in the RegGame class
     * @param weapontype your firepower which has been set in the RegGame class
     */
    void shoot(uint8_t playername, uint8_t weapontype);

   public:
/**
 * @brief Construct a new Rungame object
 * 
 * @param send_channel The channel of the IR sender 
 * @param game_par     The game parameters 
 * @param p_beeper     
 * @param p_display     
 * @param scores       The class which stores the score of players who have shot you 
 * @param transferHitCtrl The class which sends the score via usb to the host pc 
 */
    Rungame(send_controller &send_channel, 
            GameRules &game_par, 
            Beeper &p_beeper,
            DisplayController &p_display, 
            score &scores, 
            TransferHits &transferHitCtrl):
        task(3, "Rungame Control"), 
        messages(this, "Message channel"),
        second_clock(this, 1000 * rtos::ms, "seconds period clock"),
        shoot_timer(this, "shoot delay timer"),
        hit_timer(this, "Hit delay timer"),
        button_pressed_flag(this, "shoot button pressed flag"),
        sender(send_channel),
        game_par(game_par),
        beeper( p_beeper ),
        display( p_display ),
        score_hit_entity( scores ),
        transferHitCtrl( transferHitCtrl )
    {}

/**
 * @brief writes the msg into the message chhannel
 * 
 * @param msg the 16 bit message you want to write to the channel 
 */
    void write(uint16_t msg) override {
        messages.write(msg);
    }
    
/**
 * @brief sets the button_pressed_flag when button is pressed
 * 
 */
    void buttonPressed() override {
        button_pressed_flag.set();
    }
};

#endif // RUN_GAME_HPP



