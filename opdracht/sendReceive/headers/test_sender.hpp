#ifndef TEST_SENDER_HPP
#define TEST_SENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "send_classes.hpp"

class test_sender : public rtos::task<>{
private:
    send_controller &sender;

    void main(){
        for(;;) {
            for(uint8_t i = 0; i < 100; i++) {
                hwlib::cout << hwlib::dec << i << '\n';
                uint16_t data = 0;
                data += i << 1;
                uint8_t controlbits = i;
                data += (controlbits << 11);
                sender.write(data);
                // sender.write(i);
                hwlib::wait_ms(1000);
            }
        }
    }
    
public:
    test_sender(send_controller &sender):
        task(3, "send_task"),
        sender(sender)
    {}

};





#endif