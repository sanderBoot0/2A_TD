#ifndef GAMERULES_HPP
#define GAMERULES_HPP

#include "hwlib.hpp"

class GameRules{

protected:
    uint8_t playernumber;
    int cooldown = firepower / 3 * 1000;
    int firepower;
    bool startsignal = false;
    int gametime;

public:

    uint8_t getPlayerNumber(){
        return playernumber;
    }

    int getFirepower(){
         return firepower;
    }

    bool getStartSignal(){
        return startsignal;
    }

    int getGameTime(){
        return gametime;
    }

    void setPlayerNumber(uint8_t p){
        playernumber = p;
    }

    void setFirePower(int f){
        firepower = f;
    }

    void setStartSignal(){
        startsignal = !startsignal;
    }
    
    void setGameTime(int g){
        gametime = g;
    }

};

#endif