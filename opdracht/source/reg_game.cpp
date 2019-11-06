/**
 * @file reg_game.cpp
 * @brief source file of the RegGame class which contains the defined functions
 */
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
                //Show main menu trough display  
                display.clearScreen();
                display.writeCmdPool("Press\nA = Play\nC = Lead");
                //Wait for Keypad input 
                wait(keypadchannel);
                auto temp = keypadchannel.read();
                //If A typed: go to RegPlayer state 
                if(temp == 'A'){
                    state = regGameStates::RegPlayer;
                }
                //If C typed: go to GameLeader state 
                else if(temp == 'C'){
                    state = regGameStates::GameLeader;
                }
                break;
            }
            case GameLeader:{
                //wait state so it doesn't interfere with initgame 
                hwlib::wait_ms(1'000'000);
                break;
            }
            case RegPlayer: {
                switch (regplayerstate) {
                    case substates::waitforletter: {
                        //show playermenu trough display and go to waitfornumber 
                        hwlib::wait_ms(100);
                        display.writeCmdPool("Type\nplayer\nNumber\n");
                        regplayerstate = substates::waitfornumber;
                        break;
                    }
                    case substates::waitfornumber: {
                        //wait for Keypad input 
                        wait(keypadchannel);

                        temp = keypadchannel.read();

                        if (isNumber(temp)) {
                            //if input is number: show trough display and go to registernumber 
                            regplayerstate = substates::registernumber;
                            display.addChar(temp);
                            display.flushScreen();
                        } else {
                            //if input is not a number 
                            display.writeCmdPool("Not A\nNumber");
                            regplayerstate = substates::waitforletter;
                        }
                        break;
                    }
                    case substates::registernumber: {
                        //save number and go to regfp 
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
                        //wait for keypad input 
                        wait(keypadchannel);
                        temp = keypadchannel.read();
                        
                        //if B typed: go to waitfornumber 
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

                        //if keypadinput is a number: go to registernumber 
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
                    //save firepower and go to waitgametime     
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
                wait(messages);
                auto msg = messages.read();

              //if given value is a time value 
              if ( !( (msg & 0b11111000000000) == 0) ) {
                    break;
                }

                int time = (msg & 0b111100000) >> 5;
                
                g.setGameTime( time * 60 );

                state = regGameStates::WaitRun;
                break;
            }
            case regGameStates::WaitRun: {
                display.writeCmdPool("Waiting\nfor\nstart\nsignal");
                
                wait(messages);
                auto msg = messages.read();
                //if given value is a start signal: set the start signal to true 
                if(msg == (1 << 15)){
                    g.setStartSignal();
                    state = regGameStates::Started;
                }

                break;
            }
            //set task in wait mode 
            case regGameStates::Started: {
                hwlib::wait_ms(1'000'000'000);
                break;
            }
        }
    }
}