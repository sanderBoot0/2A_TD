#include "hwlib.hpp"
#include "rtos.hpp"
#include "../../headers/receive_classes.hpp"
// #include "../../sendReceive/headers/msg_decoder.hpp"
#include "../test_receiver.hpp"


int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "receive demo\n";

    namespace target = hwlib::target;

    auto data = target::pin_in(target::pins::d8);
    auto gnd  = target::pin_out(target::pins::d10);
    auto vcc  = target::pin_out(target::pins::d9);

    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    auto font    = hwlib::font_default_16x16();
    auto display = hwlib::terminal_from( oled, font );

    auto printer = Test_receiver(display);
    // auto decoder = msg_decoder(printer);
    auto receiver = Receiver_controller(data, gnd, vcc, printer);
    
    (void) printer;
    // (void) decoder;
    (void) receiver;

    rtos::run();
}
