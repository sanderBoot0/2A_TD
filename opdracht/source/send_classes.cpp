#include "../headers/send_classes.hpp"

void ir_sender::send_bit(const bool bit) {
    send_pin.write(1);      send_pin.flush();
    hwlib::wait_us(800);
    send_pin.write(bit);    send_pin.flush();
    hwlib::wait_us(800);
    send_pin.write(0);      send_pin.flush();
    hwlib::wait_us(800);
}

void ir_sender::send_message(char16_t compiled_message) {
        
    // send msg 1st time  MSB first
    for (int i = 15; i >= 0; i--) {
        send_bit( ( (compiled_message & (1 << i)) != 0) /* ? 1 : 0 */ );
    }

    // write 3ms Pause
    send_pin.write(0);  send_pin.flush();
    hwlib::wait_ms(3);

    // Send message 2nd time  MSB first
    for (int i = 15; i >= 0; i--) {
        send_bit( ( (compiled_message & (1 << i)) != 0) /* ? 1 : 0 */ );
    }

    send_pin.write(0);  send_pin.flush();    
}