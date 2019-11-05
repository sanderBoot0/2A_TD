/**
 * @file beeperCtrl.hpp
 * @brief this object will control all the sounds that needs to be played 
 * 
 */

#ifndef BEEPERCTRL_HPP
#define BEEPERCTRL_HPP

#include "note_player_gpio.hpp"
#include "hwlib.hpp"

/// @brief This class controls the beeper
/// @details This class waits for flags that are set by the RunGame class. When a flag is set, the Beeper control will play the right sound.
class Beeper : public rtos::task<> {
private:
    rtos::flag countdown_flag;
    rtos::flag start_flag;
    rtos::flag shoot_flag;
    rtos::flag hit_flag;
    rtos::flag finished_flag;
    
    hwlib::target::pin_out beeper_pin = hwlib::target::pin_out( hwlib::target::pins::d7 );
    note_player_gpio p = note_player_gpio( beeper_pin );

    void main() {
        for(;;) {
            auto event = wait(countdown_flag + start_flag + shoot_flag + hit_flag + finished_flag);
            if(event == countdown_flag) {
                p.play( note{ note::B5,  note::dQ } );
            } else if(event == start_flag) {
                p.play( note{ note::B5, note::dF } );
            } else if(event == shoot_flag) {
                p.play( note{ note::A4, note::dQ } );
            } else if(event == hit_flag) {
                p.play( note{ note::C5, note::dQ } );
                p.play( note{ note::E5, note::dQ } );
                p.play( note{ note::G5, note::dQ } );
            } else if(event == finished_flag) {
                p.play( note{ note::B4, note::dQ } );
                p.play( note{ note::C5, note::dQ } );
                p.play( note{ note::D5, note::dQ } );
                p.play( note{ note::E5, note::dQ } );
                p.play( note{ note::F5, note::dQ } );
                p.play( note{ note::G5, note::dQ } );
                p.play( note{ note::A5, note::dQ } );
                p.play( note{ note::B5, note::dH } );
            }
            hwlib::wait_ms(1000);
        }
    }

public: 
    Beeper() :
        task(5, "Beep task"),
        countdown_flag(this, "countdown beep flag"),
        start_flag(this, "start beep flag"),
        shoot_flag(this, "shoot beep flag"),
        hit_flag(this, "hit beep flag"),
        finished_flag(this, "finished beep flag")
    {}

    void countdown() {
        countdown_flag.set();
    }

    void start() {
        start_flag.set();
    }

    void shoot() {
        shoot_flag.set();
    }

    void hit() {
        hit_flag.set();
    }

    void finished() {
        finished_flag.set();
    }
};

#endif // BEEPERCTRL_HPP