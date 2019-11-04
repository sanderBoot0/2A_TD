#include "test_receiver.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

void Test_receiver::main() {
    wait(messages);
    prev_msg = messages.read();

    for(;;) {
        wait(messages);

        uint8_t msg = messages.read();
        w << '\f' << msg << '\n';

        n_metingen++;
        if(msg < prev_msg) {
            prev_msg -= 32;
        }
        n_faals += ((msg - prev_msg) -1);

        float percentage = ((n_metingen-n_faals)/(float)n_metingen) * 100;

        w << n_metingen << ' ' << n_faals << '\n';
        w << (int)percentage << '%';


        w << hwlib::flush;

        // hwlib::cout << msg << '\t' << prev_msg << '\t' << n_metingen << '\t' << n_faals << '\t' << (int)percentage << '\n';

        // w << percentage << '%' << hwlib::flush;
        prev_msg = (int8_t)msg;
    }
}