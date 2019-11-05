#include "../headers/reg_game.hpp"

void RegGame::main() {
    enum regGameStates { Idle, RegPlayer, RegFP, WaitGameTime, WaitRun, GameLeader, Started };
    enum substates { waitforletter, waitfornumber, registernumber };
    substates regplayerstate = substates::waitforletter;
    substates regfirepowerstate = substates::waitforletter;

    char temp;

    regGameStates state = regGameStates::Idle;

   
    for (;;) {

        switch (state) {
            case Idle: {
                display.clearScreen();
                display.writeCmdPool("Press\nA = Play\nC = Lead");
                wait(keypadchannel);
                auto temp = keypadchannel.read();
                if(temp == 'A'){
                    state = regGameStates::RegPlayer;
                }
                else if(temp == 'C'){
                    state = regGameStates::GameLeader;
                }
                break;
            }
            case GameLeader:{
                hwlib::wait_ms(1'000'000);
                break;
            }
            case RegPlayer: {
                switch (regplayerstate) {
                    case substates::waitforletter: {
                        hwlib::wait_ms(100);
                        display.writeCmdPool("Type\nplayer\nNumber\n");
                        regplayerstate = substates::waitfornumber;
                        break;
                    }
                    case substates::waitfornumber: {
                        wait(keypadchannel);

                        temp = keypadchannel.read();

                        if (isNumber(temp)) {
                            regplayerstate = substates::registernumber;
                            display.addChar(temp);
                            display.flushScreen();
                        } else {
                            // Vraag nieuw nummer
                            display.writeCmdPool("Not A\nNumber");
                            regplayerstate = substates::waitforletter;
                        }
                        break;
                    }
                    case substates::registernumber: {
                        g.setPlayerNumber(temp - 48);
                        state = regGameStates::RegFP;
                        display.writeCmdPool("Press B\nfor\nweapon\npower");
                        break;
                    }
                }
                break;
            }
            case regGameStates::RegFP: {
                switch (regfirepowerstate) {
                    case substates::waitforletter: {
                        wait(keypadchannel);
                        temp = keypadchannel.read();
                        
                        if (temp == 'B') {
                            regfirepowerstate = substates::waitfornumber;
                        }
                        break;
                    }
                    case substates::waitfornumber: {
                        hwlib::wait_ms(100);
                        display.writeCmdPool("Type\nweapon\npower\n");
                        wait(keypadchannel);
                        temp = keypadchannel.read();

                        if (isNumber(temp)) {
                            regfirepowerstate = substates::registernumber;
                            display.addChar(temp);
                            display.flushScreen();
                            hwlib::wait_ms(100);
                        } else {
                            display.writeCmdPool("Not a\nNumber");
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
                // Wait for IR input
                // If(IR Input == time)
                display.writeCmdPool("Waiting\nfor\ntime...");
                auto msg = messages.read();

                if ( !( (msg & 0b11111000000000) == 0) ) {
                    break;
                }

                int time = (msg & 0b111100000) >> 5;

                hwlib::cout << "received time\n";
                
                g.setGameTime( time * 60 );

                state = regGameStates::WaitRun;
                break;
            }
            case regGameStates::WaitRun: {
                // hwlib::cout << "WaitRun state" << hwlib::endl;
                // hwlib::wait_ms(1000);
                display.writeCmdPool("Waiting\nfor\nstart\nsignal");
                
                auto msg = messages.read();
                if(msg == (1 << 15)){
                    g.setStartSignal();
                    state = regGameStates::Started;
                }



                break;
            }
            case regGameStates::Started: {
                hwlib::wait_ms(1'000'000'000);
                break;
            }
        }
    }
}