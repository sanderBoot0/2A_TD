#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "send_classes.hpp"

class Initgame : public rtos::task<>{


private:
    send_controller &sender;

    void main(){
        while(true){
            shoot(5, 10);
            hwlib::wait_ms(1000);
        }

    }
public:
    Initgame(send_controller &sender):
    task(3, "send_task"),
    sender(sender){}

void shoot(uint8_t playername, uint8_t weapontype){
    uint16_t data = 0;
    data += (playername << 1);
    data += (weapontype << 6);
    uint8_t controlbits = (playername ^ weapontype);
    data += (controlbits << 11);
    sender.write(data);
}

};





#endif