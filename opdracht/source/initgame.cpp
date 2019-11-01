#include "../headers/initgame.hpp"

void Initgame::main() {
    enum state_t = {Idle, RegTime, SetStartSignal};
    state = Idle;
    uint8_t time = 0;
    for (;;) {
        switch (state) {
            case Idle:
                wait(keypadchannel);
                if (keypadchannel.read() == 'C') {
                    state = RegTime;
                }
                break;

            case RegTime:
                wait(keypadchannel);
                char temp = keypadchannel.read();

                if temp == '1'){
                    time = 1;
                    /// show on  display
                    wait(keypadchannel);
                    temp = keypadchannel.read();
                    // kan alleen nog maar 0 tot 5 invullen
                    

                }else if ( temp >= '2' && temp <= '9'){
                    // kan nu alleen nog maar # intoetsen

                    
                }else if ( time > 0 && temp == "#"){
                    //send command
                }
                
                

                send_channel.write(msg);

                break;

            case SetStartSignal:
                wait(keypadchannel);



                send_channel.write(msg);

                break;
        }
    }
}