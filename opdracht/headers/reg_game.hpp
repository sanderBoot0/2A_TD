#ifndef REGGAME_HPP
#define REGGAME_HPP

#include "gamerules.hpp"
#include "hwlib.hpp"
#include "rtos.hpp"

bool isNumber(char c) { return bool((c >= '0') && (c <= '9')); }

class RegGame : public rtos::task<> {
   private:
    rtos::channel<char, 16> keypadchannel;

    GameRules g;

    void main() {
        enum regGameStates { Idle, RegPlayer, RegFP, WaitGameTime, WaitRun };
        enum substates { waitforletter, waitfornumber, registernumber };
        substates regplayerstate = substates::waitforletter;
        substates regfirepowerstate = substates::waitforletter;

        char temp;

        regGameStates state = regGameStates::RegPlayer;

        hwlib::cout << "Type A to Continue, " << '\n';
        for (;;) {

            switch (state) {
                case Idle: {
                    hwlib::cout << "Idle state" << hwlib::endl;
                    break;
                }
                case RegPlayer: {
                    switch (regplayerstate) {
                        case substates::waitforletter: {
                            wait(keypadchannel);

                            if (keypadchannel.read() == 'A') {
                                hwlib::cout << "A pressed, " << '\n'
                                            << "Type Number" << '\n';
                                regplayerstate = substates::waitfornumber;
                            }
                            break;
                        }
                        case substates::waitfornumber: {
                            wait(keypadchannel);

                            temp = keypadchannel.read();

                            if (isNumber(temp)) {
                                regplayerstate = substates::registernumber;
                                hwlib::cout << "your player number is: " << temp << '\n';
                                hwlib::cout << "Saving player number" << '\n';
                            } else {
                                // Vraag nieuw nummer
                                hwlib::cout << "not a number" << '\n';
                            }
                            break;
                        }
                        case substates::registernumber: {
                            g.setPlayerNumber(temp - 48);
                            state = regGameStates::RegFP;
                            hwlib::cout << "Type B to continue" << '\n';
                            break;
                        }
                    }
                    break;
                }
                case regGameStates::RegFP: {
                    switch (regfirepowerstate) {
                        case substates::waitforletter: {
                            temp = keypadchannel.read();
                            
                            if (temp == 'B') {
                                hwlib::cout << "B pressed, " << '\n';
                                regfirepowerstate = substates::waitfornumber;
                                hwlib::cout << "Type a number" << '\n';
                            }
                            break;
                        }
                        case substates::waitfornumber: {
                            temp = keypadchannel.read();

                            if (isNumber(temp)) {
                                regfirepowerstate = substates::registernumber;
                                hwlib::cout << "your fire power is: " << temp << '\n';
                            } else {
                                hwlib::cout << "wrong number" << '\n';
                            }
                            break;
                        }
                        case substates::registernumber: {
                            g.setFirePower((temp - 48));
                            state = regGameStates::WaitGameTime;
                            break;
                        }
                    }

                    break;
                }
                case regGameStates::WaitGameTime: {
                    hwlib::cout << "WaitGameTime state" << hwlib::endl;
                    hwlib::wait_ms(1000);
                    // Wait for IR input
                    // If(IR Input == time)
                    // setGameTime(IR Input)
                    // state = WaitRun
                    break;
                }
                case regGameStates::WaitRun: {
                    hwlib::cout << "WaitRun state" << hwlib::endl;
                    hwlib::wait_ms(1000);
                    // Wait for IR Input
                    // if(IR Input == start)
                    //
                    break;
                }
            }
        }
    }

   public:
    RegGame()
        : task(4, "RegGame"),
          keypadchannel(this, "keypadchannel")
    {}

    void write(const char k) { keypadchannel.write(k); }
};

#endif
