#include "../headers/receive_classes.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

uint64_t receiver_controller::check_pause() {
    uint64_t begin_time;

    while (!data.read()) {
        begin_time = hwlib::now_us();
    }

    while (data.read()) {
        wait(pause_detector_clock);
    }

    uint64_t pause_length = hwlib::now_us() - begin_time;
    // hwlib::cout << pause_length << '\n';
    return pause_length;
}