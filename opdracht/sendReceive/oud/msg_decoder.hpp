#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "test_receiver.hpp"

class msg_decoder : public rtos::task<> {
   private:
    rtos::channel<uint64_t, 1024> pauses;
    test_receiver &printer;

    void main();

   public:
    msg_decoder(test_receiver & printer) : task(3, "decoder"), pauses(this, "pauses"), printer(printer) {}

    void pause_detected(int pause_length) { pauses.write(pause_length); }

    bool check(unsigned int m);
};

#endif