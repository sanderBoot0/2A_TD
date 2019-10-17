#ifndef TESTER_HPP
#define TESTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "send_classes.hpp"

class test : public rtos::task<>{


private:
    send_controller &sender;

    void main(){
        while(true){
            sender.write(0);
            hwlib::wait_ms(1000);
        }

    }
public:
    test(send_controller &sender):
    task(3, "send_task"),
    sender(sender){}

};





#endif