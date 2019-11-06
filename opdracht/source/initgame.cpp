/**
 * @file initgame.cpp
 * @brief this file contains the main of the Initgame class

 */
#include "../headers/initgame.hpp"

void Initgame::main() {
    enum state_t { Idle, RegTime, SendTime, SetStartSignal };
    state_t state = Idle;
    uint8_t time;

    uint16_t msg = 0;
    for (;;) {
        switch (state) {
            case state_t::Idle: {            // this state waits for the correct input to go into Gameleader mode
                wait(keypadchannel);                // waits for something to be writen in the keypadchannel
                if (keypadchannel.read() == 'C') {  // if that wich was writen in the keypadchannel  equals 'C' clear screen and write CMD to show that 
                    display.clearScreen();          // you are now in GameLeader mode
                    display.writeCmdPool("CMD\nC");
                    time = 0;
                    state = state_t::RegTime;       // jumps to next state RegTime
                }
                break;
            }
            case state_t::RegTime: {        // this state is used to request a game time from the gameleader 
                wait(keypadchannel);
                char temp = keypadchannel.read();

                if (temp >= '0' && temp <= '9' &&
                    (time * 10) < (255 - (temp - 48) ) ) { //to check if time doesn't exceed 8 bit unsigned int

                    time = (time * 10) + (temp - 48);

                    display.addChar(temp);
                    display.flushScreen();
                } else if (temp == '#') {
                    if (time > 0 && time <= 15) {      // to check if the Time does not exceed 15 minutes max to be sent via 4 bits
                        display.addChar(temp);
                        display.flushScreen();

                        state = state_t::SendTime;
                    } else {
                        display.clearScreen();
                        display.writeCmdPool("CMD\nC");
                        time = 0;
                    }
                }
                break;
            }
            case state_t::SendTime: {                   // this state is used to keep sending the time command to all players
                wait(keypadchannel);
                char temp = keypadchannel.read();

                if (temp == '#') {                      // everytime '#' is pressed it sends the time command
                    display.addChar(temp);
                    display.flushScreen();

                    msg = encodeMsg(time);
                    send_channel.write(msg);  // time
                    temp = '.';
                } else if (temp == '*') {               // when '*' is pressed go to the sendstartsignal state
                    time = 0;
                    state = state_t::SetStartSignal;
                }

                break;
            }
            case SetStartSignal: {                      // this state is used to send the start signal everytime '*' is pressed
                display.writeCmdPool("Press *\nTo send\nStart\ncmd");
                msg = 0 | (1 << 15);

                wait(keypadchannel);
                if (keypadchannel.read() == '*') {
                    send_channel.write(msg);
                }else{
                    state = Idle;
                    display.clearScreen();
                }

                break;
            }
        }
    }
}


uint16_t Initgame::encodeMsg(uint8_t data) {    
    uint16_t msg = (1 << 15);

    data &= ~(0b11110000);
    msg += (data << 5);
    msg |= data;

    return msg;
}
