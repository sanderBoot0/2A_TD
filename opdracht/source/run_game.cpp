#include "../headers/run_game.hpp"

void Rungame::main() {
    enum states {
        CHANGE_GAME_TIME,
        MSG_RECV,
        SHOOTING,
        SHOOTING_AVAILABLE,
        GAME_OVER
    };
    states state;

    while (!game_par.getStartSignal()) {
        hwlib::wait_ms(1000);
    }
    display.clearScreen();

    beeper.countdown();
    hwlib::wait_ms(1000);

    beeper.countdown();
    hwlib::wait_ms(1000);
    
    beeper.countdown();
    hwlib::wait_ms(1000);

    display.writeCmdPool("\n   Go");
    //hwlib::cout << "Go\n";
    beeper.start();

    for(;;) {
        if (state != states::GAME_OVER) {
            auto wait_event = wait(button_pressed_flag + second_clock +
                                   shoot_timer + messages);

            if (wait_event == second_clock) {
                state = states::CHANGE_GAME_TIME;
            } else if (wait_event == shoot_timer) {
                state = states::SHOOTING_AVAILABLE;
            } else if (wait_event == button_pressed_flag) {
                state = states::SHOOTING;
            } else if (wait_event == messages) {
                state = states::MSG_RECV;
            } else {
                state = states::GAME_OVER;
            }
        }

        switch (state) {
            case states::CHANGE_GAME_TIME: {
                // hwlib::cout << "Tijd\n";
                auto seconds = game_par.getGameTime();
                hwlib::cout << seconds << '\n';
                if (seconds <= 0) {
                    // hwlib::cout << "seconds 0\n";
                    state = states::GAME_OVER;
                    break;
                }
                game_par.setGameTime(--seconds);
                auto score = score_hit_entity.getScore();
                display.writeGameInfoPool(seconds, score);

                break;
            }
            case states::MSG_RECV: {
                // hwlib::cout << "message\n";

                auto m = messages.read();

                uint8_t playerData = (m & 0b0111110000000000) >> 10;
                uint8_t weaponType = (m & 0b0000001111100000) >> 5;

                if (playerData == 0) {
                    break;
                }

                score_hit_entity.addHit(playerData, weaponType);

                int seconds = game_par.getGameTime();
                int score = score_hit_entity.getScore();

                beeper.hit();

                if (score <= 0) {
                    // hwlib::cout << "Score 0\n";
                    state = states::GAME_OVER;
                }
                display.writeGameInfoPool(seconds, score);
                break;
            }
            case states::SHOOTING_AVAILABLE: {
                shoot_available = true;
                break;
            }
            case states::SHOOTING: {
                if (shoot_available) {
                    uint8_t playernumber = game_par.getPlayerNumber();
                    uint8_t weapontype = game_par.getFirepower();

                    shoot(playernumber, weapontype);
                    beeper.shoot();

                    shoot_timer.set(weapontype * 500'000);
                    shoot_available = false;
                }
                break;
            }
            case states::GAME_OVER: {
                beeper.finished();
                game_par.setFinishedSignal();
                hwlib::wait_ms(1'000);
                display.writeCmdPool("\n  Game\n  Over!");
                hwlib::wait_ms(1'000'000'000);
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