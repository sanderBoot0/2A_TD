/**
 * @file receive_classes.cpp
 * @brief source file of the receive_classes class where the functions are defined 
 */

#include "../headers/receive_classes.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

void Receiver_controller::main(){
    bool message1[16];
    bool message2[16];

    enum states {RECEIVING_MESSAGE, RECEIVING_CONTROL_MESSAGE, DECODING_MESSAGE};
    states state = states::RECEIVING_MESSAGE;

    int position = 0;

    for(;;) {
        switch(state) { // check for a start bit
            case states::RECEIVING_MESSAGE: {
                int bit = get_bit();

                if (bit == 2) {         // if there is no start bit go back to the first position in the message array
                    position = 0;
                    break;
                }

                message1[position] = bit && 1;

                if(position == 0)   
                    message1[position] = 1;

                position++;         
                if(position == 16) {        // get 16 bits then wait 3 ms for the pause
                    position = 0;
                    state = states::RECEIVING_CONTROL_MESSAGE;
                    hwlib::wait_ms(3);
                }
                break;
            }
            case states::RECEIVING_CONTROL_MESSAGE: {  // same as previous state butt for the coontrol message
                int bit = get_bit();

                if(bit == 2) {
                    position = 0;
                    state = states::RECEIVING_MESSAGE;
                    break;
                }

                message2[position] = bit && 1;

                if(position == 0) 
                    message2[position] = 1;

                position++;
                if(position == 16) {
                    position = 0;
                    if(!check_equal(message1, message2)) {  // check if message 1 and message2 are equal; this means the received data is correct
                        state = states::RECEIVING_MESSAGE;
                    }
                    state = states::DECODING_MESSAGE;
                }
                break;
            }
            case states::DECODING_MESSAGE: {  // decode message1
                uint16_t message = 0;
                for(int i = 0; i < 16; i++ ) { // make a uint16_t from the message1[] array
                    message <<= 1;
                    message |= message1[i];
                }
                if(check(message)) { // check if the controlbits are correct
                    for(int i = 0; i < n_listeners; i++) {
                        listeners[i]->write(message); // write the message naar alle listeners
                    }
                    
                }
                state = states::RECEIVING_MESSAGE;
                break;
            }
        }
    }
} 

bool Receiver_controller::check_equal(bool message1[16], bool message2[16]) {
    for(int i = 0; i < 16; i++) {
        if(message1[i] != message2[i]) {
            return false;
        }
    }
    return true;
}

bool Receiver_controller::check(uint16_t m) {
    // use a mask to get the data from the msg
    uint8_t playerData =   (m & 0b0111110000000000) >> 10;
    uint8_t weaponType =   (m & 0b0000001111100000) >> 5 ;

    uint8_t control_bits = (m & 0b0000000000011111);
    
    if (control_bits == (playerData ^ weaponType) ) {
        return 1;
    }
    return 0;
}

int Receiver_controller::get_bit() {
    bool signal_2nd_check = 0;
    bool signal_3rd_check = 0;
   
    
    // Wait for signal to get high
    int waiting_time = 0;
    while(data.read()) {
        if(waiting_time == 4000) 
            return 2;
        
        wait(pause_detector_clock);
        waiting_time += 50;
    }

    hwlib::wait_us(1000);
    signal_2nd_check = !data.read();
    hwlib::wait_us(800);
    signal_3rd_check = !data.read();

    if(signal_3rd_check)
        return 2;

    return signal_2nd_check;
}
