/**
 * @file receive_classes.hpp
 * @brief This file contains the receive classes
 */


#ifndef RECEIVE_CLASSES_HPP
#define RECEIVE_CLASSES_HPP

#include "../test/test_receiver.hpp"

#include "hwlib.hpp"
#include "msglistener.hpp"
#include "rtos.hpp"


/**
 * @brief this class contains all the functions to receive en decode incomming messages
 * 
 */
class Receiver_controller : public rtos::task<> {
   private:
    rtos::clock pause_detector_clock;

	MsgListener* listeners[2];
    int n_listeners = 0;

    hwlib::target::pin_in data = hwlib::target::pin_in(hwlib::target::pins::d8);
    hwlib::target::pin_out gnd  = hwlib::target::pin_out(hwlib::target::pins::d10);
    hwlib::target::pin_out vcc  = hwlib::target::pin_out(hwlib::target::pins::d9);

    /**
     * @brief Get the bit object. If getting the bit takes too long, returns a time-out
     * 
     * @return int 0 or 1 for the bits. 2 for timeout
     */
    int get_bit();
    
    /**
     * @brief checks if the two given message arrays are equal
     * 
     * @param message1 
     * @param message2 
     * @return true 
     * @return false 
     */
    bool check_equal(bool message1[16], bool message2[16]);
    /**
     * @brief checks if the given message is a valid message with correct control bits
     * 
     * @param m 
     * @return true 
     * @return false 
     */
    bool check(uint16_t m);

    void main();

   public:
   /**
    * @brief Construct a new Receiver_controller object
    * 
    */
    Receiver_controller(): 
		task(1, "receiver_controller"),
        pause_detector_clock(this, 50 * rtos::us, "pause_detector_clock") 
    {
        gnd.write(0);
        vcc.write(1);
        gnd.flush();
        vcc.flush();
    }
   /**
    * @brief adds listener to receive class
    * 
    * @param m the messagelistener you want to add to the array 
    */
    void addListener(MsgListener* m) {
        listeners[n_listeners] = m;
        n_listeners++;
    }
};

#endif