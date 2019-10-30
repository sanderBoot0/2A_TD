#ifndef MSG_LOGGER_HPP
#define MSG_LOGGER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "msg_listener.hpp"

class msg_logger : public rtos::task<>, public msg_listener {
private:
	rtos::channel<ir_msg, 1024> messages;

public:
    msg_logger( const char * name ):
        task( 3, name ),
        messages( this, "messages" )
    {}

    virtual void msg_received( const ir_msg & msg ) override {
        messages.write( msg );
    };

	void main() override {
        enum states {idle, show_message};
        states state = states::idle;
		for(;;){
			switch(state) {
				case states::idle: {
					wait(messages);
					state = states::show_message;
				}
				
				case states::show_message: {
					auto p = messages.read();
					hwlib::wait_ms( 50 );
					hwlib::cout << p.player << "\n" << p.data << "\n";
					state = states::idle;
				}
			}
		}
	}
};

#endif // MSG_LOGGER_HPP