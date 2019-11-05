#ifndef TRANSFER_HITS_HPP
#define TRANSFER_HITS_HPP

#include "rtos.hpp"
#include "gamerules.hpp"
#include "score.hpp"

// prioriteit 10
class TransferHits : public rtos::task<> {
private:
    GameRules &g;
    score &hits;

    void main() {
        enum states {WAIT_FOR_ENDING, WAIT_FOR_USB, TRANSFERING, DONE};
        states state = states::WAIT_FOR_ENDING;

        for(;;) {
            switch(state) {
                case states::WAIT_FOR_ENDING: {
                    hwlib::wait_ms(1000);
                    if(g.getFinishedSignal()) {
                        state = states::WAIT_FOR_USB;
                    }
                    break;
                }
                case states::WAIT_FOR_USB: {
                    char input;
                    hwlib::cin >> input;
                    if(input == 'D') {
                        state = states::TRANSFERING;
                        hwlib::cout << "Start transfering\n";
                    }
                    break;
                }
                case states::TRANSFERING: {
                    for(int i = 0;; i++) {
                        auto hit = hits.getHit(i);
                        if(hit.playerID == 0 && hit.damage == 0) {
                            hwlib::cout << "No hits\n'";
                            break;
                        } else {
                            hwlib::cout << hit.playerID << '\t' << hit.damage << '\n';
                        }
                    }
                }
                case states::DONE: {
                    hwlib::wait_ms(1'000'000'000);
                    break;
                }
            }
        }
    }

public:
    TransferHits(GameRules &g, score &hits):
        task(10, "Transfer hits task"),
        g( g ),
        hits( hits )
    {}

};

#endif // TRANSFER_HITS_HPP