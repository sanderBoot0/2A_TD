#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "../test/test_receiver.hpp"

#include "hwlib.hpp"
#include "msglistener.hpp"
#include "rtos.hpp"

class Receiver_controller : public rtos::task<> {
   private:
    rtos::clock pause_detector_clock;

	MsgListener* listeners[2];
    int n_listeners = 0;

    hwlib::target::pin_in data = hwlib::target::pin_in(hwlib::target::pins::d8);
    hwlib::target::pin_out gnd  = hwlib::target::pin_out(hwlib::target::pins::d10);
    hwlib::target::pin_out vcc  = hwlib::target::pin_out(hwlib::target::pins::d9);

    int get_bit();
    bool check_equal(bool message1[16], bool message2[16]);
    bool check(uint16_t m);

    void main();

   public:
    Receiver_controller(): 
		task(1, "receiver_controller"),
        pause_detector_clock(this, 50 * rtos::us, "pause_detector_clock") 
    {
        gnd.write(0);
        vcc.write(1);
        gnd.flush();
        vcc.flush();
    }

    void addListener(MsgListener* m) {
        listeners[n_listeners] = m;
        n_listeners++;
    }
};

#endif