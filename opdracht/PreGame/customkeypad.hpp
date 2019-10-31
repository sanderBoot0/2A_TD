#ifndef CUSTOMKEYPAD_HPP
#define CUSTOMKEYPAD_HPP

#include "hwlib.hpp"

// template<typename T, typename N>
// class customkeypad : public hwlib::keypad{
// private:
//     hwlib::target::pin_oc out0 = hwlib::target::pin_oc( hwlib::target::pins::a0 );
//     hwlib::target::pin_oc out1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
//     hwlib::target::pin_oc out2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
//     hwlib::target::pin_oc out3 = hwlib::target::pin_oc( hwlib::target::pins::a3 );

//     hwlib::target::pin_in in0  = hwlib::target::pin_in( hwlib::target::pins::a4 );
//     hwlib::target::pin_in in1  = hwlib::target::pin_in( hwlib::target::pins::a5 );
//     hwlib::target::pin_in in2  = hwlib::target::pin_in( hwlib::target::pins::a6 );
//     hwlib::target::pin_in in3  = hwlib::target::pin_in( hwlib::target::pins::a7 );

//     hwlib::port_oc out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
//     hwlib::port_in in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
//     hwlib::matrix_of_switches matrix   = hwlib::matrix_of_switches( out_port, in_port );

// public:
//     customkeypad():
//         hwlib::keypad(matrix, "123A456B789C*0#D")
//     {};
// };

#endif //CUSTOMKEYPAD_HPP