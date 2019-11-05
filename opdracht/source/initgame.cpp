#include "../headers/initgame.hpp"

void Initgame::main() {
    enum state_t { Idle, RegTime, SendTime, SetStartSignal };
    state_t state = Idle;
    uint8_t time;

    uint16_t msg = 0;
    for (;;) {
        switch (state) {
            case state_t::Idle: {
                wait(keypadchannel);
                if (keypadchannel.read() == 'C') {
                    display.clearScreen();
                    display.writeCmdPool("CMD\nC");
                    time = 0;
                    state = state_t::RegTime;
                }
                break;
            }
            case state_t::RegTime: {
                wait(keypadchannel);
                char temp = keypadchannel.read();

                if (temp >= '0' && temp <= '9' &&
                    (time * 10) < 255 - (temp - 48)) {
                    time = (time * 10) + (temp - 48);

                    display.addChar(temp);
                    display.flushScreen();
                } else if (temp == '#') {
                    if (time > 0 && time <= 15) {
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
            case state_t::SendTime: {
                wait(keypadchannel);
                char temp = keypadchannel.read();

                if (temp == '#') {
                    display.addChar(temp);
                    display.flushScreen();

                    msg = encodeMsg(time);
                    send_channel.write(msg);  // time
                    temp = '.';
                } else if (temp == '*') {
                    time = 0;
                    state = state_t::SetStartSignal;
                }

                break;
            }
            case SetStartSignal: {
                //display.showCommand("Press *\nTo send\nStart\ncmd");
                display.writeCmdPool("Press *\nTo send\nStart\ncmd");
                msg = 0 | (1 << 15);
                send_channel.write(msg);

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
