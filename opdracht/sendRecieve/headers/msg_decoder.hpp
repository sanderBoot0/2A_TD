#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class msg_decoder : public rtos::task<> {
   private:
    rtos::channel<uint64_t, 1024> pauses;

    void main();

   public:
    msg_decoder() : task(3, "decoder"), pauses(this, "pauses") {}

    void pause_detected(int pause_length) { pauses.write(pause_length); }

    bool check(unsigned int m);
};

#endif