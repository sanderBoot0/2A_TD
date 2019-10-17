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
            // while (data.read()) {
            // }

            // for (int i = 0; i < 32; i++) {
                //pauses[i] = check_pause();
                
            listener.pause_detected( check_pause() );
            // }
            // for (int i = 0; i < 32; i++) {
            //     hwlib::cout << pauses[i] << ' ';
            // }
            // hwlib::cout << '\n';
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

        uint64_t check_pause() {
            uint64_t begin_time;

            while (!data.read()) {
                begin_time = hwlib::now_us();
            }

            while (data.read()) {
                wait(pause_detector_clock);
            }

            uint64_t pause_length = hwlib::now_us() - begin_time;
            // hwlib::cout << pause_length << '\n';
            return pause_length;
        }
    };

#endif