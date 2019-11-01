#ifndef REGGAME_HPP
#define REGGAME_HPP

#include "rtos.hpp"
#include "GameRules.hpp"
// #include "keypadclass.hpp"

bool isNumber(char c)
{
    return bool((c >= '0') && (c <= '9'));
}

class regGame : public rtos::task<>
{
private:
    rtos::channel<char, 16> keypadchannel;

    GameRules g;
    // keypadclass keypadinstance;

    void main()
    {
        enum regGameState
        {
            Idle,
            RegPlayer,
            RegFP,
            WaitGameTime,
            WaitRun
        };
        enum substates
        {
            waitforletter,
            waitfornumber,
            registernumber
        };
        substates regplayerstate = substates::waitforletter;
        substates regfirepowerstate = substates::waitforletter;
        
        regGameState state = RegPlayer;
        
        hwlib::cout << "Type A to Continue, " << '\n';
        for (;;)
        {
            // char tempread = keypadchannel.read();

            switch (state)
            {
            case Idle:
                hwlib::cout << "Idle state" << hwlib::endl;
                break;
            case RegPlayer:
                switch (regplayerstate)
                {
                case waitforletter:
                    wait(keypadchannel);

                    if (keypadchannel.read() == 'A')
                    {
                        hwlib::cout << "A pressed, " << '\n'
                                    << "Type Number" << '\n';
                        regplayerstate = waitfornumber;
                    }
                    break;

                case waitfornumber:
                    wait(keypadchannel);

                    auto temp = keypadchannel.read();

                    if (isNumber(temp))
                    {
                        regplayerstate = registernumber;
                        hwlib::cout << "your player number is: " << temp << '\n';
                    }
                    else
                    {
                        //Vraag nieuw nummer
                        hwlib::cout << "not a number" << '\n';
                    }
                    break;
                case registernumber:
                    hwlib::cout << "Saving player number" << '\n';
                    g.setPlayerNumber(tempread - 48);
                    state = RegFP;

                    break;
                }

                //listen to keypad

                //if(k.read() == cijfer)
                //g.setPlayerNumber(keypadinput)
                //state = RegFP;
                // int i = g.getPlayerNumber;
                // hwlib::cout << "playernumber is " << i << '\n';
                break;
            case RegFP:
                switch (regfirepowerstate)
                {
                case waitforletter:
                    hwlib::cout << "Type B to continue" << '\n';
                    if (tempread == 'B')
                    {
                        hwlib::cout << "B pressed, " << '\n';
                        regfirepowerstate = waitfornumber;
                    }
                    break;
                case waitfornumber:
                    hwlib::cout << "Type a number" << '\n';
                    if (isNumber(tempread))
                    {
                        regfirepowerstate = registernumber;
                        hwlib::cout << "your fire power is: " << tempread << '\n';
                    }
                    else
                    {
                        hwlib::cout << "wrong number" << '\n';
                        //Vraag nieuw nummer
                    }
                    break;
                case registernumber:
                    g.setFirePower((tempread - 48));

                    hwlib::cout << "your fire power is: " << tempread - 48 << '\n';

                    state = regGameState::WaitGameTime;
                    break;
                }

                break;
            case WaitGameTime:
                hwlib::cout << "WaitGameTime state" << hwlib::endl;
                //Wait for IR input
                //If(IR Input == time)
                //setGameTime(IR Input)
                //state = WaitRun
                break;
            case WaitRun:
                hwlib::cout << "WaitRun state" << hwlib::endl;
                //Wait for IR Input
                //if(IR Input == start)
                //
                break;
            }
        }
    }

    // void read_channel(){
    //     auto msg = keypadinstance.keypadchannel.read();
    //     hwlib::cout << msg << hwlib::endl;

    // }

public:
    regGame() : task(1, "RegGame"),
                keypadchannel(this, "keypadchannel")
    // keypadinstance(keypadconstructor)
    {
    }

    void write(const char k)
    {
        keypadchannel.write(k);
    }
};

#endif
