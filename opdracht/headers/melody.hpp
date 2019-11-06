/**
 * @file melody.hpp
 * @brief This file has been taken from the v2cpse1 repository so that the beeper will work 
 * @ref https://github.com/wovo/v2cpse1-examples/tree/master/practicum-ringtone
 */
#ifndef _MELODY_HPP
#define _MELODY_HPP

#include "note_player.hpp"

// an abstract melody

class melody {
public:
   virtual void play( note_player & p );
};

#endif
