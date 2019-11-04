#ifndef RUN_GAME_HPP
#define RUN_GAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "gamerules.hpp"

#include "button.hpp"
#include "buttonlistener.hpp"

#include "send_classes.hpp"

class Rungame : public rtos::task<>, public Buttonlistener {
   private:
    rtos::clock second_clock;
    rtos::timer shoot_timer;
    rtos::flag button_pressed_flag;

    send_controller &sender;

    GameRules &game_par;

    bool shoot_available = true;

    void main();

    void shoot(uint8_t playername, uint8_t weapontype);

   public:

    Rungame(send_controller &send_channel, GameRules &game_par):
        task(3, "Rungame Control"), 
        second_clock(this, 1000 * rtos::ms, "seconds period clock"),
        shoot_timer(this, "shoot delay timer"),
        button_pressed_flag(this, "shoot button pressed flag"),
        sender(send_channel),
        game_par(game_par)
    {}

    void buttonPressed() override {
        button_pressed_flag.set();
    }
};

#endif // RUN_GAME_HPP