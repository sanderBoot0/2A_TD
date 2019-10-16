#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "msg_decoder.hpp"

class receiver_controller : public rtos::task<> {
   private:
    rtos::clock pause_detector_clock;
    hwlib::target::pin_in& data;
    hwlib::target::pin_out& gnd;
    hwlib::target::pin_out& vcc;
    msg_decoder& listener;

    void main() {
        enum states { idle, signal };
        states state = states::idle;
        unsigned int pause_length = 0;

        for (;;) {
            switch (state) {
                case states::idle: {
                    wait(pause_detector_clock);
                    if (read_object()) {
                        pause_length += 100;
                    } else {
                        listener.pause_detected(pause_length);
                        //						hwlib::cout
                        //<< pause_length << "\n";
                        state = states::signal;
                    }
                    break;
                }

                case states::signal: {
                    hwlib::cout << "in signal\n";
                    if (read_object()) {
                        pause_length = 0;
                        state = states::idle;
                    }
                    break;
                }
            }
        }
    }

   public:
    receiver_controller(hwlib::target::pin_in& data,
                        hwlib::target::pin_out& gnd,
                        hwlib::target::pin_out& vcc, 
                        msg_decoder& listener)
        : task(0, "receiver_controller"),
          pause_detector_clock(this, 100 * rtos::us, "pause_detector_clock"),
          data(data),
          gnd(gnd),
          vcc(vcc),
          listener(listener) {
        gnd.write(0);
        vcc.write(1);
        gnd.flush();
        vcc.flush();
    }

    bool read_object() {
        data.refresh();
        return data.read();
    }
};

#endif