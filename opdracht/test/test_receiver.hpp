#ifndef TEST_RECEIVER_HPP
#define TEST_RECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
/**
 * @brief this class is used to test the receive percentage of incomming messages
 * 
 */
class Test_receiver : public rtos::task<> {
   private:
    rtos::channel<uint8_t, 10> messages;
    hwlib::terminal_from &w;

    uint32_t n_metingen = 0;
    uint32_t n_faals = 0;

    int8_t prev_msg = 0;

    void main();

   public: 
/**
 * @brief Construct a new Test_receiver object
 * 
 * @param w 
 */
    Test_receiver(hwlib::terminal_from &w):
        task( 4, "test_receiver" ),
        messages( this, "messages" ),
        w( w ) 
    {}

/**
 * @brief Writes a message into the messages channel
 * 
 * @param msg 
 */
    void write(uint8_t msg) {
        messages.write(msg);
    }
};

#endif // TEST_RECEIVER_HPP