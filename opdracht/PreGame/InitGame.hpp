#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class InitGame : public rtos::task<> {
   private:
    rtos::channel<char, 16> keypadchannel;

    void main() {
        enum state_t = {Idle, RegTime, SetStartSignal};
        state = Idle;
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

                    break;

                case SetStartSignal:

                    break;
            }
        }
    }

   public:
    void write(const char k) { keypadchannel.write(k); }
};

#endif  // INITGAME_HPP