/**
 * @file transferHits.hpp
 * @brief This file contains the TranferHits class which control the data to the serial 

 */

#ifndef TRANSFER_HITS_HPP
#define TRANSFER_HITS_HPP

#include "rtos.hpp"
#include "gamerules.hpp"
#include "score.hpp"

/**
 * @brief thhs class is used to tranfer the hit data to the computer via serial
 * 
 */
class TransferHits : public rtos::task<> {
private:
    rtos::flag gameOver;
    score &hits;

    void main(); 

public:
/**
 * @brief Construct a new Transfer Hits object
 * 
 * @param hits 
 */
    TransferHits(score &hits):
        task(10, "Transfer hits task"),
        gameOver(this, "Start transfer flag"),
        hits( hits )
    {}
/**
 * @brief starts the transfer of the hit data
 * 
 */
    void startTransfer() {
        gameOver.set();
    }
};

#endif // TRANSFER_HITS_HPP