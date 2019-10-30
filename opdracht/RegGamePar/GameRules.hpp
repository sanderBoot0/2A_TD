#include "hwlib.hpp"

class GameRules{

protected:
    uint8_t playernumber;
    int cooldown = firepower / 3 * 1000;
    int firepower;
    bool startsignal = false;
    int gametime;

public:

    uint8_t GetPlayerNumber(){
        return playernumber;
    }

    int GetFirepower(){
         return firepower;
    }

    bool GetStartSignal(){
        return startsignal;
    }

    int GetGameTime(){
        return gametime;
    }

    void SetPlayerNumber(uint8_t p){
        playernumber = p;
    }

    void SetFirePower(int f){
        firepower = f;
    }

    void SetStartSignal(){
        startsignal = !startsignal;
    }
    
    void SetGameTime(int g){
        gametime = g;
    }

};