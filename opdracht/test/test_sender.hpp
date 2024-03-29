/**
 * @file test_sender.hpp
 * @brief This file contains the declaration of the Test_sender class and its functions
 */

#ifndef TEST_SENDER_HPP
#define TEST_SENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "send_classes.hpp"
/**
 * @brief This class is used to send the test messages to the  test receiver
 * 
 */
class Test_sender : public rtos::task<>{
private:
    Send_controller &sender;
    
    void main(){
        for(;;) {
            for(uint8_t i = 0; i < 32; i++) {

                hwlib::cout << hwlib::dec << i << '\n';
                shoot(i,0);

                hwlib::wait_ms(1500);
            }
        }
    }

    /**
     * @brief Makes the control bits and sends the playername, weapontype and controlbits into the sender so the IR LED can send the data
     * 
     * @param playername number between 0 and 9
     * @param weapontype number between 0 and 9
     */
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
    /**
     * @brief Constructor which initialises the objects and sets the taskpriority to 3
     * 
     * @param sender 
     */
    Test_sender(send_controller &sender):
        task(3, "send_task"),
        sender(sender)
    {}

};





#endif