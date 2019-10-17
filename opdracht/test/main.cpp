#include "hwlib.hpp"
// #include "rtos.hpp"

int check_pause(hwlib::pin_in & irp) {
    int begin_time;
    
    while(!irp.read()) {
        begin_time = hwlib::now_us();
    }
    
    while(irp.read()) {}

    int pause_length = hwlib::now_us() - begin_time;

    return pause_length;
}

int main() { 
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms(2000);

    namespace target = hwlib::target;

	auto ir_receiver_pin = target::pin_in( target::pins::d8 );

    auto gnd  = target::pin_out(target::pins::d10);
    auto vcc  = target::pin_out(target::pins::d9);

	gnd.write(0);
	vcc.write(1);
	gnd.flush();
	vcc.flush();

    // uint16_t message = 0;

    uint16_t pauses[32];

    for(;;) {
        while(ir_receiver_pin.read()) {}

        for(int i = 0; i < 32; i++) {
            pauses[i] = check_pause(ir_receiver_pin);
        }
        for(int i = 0; i < 32; i++) {
            hwlib::cout << pauses[i] << ' ';
        }
        hwlib::cout << '\n';
    }
}