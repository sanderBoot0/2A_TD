#include "hwlib.hpp"
#include "rtos.hpp"

#include "headers/displayController.hpp"
#include "headers/time_entity.hpp"

int main(void) {
    // wait for the PC console to start
    hwlib::wait_ms(500);

    hwlib::cout << "display demo\n";

    namespace target = hwlib::target;

    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
        
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
        
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    auto font = hwlib::font_default_16x16();

    auto tijd = time(11, 11);
    auto displayCtrl = displayController(oled, font);


    (void) displayCtrl;

    rtos::run();
}
