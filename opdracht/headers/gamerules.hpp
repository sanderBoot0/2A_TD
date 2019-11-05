/**
 * @file gamerules.hpp
 * @brief This file contains the class GameRules
 * 
 */

#ifndef GAMERULES_HPP
#define GAMERULES_HPP

#include "hwlib.hpp"

/**
 * @brief Class that stores values of the player and the game itself
 * 
 */
class GameRules{

protected:
    int playernumber;
    int firepower;
    bool startsignal = false;
    bool gameFinished = false;
    int gametime;

public:

    /**
     * @brief Get the Player Number value
     * 
     * @return int 
     */
    int getPlayerNumber(){
        return playernumber;
    }

    /**
     * @brief Get the Firepower value
     * 
     * @return int 
     */
    int getFirepower(){
         return firepower;
    }

    /**
     * @brief Get the Start Signal value
     * 
     * @return bool
     */
    bool getStartSignal(){
        return startsignal;
    }

    /**
     * @brief Get the Finished Signal value
     * 
     * @return bool
     */
    bool getFinishedSignal() {
        return gameFinished;
    }

    /**
     * @brief Get the Game Time value
     * 
     * @return int 
     */
    int getGameTime(){
        return gametime;
    }

    /**
     * @brief Set the Player Number value
     * 
     * @param p 
     */
    void setPlayerNumber(int p){
        playernumber = p;
    }

    /**
     * @brief Set the Fire Power value
     * 
     * @param f 
     */
    void setFirePower(int f){
        firepower = f;
    }

    /**
     * @brief Set the Start Signal value
     * 
     */
    void setStartSignal(){
        startsignal = !startsignal;
    }

    /**
     * @brief Set the Finished Signal value
     * 
     */
    void setFinishedSignal() {
        gameFinished = true;
    }
    
    /**
     * @brief Set the Game Time value
     * 
     * @param g 
     */
    void setGameTime(int g){
        gametime = g;
    }

};

#endif
