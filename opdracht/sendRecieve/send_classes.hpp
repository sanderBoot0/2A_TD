#ifndef SEND_CLASSES_HPP
#define SEND_CLASSES_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class ir_sender {
   private:
    hwlib::target::d2_36kHz send_pin;

   public:
    void send_one() {
        send_pin.write(1);
        send_pin.flush();
        hwlib::wait_us(1600);
        send_pin.write(0);
        send_pin.flush();
        hwlib::wait_us(800);
    }

    void send_zero() {
        send_pin.write(1);
        send_pin.flush();
        hwlib::wait_us(800);
        send_pin.write(0);
        hwlib::wait_us(1600);
    }

    void set_zero() { send_pin.write(0); }

    void send_message(char16_t compiled_message) {
        for (int amount_messages = 0; amount_messages < 2; amount_messages++) {
            for (int i = 15; i >= 0; i--) {
                if ((compiled_message & (1 << i)) != 0) {
                    send_one();
                } else {
                    send_zero();
                }
            }
            send_pin.write(0);
            hwlib::wait_ms(3);
        }
    }
};

class send_controller : public rtos::task<> {
   private:
    ir_sender ir_send;
    rtos::channel<char16_t, 6> messages_channel;

    void main() {
        while (1) {
            wait(messages_channel);
            send_full_message();
        }
    }

    void send_full_message() {
        auto message = messages_channel.read();
        ir_send.send_message(message);
        hwlib::cout << message << '\n';
    }

   public:
    send_controller()
        : task(1, "send_task"),
          ir_send(),
          messages_channel(this, "messages_channel") {}

    void write(char16_t value) { messages_channel.write(value); }
};

#endif