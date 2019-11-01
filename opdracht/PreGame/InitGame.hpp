#ifndef INITGAME_HPP
#define INITGAME_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class InitGame : public rtos::task<>{
protected:

void main(){
    enum state_t = {Idle, RegTime, SetStartSignal};
    state = Idle;
    switch(state){
        case Idle:

        case RegTime:

        case SetStartSignal:
        
    }
}

public:

}

#endif // INITGAME_HPP