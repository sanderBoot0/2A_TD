/*

PROJECT Themaopdracht DEVICES (2A_TD)
NAME :  
Date :  November 2019

AUTHORS:
    Mick Bos
    Tobias van den Hoogen
    Scott Timmermans
    Sander Boot

*/

#include "../headers/gamerules.hpp"
#include "../headers/reg_game.hpp"
#include "../headers/keypadclass.hpp"

#include "../headers/time_entity.hpp"
#include "../headers/displaycontroller.hpp"

#include "../headers/receive_classes.hpp"
#include "../headers/send_classes.hpp"

#include "../headers/run_game.hpp"

#include "../headers/gamerules.hpp"

#include "../headers/button.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"


int main(){
        
// receiver tester main  ==============================================
    namespace target = hwlib::target;

// // Ir-Receiver pins
    auto data = target::pin_in(target::pins::d8);
    auto gnd  = target::pin_out(target::pins::d10);
    auto vcc  = target::pin_out(target::pins::d9);

// // Display I2C pins
//     auto scl = target::pin_oc( target::pins::scl );
//     auto sda = target::pin_oc( target::pins::sda );
//     auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

// // Declaration of Display and font for displayController class
//     auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 
//     auto font = hwlib::font_default_16x16();

// reciever tester main ================================================

// keypad Pins
    auto out0 = target::pin_oc( target::pins::a0 );
    auto out1 = target::pin_oc( target::pins::a1 );
    auto out2 = target::pin_oc( target::pins::a2 );
    auto out3 = target::pin_oc( target::pins::a3 );

    auto in0  = target::pin_in( target::pins::a4 );
    auto in1  = target::pin_in( target::pins::a5 );
    auto in2  = target::pin_in( target::pins::a6 );
    auto in3  = target::pin_in( target::pins::a7 );
    
// pin list of in's and out's
    auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
    auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
    auto matrix = hwlib::matrix_of_switches( out_port, in_port );

    auto button = target::pin_in( target::pins::d6 );

    auto message = "123A456B789C*0#D";
    auto keypadaanmaak = hwlib::keypad<16>(matrix, message);

    auto game_par = GameRules();

    auto regGame1 = RegGame(game_par);
    auto keypad = Keypadclass(keypadaanmaak, regGame1);

    auto buttonCtrl = Button(button);

    auto receiver = Receiver_controller(data, gnd, vcc/*, printer*/);
    auto sender = send_controller();

    // auto tijd = time(11, 11);
    // auto displayCtrl = displayController(oled, font);

    auto runCtrl = Rungame(sender, game_par);

    buttonCtrl.addListener(&runCtrl);


    (void) keypad;
    (void) regGame1;
    
    // (void) displayCtrl;
    (void) receiver;
    
    (void) sender;

    (void) runCtrl;

    (void) buttonCtrl;
    
    // wait for the PC console to start
    hwlib::wait_ms( 500 );

    rtos::run();
    
}
