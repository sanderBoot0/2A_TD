#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class msg_decoder : public rtos::task<> {
   private:
    rtos::channel<uint64_t, 1024> pauses;

    void main() {
        enum states { idle, message };
        states state = states::idle;
        unsigned int counter = 0;
        // unsigned int initial_pause = 0;
        uint16_t msg = 0;
        uint16_t previous_msg = 0;

        hwlib::cout << "Augurk\n";

        for (;;) {
            switch (state) {
                case states::idle: {
                    // hwlib::cout << "Idle\n";
                    wait(pauses);
                    auto pause = pauses.read();
                    // hwlib::cout << pause << '\n';
                    if (pause > 600 && pause < 1000) {
                        state = states::message;
                    }
                    break;
                }

                case states::message: {
                    hwlib::wait_ms(100);
                    msg = 0;
                    counter = 0;
                    for (int i = 0; i < 16; i++) {
                        auto pause = pauses.read();
                        msg <<= 1;
                        if (pause > 600 && pause < 1000)
                            msg |= 1;
                        else if (pause > 1400 && pause < 1800)
                            msg = msg & ~(0x1);
                        else
                            state = states::idle;
                    }

                    if (check(msg)) {
                        auto pause = pauses.read();
                        hwlib::cout << hwlib::bin << msg << '\t' << hwlib::bin << previous_msg << '\t' << pause<< '\n';
                        if (pause > 2000 && pause < 4000 &&
                            msg == previous_msg) {
                            previous_msg = 0;
                        } else {
                            previous_msg = msg;
                            uint8_t player = ((msg & 0b000000000011111) >> 1);
                            uint8_t weapon = ((msg & 0b000001111100000) >> 6);
                            
                            hwlib::cout << "P\t" << player << "\tW\t" << weapon << '\n';
                            
                            //ir_msg msg = {player, weapon};
                            //listener.msg_received(msg);
                            state = states::idle;
                        }
                    } else {
                        state = states::idle;
                    }

                    //hwlib::cout << hwlib::bin << msg << '\n';

                    pauses.clear();

                    state = states::idle;
                    break;
                }
            }
        }
    }

   public:
    msg_decoder() : task(3, "decoder"), pauses(this, "pauses") {}

    void pause_detected(int pause_length) { pauses.write(pause_length); }

    bool check(unsigned int m) {
        uint8_t player = ((m & 0b0000000000111110) >> 1);
        uint8_t weapon = ((m & 0b0000011111000000) >> 6);
        uint8_t control = ((m & 0b1111100000000000) >> 11);
        uint8_t control2 = (player ^ weapon);
        if (control == control2) {
            return 1;
        }
        return 0;
    }
};

#endif