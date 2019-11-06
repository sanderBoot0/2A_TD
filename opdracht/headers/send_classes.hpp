/**
 * @file send_classes.hpp
 * @brief This file contains the declaration of the send_classes class and its functions
 */

#ifndef SEND_CLASSES_HPP
#define SEND_CLASSES_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
/**
 * @brief Class that sends all the messages
 * 
 */
class ir_sender {
   private:
    hwlib::target::d2_36kHz send_pin;

    /**
     * @brief Sends a single bit with IR LED
     * 
     * @param bit The bit that will be sent
     */
    void send_bit(const bool bit);
    
   public:
   /**
    * @brief Sends all the messages using send_bit()
    * 
    * @param compiled_message The message to be sent with IR
    */
    void send_message(char16_t compiled_message);
};
/**
 * @brief Send controller class. This is a Rtos task that has a message channel that recieves messages from the Rungame & InitGame classes 
 * 
 */
class send_controller : public rtos::task<> {
   private:
    ir_sender ir_send;
    rtos::channel<char16_t, 10> messages_channel;

    void main() {
        while (1) {
            wait(messages_channel);         // waits for a message in the channel
            //hwlib::wait_ms(1000);           //
            send_full_message();    
        }
    }
    /**
     * @brief Reads the messages_channel and sends those messages
     * 
     */
    void send_full_message() {
        auto message = messages_channel.read();
        ir_send.send_message(message);
    }

   public:
    send_controller(): 
        task(2, "send_task"),
        messages_channel(this, "messages_channel") 
    {}

    /**
     * @brief Writes a value into the messages_channel. To be used with a listener
     * 
     * @param value The value to be writed into the channel
     */
    void write(char16_t value) { messages_channel.write(value); }
};

#endif