/**
 * @file keypadlistener.hpp
 * @brief this file contains the keypad lisntener pattern class
 * 
 */


#ifndef KEYPAD_LISTENER_HPP
#define KEYPAD_LISTENER_HPP 
/**
 * @brief This class is used by all classes that inherrit the keypad listener pattern
 * 
 */
class KeypadListener {
public:
    /**
     * @brief Virtual write function. Used to make functions in the subclass
     * 
     * @param k Const character to write
     */
    virtual void write(const char k) = 0;
};

#endif // KEYPAD_LISTENER_HPP