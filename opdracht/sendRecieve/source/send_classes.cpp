#include "../headers/send_classes.hpp"

void ir_sender::send_bit(const bool &bit) {
    send_pin.write(1);      send_pin.flush();
    hwlib::wait_us(800);
    send_pin.write(bit);    send_pin.flush();
    hwlib::wait_us(800);
    send_pin.write(0);      send_pin.flush();
    hwlib::wait_us(800);
}

void ir_sender::set_zero() { send_pin.write(0); }

void ir_sender::send_message(char16_t compiled_message) {
        send_one();
        for (int i = 15; i >= 0; i--) {
            // if ((compiled_message & (1 << i)) != 0) {
            //     send_one();
            // } else {
            //     send_zero();
            // }
            send_bit( ( (compiled_message & (1 << i)) != 0) ? 1 : 0 );
        }
        send_pin.write(0);
        send_pin.flush();
        hwlib::wait_ms(3);
            for (int i = 15; i >= 0; i--) {
            if ((compiled_message & (1 << i)) != 0) {
                send_one();
            } else {
                send_zero();
            }
        }
        send_pin.write(0);
        send_pin.flush();
        hwlib::wait_ms(3);
    
}