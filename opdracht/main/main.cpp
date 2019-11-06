/**
 * @file main.cpp 
 * @brief the main file 
 * 
 */

/*

PROJECT Themaopdracht DEVICES (2A_TD)
NAME :  
Date :  November 2019

AUTHORS:
    Mick Bos
    Tobias van den Hoogen
    Scott Timmermans
    Sander Boot

*/

#include "../headers/gamerules.hpp"
#include "../headers/reg_game.hpp"
#include "../headers/initgame.hpp"
#include "../headers/keypadclass.hpp"

#include "../headers/displaycontroller.hpp"

#include "../headers/receive_classes.hpp"
#include "../headers/send_classes.hpp"

#include "../headers/run_game.hpp"

#include "../headers/button.hpp"

#include "../headers/note_player_gpio.hpp"

#include "../headers/score.hpp"

#include "../headers/beeperCtrl.hpp"

#include "../headers/transferHits.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

int main(){
    namespace target = hwlib::target;
    
    //Declare IR Receiver 
    auto receiver = Receiver_controller();

    //Declare IR Sender 
    auto sender = send_controller();

    //Declare Display 
    auto displayCtrl = DisplayController();

    //Declare Control Objects en entities 
    auto game_par = GameRules();
    auto regGame1 = RegGame(game_par, displayCtrl);
    auto initGameCtrl = Initgame(sender, displayCtrl);

    //Declare Keypad 
    auto keypad = Keypadclass();
    
    //Declare Speaker 
    auto beeper = Beeper();

    auto button = target::pin_in( target::pins::d6 );
    auto buttonCtrl = Button(button);

    auto score_hit_entity = score();

    auto transferHitsCtrl = TransferHits(score_hit_entity);

    auto runCtrl = Rungame(sender, game_par, beeper, displayCtrl, score_hit_entity, transferHitsCtrl);

    //Declare Listeners

    keypad.addListener(&initGameCtrl);
    keypad.addListener(&regGame1);

    buttonCtrl.addListener(&runCtrl);

    receiver.addListener(&runCtrl);
    receiver.addListener(&regGame1);

    // Voids to cancel the unused errors because of RTOS


    (void) receiver;
    (void) sender;

    (void) buttonCtrl;
    (void) beeper;
    (void) displayCtrl;
    (void) keypad;

    (void) initGameCtrl;
    (void) regGame1;
    
    (void) runCtrl;

    (void) transferHitsCtrl;
    
    // wait for the PC console to start
    hwlib::wait_ms( 500 );

    //run all task 
    rtos::run();
    
}
