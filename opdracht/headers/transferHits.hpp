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

    void main() {
        enum states {WAIT_FOR_ENDING, WAIT_FOR_USB, TRANSFERING, DONE};
        states state = states::WAIT_FOR_ENDING;

        for(;;) {
            switch(state) {
                case states::WAIT_FOR_ENDING: {
                    wait(gameOver);
                    state = states::WAIT_FOR_USB;

                    break;
                }
                case states::WAIT_FOR_USB: {
                    hwlib::cout << "Press 'D', to start transfer";
                    char input;
                    hwlib::cin >> input;
                    if(input == 'D') {
                        state = states::TRANSFERING;
                        hwlib::cout << "Start transfering\n";
                    }
                    break;
                }
                case states::TRANSFERING: {
                    int health = 100;
                    for(int i = 0;; i++) {
                        auto hit = hits.getHit(i);
                        if(hit.playerID == 0 && hit.damage == 0) {
                            break;
                        } else {
                            health -= hit.damage;
                            if(health < 0) { health = 0; }
                            hwlib::cout << "Player: " << hit.playerID << "\tHit damage: " << hit.damage << "\tRemaining health: " << health << '\n';
                        }
                    }
                    if(health == 100) {
                        hwlib::cout << "No hits!\nWell Played!\n";
                    }
                }
                case states::DONE: {
                    state = states::WAIT_FOR_ENDING;
                    break;
                }
            }
        }
    }

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