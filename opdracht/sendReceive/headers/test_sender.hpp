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
            for(uint8_t i = 0; i < 32; i++) {

                hwlib::cout << hwlib::dec << i << '\n';
                shoot(i,0);

                hwlib::wait_ms(1500);
            }
        }
    }

    
    void shoot(uint8_t playername, uint8_t weapontype) {
        uint16_t data = (1 << 15);
        playername &= ~(0b11100000);
        weapontype &= ~(0b11100000);
        data += (playername << 10);
        data += (weapontype << 5);
        uint8_t controlbits = (playername ^ weapontype);
        data |= controlbits;
        hwlib::cout << hwlib::bin << data << '\n';
        sender.write(data);
}

    
public:
    test_sender(send_controller &sender):
        task(3, "send_task"),
        sender(sender)
    {}

};





#endif