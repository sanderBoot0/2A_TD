#include "../headers/run_game.hpp"

void Rungame::main() {

    enum states {IDLE, CHANGE_GAME_TIME, MSG_RECV, SHOOTING, SHOOTING_AVAILABLE};
    states state = states::IDLE;

    // while(!game_par.getStartSignal()) {
    //     hwlib::wait_ms(1000);
    // }

    hwlib::cout << 3 << '\n';
    beeper.countdown();
    hwlib::wait_ms(1000);
    hwlib::cout << 2 << '\n';
    beeper.countdown();
    hwlib::wait_ms(1000);
    hwlib::cout << 1 << '\n';
    beeper.countdown();
    hwlib::wait_ms(1000);
    hwlib::cout << "Go\n";
    beeper.start();

    for(;;) {
        auto wait_event = wait(button_pressed_flag + second_clock + shoot_timer + messages);

        if(wait_event == second_clock) {
            state = states::CHANGE_GAME_TIME;
        } else if(wait_event == shoot_timer) {
            state = states::SHOOTING_AVAILABLE;
        } else if(wait_event == button_pressed_flag) {
            state = states::SHOOTING;
        } else if(wait_event == messages){
            state = states::MSG_RECV;
        } else {
            hwlib::cout << "d\n";
        }
        
        switch(state) {
            case states::IDLE: {
                break;
            }
            case states::CHANGE_GAME_TIME: {
                // auto seconds = game_par.getGameTime();
                hwlib::cout << "tijd\n";
                break;
            }
            case states::MSG_RECV: {
                hwlib::cout << "massage\n";
                break;
            }
            case states::SHOOTING_AVAILABLE: {
                shoot_available = true;
                hwlib::cout << "shoot available\n";
                break;
            }
            case states::SHOOTING: {
                if(shoot_available) {
                    hwlib::cout << "Shoot\n";

                    uint8_t playernumber = game_par.getPlayerNumber();
                    uint8_t weapontype = game_par.getFirepower();

                    shoot(playernumber, weapontype);

                    shoot_timer.set(2'000'000);
                    shoot_available = false;
                }
            }
        }
    }
}

void Rungame::shoot(uint8_t playername, uint8_t weapontype) {
    uint16_t data = (1 << 15);
    playername &= ~(0b11100000);
    weapontype &= ~(0b11100000);
    data += (playername << 10);
    data += (weapontype << 5);
    uint8_t controlbits = (playername ^ weapontype);
    data |= controlbits;
    sender.write(data);
}