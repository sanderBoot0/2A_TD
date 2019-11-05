#ifndef GAMERULES_HPP
#define GAMERULES_HPP

#include "hwlib.hpp"

class GameRules{

protected:
    int playernumber;
    int cooldown = firepower / 3 * 1000;
    int firepower;
    bool startsignal = false;
    bool gameFinished = false;
    int gametime;

public:

    int getPlayerNumber(){
        return playernumber;
    }

    int getFirepower(){
         return firepower;
    }

    bool getStartSignal(){
        return startsignal;
    }

    bool getFinishedSignal() {
        return gameFinished;
    }

    int getGameTime(){
        return gametime;
    }

    void setPlayerNumber(int p){
        playernumber = p;
    }

    void setFirePower(int f){
        firepower = f;
    }

    void setStartSignal(){
        startsignal = !startsignal;
    }

    void setFinishedSignal() {
        gameFinished = true;
    }
    
    void setGameTime(int g){
        gametime = g;
    }

};

#endif
