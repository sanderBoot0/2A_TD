#include "../headers/displaycontroller.hpp"

void DisplayController::showGameInfo() {
    display << '\f';

    gameinfo poolInput = gameinfopool.read();

    unsigned int minutes = poolInput.seconds / 60;
    unsigned int seconds = poolInput.seconds % 60;
    unsigned int score   = poolInput.score;
    if(minutes < 10) 
        display << '0';

    display << minutes << ':';

    if(seconds < 10) 
        display << '0';

    display << seconds << "\n   " << score;
    flushScreen();
}

void DisplayController::showCommand(const char *p) {
    display << '\f' ;

    do{
        display << *p++;

    }while(*p != '\0');

    flushScreen();
}

void DisplayController::addChar(const char c){
    display << c;
}

void DisplayController::flushScreen(){
    display << hwlib::flush;
}

void DisplayController::clearScreen(){
    display << '\f';
    flushScreen();
}

    void DisplayController::writeCmdPool(const char* cmd){
        commandpool.write(cmd);
        commandflag.set();
    }

    void DisplayController::writeGameInfoPool(int seconds, int score){
        gameinfopool.write(gameinfo(score,seconds));
        gameinfoflag.set();
    }
