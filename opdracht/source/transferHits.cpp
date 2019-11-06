/**
 * @file transferHits.cpp
 * @brief The source file of the transferHits class which contains the defined functions
 */

#include "../headers/transferHits.hpp"

void TransferHits::main(){
    enum states {WAIT_FOR_ENDING, WAIT_FOR_USB, TRANSFERING};
    states state = states::WAIT_FOR_ENDING;

    for(;;) {
        switch(state) {

            // Wait for the gamover flag to be set, then the game has finished.
            case states::WAIT_FOR_ENDING: {
                wait(gameOver);
                state = states::WAIT_FOR_USB;

                break;
            }

            // Wait for the person to press D on the computer
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

            // Get all the hits, and cout them. Then go back to the beginning.
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

                hwlib::cout << "Done transfering, goodbye!\n";
                
                state = states::WAIT_FOR_ENDING;
                break;
            }
        }
    }
}

