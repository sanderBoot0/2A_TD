#ifndef TEST_RECEIVER_HPP
#define TEST_RECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class test_receiver : public rtos::task<> {
   private:
    rtos::channel<uint8_t, 10> messages;
    hwlib::terminal_from &w;

    uint32_t n_metingen = 0;
    uint32_t n_faals = 0;

    int8_t prev_msg = 0;

    void main();

   public: 

    test_receiver(hwlib::terminal_from &w):
        task( 4, "test_receiver" ),
        messages( this, "messages" ),
        w( w ) 
    {}

    void write(uint8_t msg) {
        messages.write(msg);
    }
};

#endif // TEST_RECEIVER_HPP