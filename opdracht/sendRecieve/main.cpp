#include "hwlib.hpp"
#include "rtos.hpp"
//#include "headers/send_classes.hpp"
#include "headers/receive_classes.hpp"
#include "headers/msg_decoder.hpp"
// #include "initgame.hpp"


int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "receive demo\n";

    namespace target = hwlib::target;

    auto data = target::pin_in(target::pins::d8);
    auto gnd  = target::pin_out(target::pins::d10);
    auto vcc  = target::pin_out(target::pins::d9);

    auto decoder = msg_decoder();
    auto receiver = receiver_controller(data, gnd, vcc, decoder);
    //auto sender = send_controller();
    // auto tester = Initgame(sender);
    
    (void) decoder;
    (void) receiver;
    //(void) sender;
    //(void) tester;

    rtos::run();
}
