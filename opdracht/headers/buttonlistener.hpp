/**
 * @file buttonlistener.hpp
 * @brief this file contains the button listener class
 * 
 */
#ifndef BUTTONLISTENER_HPP
#define BUTTONLISTENER_HPP

/**
 * @brief abstract button listner class for all listeners to inherit
 * 
 */
class Buttonlistener {
public:
    virtual void buttonPressed() = 0;
};

#endif // BUTTONLISTENER_HPP