#ifndef TRANSFER_HITS_HPP
#define TRANSFER_HITS_HPP

#include "rtos.hpp"
#include "gamerules.hpp"
#include "score.hpp"

// prioriteit 10
class TransferHits : public rtos::task<> {
private:
    rtos::flag gameOver;
    score &hits;

    void main(); 

public:
    TransferHits(score &hits):
        task(10, "Transfer hits task"),
        gameOver(this, "Start transfer flag"),
        hits( hits )
    {}

    void startTransfer() {
        gameOver.set();
    }
};

#endif // TRANSFER_HITS_HPP