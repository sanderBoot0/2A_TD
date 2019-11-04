#ifndef _MELODY_HPP
#define _MELODY_HPP

#include "note_player.hpp"

// an abstract melody

class melody {
public:
   virtual void play( note_player & p );
};

#endif
