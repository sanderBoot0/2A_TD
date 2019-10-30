#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "hwlib.hpp"
#include "msg_decoder.hpp"
#include "rtos.hpp"

class receiver_controller : public rtos::task<> {
   private:
    rtos::clock pause_detector_clock;
    hwlib::target::pin_in& data;
    hwlib::target::pin_out& gnd;
    hwlib::target::pin_out& vcc;
    msg_decoder& listener;

    void main() override{
        for (;;) {
            wait(pause_detector_clock);
                
            listener.pause_detected( check_pause() );
        }
    } 

   public:
        receiver_controller(
            hwlib::target::pin_in & data, hwlib::target::pin_out & gnd,
            hwlib::target::pin_out & vcc, msg_decoder & listener)
            : task(1, "receiver_controller"),
              pause_detector_clock(this, 50 * rtos::us, "pause_detector_clock"),
              data(data),
              gnd(gnd),
              vcc(vcc),
              listener(listener) {
            gnd.write(0);
            vcc.write(1);
            gnd.flush();
            vcc.flush();
        }

        uint64_t check_pause();
    };

#endif