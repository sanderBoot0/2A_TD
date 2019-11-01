#ifndef TIME_ENTITY_HPP
#define TIME_ENTITY_HPP

#include "hwlib.hpp"

class time {
private:
    unsigned int seconds;

public:
    time() {
        seconds = 0;
    }

    time(unsigned int p_minutes, unsigned int p_seconds) {
        seconds = (p_minutes * 60) + p_seconds;
    }

    unsigned int getMinutes() {
        return seconds / 60;
    }

    unsigned int getSeconds() {
        return seconds % 60;
    }

    void set_time(unsigned int p_minutes, unsigned int p_seconds) {
        seconds = (p_minutes * 60) + p_seconds;
    }

    void set_relative_time(unsigned int p_minutes, unsigned int p_seconds) {
        seconds += (p_minutes * 60) + p_seconds;
    }
};

#endif // TIME_ENTITY_HPP