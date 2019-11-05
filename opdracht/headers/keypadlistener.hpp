#ifndef KEYPAD_LISTENER_HPP
#define KEYPAD_LISTENER_HPP 

class KeypadListener {
public:
    virtual void write(const char k) = 0;
};

#endif // KEYPAD_LISTENER_HPP