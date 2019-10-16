#include "hwlib.hpp"
#include "rtos.hpp"
#include "send_classes.hpp"
#include "receive_classes.hpp"


int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "receive demo\n";

    namespace target = hwlib::target;

    auto data = target::pin_in(target::pins::d8);
    auto gnd  = target::pin_out(target::pins::d10);
    auto vcc  = target::pin_out(target::pins::d9);

    auto receiver = receiver_controller(data, gnd, vcc);
    auto sender = send_controller();
    rtos::run();
    return 0;
}
