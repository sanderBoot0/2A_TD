#ifndef PAUSE_DETECTOR_HPP
#define PAUSE_DETECTOR_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "pause_listener.hpp"

class pause_detector : public rtos::task<> {
private:
	rtos::clock pause_detector_clock;
	hwlib::pin_in & irp;
	pause_listener & listener;
public:
	pause_detector( const char * name, hwlib::pin_in & irp, pause_listener & listener ):
		task( 0, name ),
		pause_detector_clock( this, 50 * rtos::us, "pause_detector_clock" ),
		irp( irp ),
		listener( listener )
	{}
	
	void main() override {
		//enum states { idle, signal };
		//states state = states::idle;
		int pause_length = 0;
		//int i = 0;
		int begin_time;
		bool signal_detected = false;

		//uint16_t signal = 0;
		//int i = 0;
		for(;;){
			// switch( state ) {
			// 	case states::idle: {
			// 		wait( pause_detector_clock );
			// 		irp.refresh();
			// 		if( irp.read() ) {
			// 			// hwlib::cout << "I\n";
			// 			pause_length += 50;
			// 		}
			// 		else{
			// 			listener.pause_detected( pause_length );
			// 			//hwlib::cout << pause_length << "\n";
			// 			state = states::signal;
			// 		}
			// 		break;
			// 	}
				
			// 	case states::signal: {
			// 		irp.refresh();
			// 		if( !irp.read() ) {
			// 			hwlib::cout << "S\t" << pause_length << '\n';

			// 			pause_length = 0;
			// 			state = states::idle;
			// 		}
			// 		break;
			// 	}
			// }


			// int begin_time = hwlib::now_us();
			// while(irp.read() == 1) {
			// 	// wait( pause_detector_clock );
			// 	irp.refresh();
			// }
			// pause_length = hwlib::now_us() - begin_time;
			// hwlib::cout << "S\t" << pause_length << '\n';


			// hwlib::cout << (int) irp.read();
			// wait(pause_detector_clock);
			if(irp.read() == 1) {
				if(!signal_detected ) {
					signal_detected = true;
					begin_time = hwlib::now_us();				
				
				}
			} else {
				if(signal_detected) {
					// signal = (signal << 1) & ~(0x1);
					pause_length = hwlib::now_us() - begin_time;
					listener.pause_detected( pause_length );
					// signal |= (0x500 & pause_length) && 0x500;
					// i = (i++) % 16;

					// if(i == 0)
					// 	hwlib::cout << "S\t" << hwlib::bin << signal << '\n';
				}
				signal_detected = false;
			}
		}
	}
};

#endif // PAUSE_DETECTOR_HPP