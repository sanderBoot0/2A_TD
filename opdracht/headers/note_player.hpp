/**
 * @file note_player.hpp
 * @brief This file has been taken from the v2cpse1 repository so that the beeper will work 
 * @ref https://github.com/wovo/v2cpse1-examples/tree/master/practicum-ringtone
 */

#ifndef _NOTE_PLAYER_HPP
#define _NOTE_PLAYER_HPP

#include "note.hpp"

// ===========================================================================
//
// abstract interface for a note player
//
// ===========================================================================

class note_player {
public:   
   virtual void play( const note & n ) = 0;
};

#endif