/**
 * @file run_game.cpp
 * @brief The source file of the RunGame class which contains the defined functions
 */

#include "../headers/run_game.hpp"

void Rungame::main() {
    enum states {
        CHANGE_GAME_TIME,
        HIT_AVAILABLE,
        MSG_RECV,
        SHOOTING,
        SHOOTING_AVAILABLE,
        GAME_OVER,
        IDLE
    };
    states state = states::IDLE;

    while (!game_par.getStartSignal()) { // waiting for StartSignal
        hwlib::wait_ms(1000);
    }
    display.clearScreen();

    beeper.countdown();                 // play countdown sound 3 times
    hwlib::wait_ms(1000);

    beeper.countdown();
    hwlib::wait_ms(1000);
    
    beeper.countdown();
    hwlib::wait_ms(1000);

    display.writeCmdPool("\n   Go");    // write Go to display
    beeper.start();

    for(;;) {
        switch (state) {
            case states::IDLE: {
                auto wait_event = wait(button_pressed_flag + hit_timer + second_clock + // if onne of these events triggers go to that state
                                   shoot_timer + messages);

                if (wait_event == second_clock) {
                    state = states::CHANGE_GAME_TIME;
                } else if (wait_event == shoot_timer) {
                    state = states::SHOOTING_AVAILABLE;
                } else if (wait_event == button_pressed_flag) {
                    state = states::SHOOTING;
                } else if (wait_event == messages) {
                    state = states::MSG_RECV;
                } else if (wait_event == hit_timer) {
                    state = states::HIT_AVAILABLE;
                } else {
                    state = states::GAME_OVER;
                }

                break;
            }
            case states::CHANGE_GAME_TIME: {                // this state prints the time on the display unless it's 0  then go to GAME_OVER
                auto seconds = game_par.getGameTime();

                if (seconds <= 0) {
                    state = states::GAME_OVER;
                    break;
                }
                game_par.setGameTime(--seconds);            // lower the remaining game time by 1 second
                auto score = score_hit_entity.getScore();
                display.writeGameInfoPool(seconds, score);  // display game time and score

                state = states::IDLE;
                break;
            }
            case states::HIT_AVAILABLE: {                    // when the hit timer is done you will be able to get hit again
                can_be_hit = true;

                state = states::IDLE;
                break;
            }
            case states::MSG_RECV: {                         // when hit store data of enemy player and take the dmg for the amount hit
                auto m = messages.read();

                if(can_be_hit) {
                    uint8_t playerData = (m & 0b0111110000000000) >> 10;
                    uint8_t weaponType = (m & 0b0000001111100000) >> 5;

                    if (playerData == 0 || playerData == game_par.getPlayerNumber()) {
                        state = states::IDLE;
                        break;
                    }

                    score_hit_entity.addHit(playerData, weaponType);

                    int seconds = game_par.getGameTime();
                    int score = score_hit_entity.getScore();

                    beeper.hit();

                    can_be_hit = false;         // when hit get a cooldown before you can be hit again
                    hit_timer.set(100'000);

                    if (score <= 0) {
                        score = 0;
                        state = states::GAME_OVER;
                    }   

                    display.writeGameInfoPool(seconds, score);  //  when hit update time and score on screen
                }

                state = states::IDLE;
                break;
            }
            case states::SHOOTING_AVAILABLE: {                 // allows the player to shoot once the  shoot_timer is over
                shoot_available = true;

                state = states::IDLE;
                break;
            }
            case states::SHOOTING: {                           // this state allows the player to shoot
                if (shoot_available) {
                    uint8_t playernumber = game_par.getPlayerNumber();
                    uint8_t weapontype = game_par.getFirepower();

                    shoot(playernumber, weapontype);           // shoot and play shoot sound
                    beeper.shoot();

                    shoot_timer.set(weapontype * 500'000);     // shoot_timer = weapon dmg * half_a_sec
                    shoot_available = false;
                }

                state = states::IDLE;
                break;
            }
            case states::GAME_OVER: {
                beeper.finished();
                game_par.setFinishedSignal();
                hwlib::wait_ms(1'000);
                display.writeCmdPool("\n  Game\n  Over!");
                transferHitCtrl.startTransfer();
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