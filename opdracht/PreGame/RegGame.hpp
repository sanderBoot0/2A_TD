#ifndef REGGAME_HPP
#define REGGAME_HPP
#include "rtos.hpp"
#include "GameRules.hpp"
#include "Keypad.hpp"

class regGame : public rtos::task<>{
private:
    GameRules g;

void main(){
    for(;;){
        enum regGameState {Idle, RegPlayer, RegFP, WaitInit, WaitRun};
        regGameState state = Idle;
        switch(state){
            case Idle:
                hwlib::cout << "Idle state" << hwlib::endl;
                //wait for A or B
                //Switch state accordingly
                break;
            case RegPlayer:
                hwlib::cout << "RegPlayer state" << hwlib::endl;
                //listen to keypad
                //if(k.read() == cijfer)
                //g.setPlayerNumber(keypadinput)
                //state = RegFP;
            case RegFP:
                hwlib::cout << "RegFP state" << hwlib::endl;
                //listen to keypad
                //if(k.read() == cijfer)
                //g.setFirePower(keypadinput)
                //state = WaitInit

            case WaitInit:
                hwlib::cout << "WaitInit state" << hwlib::endl;
                //Wait for IR input
                //If(IR Input == time)
                //setGameTime(IR Input)
                //state = WaitRun
            case WaitRun:
                hwlib::cout << "WaitRun state" << hwlib::endl;
                //Wait for IR Input
                //if(IR Input == start)
                //
        }
    }
    

}

public:
    regGame(hwlib::istream & keyinput):
        task("RegGame"),
        keyinput(keyinput)
    {}

    
    hwlib::istream & keyinput;
};

#endif 