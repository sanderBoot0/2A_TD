#include "hwlib.hpp"
#include "rtos.hpp"
#include "../../sendReceive/headers/send_classes.hpp"
#include "../../sendReceive/headers/test_sender.hpp"


int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "send demo\n";

    namespace target = hwlib::target;

    auto sender = send_controller();
    auto test_class = test_sender(sender);
    
    (void) sender;
    (void) test_class;

    rtos::run();
}