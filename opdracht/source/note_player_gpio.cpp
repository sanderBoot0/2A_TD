/**
 * @file note_player_gpio.cpp
 * @brief This file has been taken from the v2cpse1 repository so that the beeper will work 
 * @ref https://github.com/wovo/v2cpse1-examples/tree/master/practicum-ringtone
 */

#include "hwlib.hpp"
#include "../headers/note_player_gpio.hpp"

  
void note_player_gpio::play( const note & n ){
   if( n.frequency == 0 ){
      hwlib::wait_us( n.duration );
      
   } else {
      auto half_period = 1'000'000 / ( 2 * n.frequency );    
      auto end = hwlib::now_us() + n.duration;
      do { 
         lsp.write( 1 );
         lsp.flush();
         hwlib::wait_us( half_period );
         lsp.write( 0 );
         lsp.flush();
         hwlib::wait_us( half_period );
      } while ( end > hwlib::now_us() );
   }     
}
