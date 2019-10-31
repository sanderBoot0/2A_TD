#include "../headers/msg_decoder.hpp"

void msg_decoder::main() {
    enum states { idle, message };
    states state = states::idle;
    unsigned int counter = 0;
    // unsigned int initial_pause = 0;
    uint16_t msg = 0;
    uint16_t previous_msg = 0;

    for (;;) {
        switch (state) {
            case states::idle: {
                wait(pauses);
                auto pause = pauses.read();

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
                    
                    hwlib::wait_ms(5);
                }

                if (check(msg)) {
                    auto pause = pauses.read();
                    // hwlib::cout << hwlib::bin << msg << '\t' << hwlib::bin << previous_msg << '\t' << pause<< '\n';
                    if (pause > 2000 && pause < 4000 &&
                        msg == previous_msg) {
                        previous_msg = 0;
                    } else {
                        previous_msg = msg;
                        // uint8_t player = ((msg & 0b000000000011111) >> 1);
                        // uint8_t weapon = ((msg & 0b000001111100000) >> 6);
                        
                        // hwlib::cout << "P\t" << player << "\tW\t" << weapon << '\n';

                        uint8_t bericht = (msg & 0b111111110) >> 1;
                        // hwlib::cout << hwlib::dec << bericht << '\n';
                        printer.write(bericht);
                        
                        //ir_msg msg = {player, weapon};
                        //listener.msg_received(msg);
                        state = states::idle;
                    }
                } else {
                    hwlib::cout << ((msg & 0b111111110) >> 1) << '\n';
                    state = states::idle;
                }

                pauses.clear();

                state = states::idle;
                break;
            }
        }
    }
}

bool msg_decoder::check(unsigned int m) {
    uint8_t msg =  ((m & 0x3E  ) >> 1);

    uint8_t control_bits = ((m & 0xF800) >> 11);
    uint8_t control2_xor = (msg);
    if (control_bits == control2_xor) {
        return 1;
    }
    return 0;
}

