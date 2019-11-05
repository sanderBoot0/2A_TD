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

# endif