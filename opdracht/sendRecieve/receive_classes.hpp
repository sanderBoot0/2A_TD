#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class receiver_controller : public rtos::task<> {
   private:
    rtos::timer receive_timer;
    hwlib::target::pin_in& data;
    hwlib::target::pin_out& gnd;
    hwlib::target::pin_out& vcc;

    void main() {
        while (1) {
            receive_timer.set(400 * rtos::us);
            wait(receive_timer);
            if (get_start_bit() != -1) {
                hwlib::cout << get_message() << "\n";
                hwlib::wait_ms(1000);
            }
        }
    }

   public:
    receiver_controller(hwlib::target::pin_in& data,
                        hwlib::target::pin_out& gnd,
                        hwlib::target::pin_out& vcc)
        : task(0, "receiver_controller"),
          receive_timer(this, "receive_timer"),
          data(data),
          gnd(gnd),
          vcc(vcc) {
        gnd.write(0);
        vcc.write(1);
        gnd.flush();
        vcc.flush();
    }

    bool read_object() {
        data.refresh();
        return data.read();
    }

    int get_start_bit() {
       
        if (!read_object()) {
            hwlib::wait_us(1100);
            
            if (!read_object()) {
                hwlib::wait_us(700);
                return 1;
            } else {
                hwlib::wait_us(700);
                return 0;
            }
        }
        return -1;
    }

    int get_bit() {
        int begin = hwlib::now_us();
        
        while (read_object()) {
            hwlib::wait_us(100);
            if (begin - hwlib::now_us() >= 4000) {
                return -1;
            }
        }
        hwlib::wait_us(1100);
        
        if (!read_object()) {
            hwlib::wait_us(700);
            return 1;
        } else {
            hwlib::wait_us(700);
            return 0;
        }
        return -1;
    }

    char16_t get_message() {
        char16_t bitstream = 0;
        bitstream = bitstream << 1;
        for (int i = 0; i < 15; i++) {
            auto bit = get_bit();
            if ((bit == 1) || (bit == 0)) {
                bitstream = (bitstream | bit);
            } else if (bit == -1) {
                return -1;
            }
            if (i < 14) {
                bitstream = bitstream << 1;
            }
        }
        bitstream = bitstream | (1 << 15);
        hwlib::cout << bitstream << '\n';
        return bitstream;
    }
};

#endif