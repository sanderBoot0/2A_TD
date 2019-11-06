/**
 * @file note_player_gpio.hpp
 * @brief This file has been taken from the v2cpse1 repository so that the beeper will work 
 * @ref https://github.com/wovo/v2cpse1-examples/tree/master/practicum-ringtone
 */

#ifndef _NOTE_PLAYER_GPIO_HPP
#define _NOTE_PLAYER_GPIO_HPP

#include "hwlib.hpp"
#include "note_player.hpp"

// ===========================================================================
//
// simple note player for a speaker connected to a GPIO pin
//
// ===========================================================================

class note_player_gpio : public note_player {
private:   
   hwlib::pin_out & lsp;
public: 
   note_player_gpio( hwlib::pin_out & lsp ):
      lsp( lsp )
   {}
   
   void play( const note & n ) override;
};

#endif
