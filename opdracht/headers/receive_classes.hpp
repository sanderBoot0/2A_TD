#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "../test/test_receiver.hpp"

#include "hwlib.hpp"
#include "msglistener.hpp"
#include "rtos.hpp"

class Receiver_controller : public rtos::task<> {
   private:
    rtos::clock pause_detector_clock;
    hwlib::pin_in& data;
    hwlib::pin_out& gnd;
    hwlib::pin_out& vcc;

    MsgListener* listeners[5];
    int n_listeners = 0;

    int get_bit();
    bool check_equal(bool message1[16], bool message2[16]);
    bool check(uint16_t m);

    void main();

   public:
    Receiver_controller(hwlib::pin_in& data, hwlib::pin_out& gnd,
                        hwlib::pin_out& vcc)
        : task(1, "receiver_controller"),
          pause_detector_clock(this, 50 * rtos::us, "pause_detector_clock"),
          data(data),
          gnd(gnd),
          vcc(vcc) {
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