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

class Rungame : public rtos::task<>, public MsgListener, public Buttonlistener {
   private:
    rtos::channel<uint16_t, 10> messages;

    rtos::clock second_clock;
    rtos::timer shoot_timer;
    rtos::flag button_pressed_flag;

    send_controller &sender;

    GameRules &game_par;

    Beeper &beeper;

    DisplayController &display;

    score &score_hit_entity;

    bool shoot_available = true;

    void main();

    void shoot(uint8_t playername, uint8_t weapontype);

    void write(uint16_t msg) override {
        messages.write(msg);
    }

   public:

    Rungame(send_controller &send_channel, GameRules &game_par, Beeper &p_beeper, DisplayController &p_display, score &scores):
        task(3, "Rungame Control"), 
        messages(this, "Message channel"),
        second_clock(this, 1000 * rtos::ms, "seconds period clock"),
        shoot_timer(this, "shoot delay timer"),
        button_pressed_flag(this, "shoot button pressed flag"),
        sender(send_channel),
        game_par(game_par),
        beeper( p_beeper ),
        display( p_display),
        score_hit_entity( scores )
    {}

    void buttonPressed() override {
        button_pressed_flag.set();
    }
};

#endif // RUN_GAME_HPP



