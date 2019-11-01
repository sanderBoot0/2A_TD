#include "GameRules.hpp"
#include "RegGame.hpp"
#include "rtos.hpp"

#include "keypadclass.hpp"

int main(){
        

    auto out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
    auto out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
    auto out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
    auto out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

    auto in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
    auto in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
    auto in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
    auto in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );
    
    auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    auto matrix = hwlib::matrix_of_switches( out_port, in_port );
    auto message = "123A456B789C*0#D";

    auto keypadaanmaak = hwlib::keypad<16>(matrix, message);

    regGame regGame1;

    keypadclass keypad(keypadaanmaak, regGame1);


    (void) regGame1;
    (void) keypad;






   // kill the watchdog
    // WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
    hwlib::wait_ms( 500 );

    // regGame(keypad);


    //keypadclass test(keypadaanmaak);
    rtos::run();
    
}
