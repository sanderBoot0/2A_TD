#ifndef SEND_CLASSES_HPP
#define SEND_CLASSES_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class ir_sender {
   private:
    hwlib::target::d2_36kHz send_pin;

   public:
    void send_bit(const bool bit);

    void set_zero() { send_pin.write(0); }

    void send_message(char16_t compiled_message);
};

class send_controller : public rtos::task<> {
   private:
    ir_sender ir_send;
    rtos::channel<char16_t, 10> messages_channel;

    void main() {
        while (1) {
            wait(messages_channel);
            hwlib::wait_ms(1000);
            send_full_message();
        }
    }

    void send_full_message() {
        auto message = messages_channel.read();
        ir_send.send_message(message);
        // hwlib::cout  << hwlib::bin << message << '\n';
    }

   public:
    send_controller(): 
        task(2, "send_task"),
        ir_send(),
        messages_channel(this, "messages_channel") 
    {}

    void write(char16_t value) { messages_channel.write(value); }
};

#endif