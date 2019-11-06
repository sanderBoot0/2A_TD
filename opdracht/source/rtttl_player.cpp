/**
 * @file rtttl_player.cpp
 * @brief This file has been taken from the v2cpse1 repository so that the beeper will work 
 * @ref https://github.com/wovo/v2cpse1-examples/tree/master/practicum-ringtone
 */

#ifdef BMPTK_TARGET
   #include "hwlib.hpp"
   #define COUT hwlib::cout
#else
   #include <iostream>
   #define HWLIB_TRACE std::cerr << "\n" << std::flush
   #define COUT std::cerr
#endif
#include "../headers/rtttl_player.hpp"

bool is_digit( char c ){ return ( c >= '0' ) && ( c <= '9' ); }
bool is_lowercase( char c ){ return ( c >= 'a' ) && ( c <= 'z' ); }
int frequencies[] = { 440'000, 493'880, 261'630, 293'660, 329'630, 349'230, 392'000 };

void rtttl_play( note_player & lsp, const char *s ){
   int def_duration = 4, def_octave = 6, beat = 100, value;
   int duration, octave, frequency;
   int state = 0;
   char def;
   bool dot;
   for( const char * p = s; state >= 0; p++ ){
      const char c = *p;

      switch(state ){
             
         // title 
         case 0:
            // ignore title (chars up until the first ':')
            if( c == ':' ){
               state = 1;
            } 
            break;
               
          // defaults  
          case 1:
               // end of the defaults, start of the melody                
            if( c == ':' ){                
               state = 3;
               
            // start of a default (d,o,b)               
            } if( is_lowercase( c )){
               def = c;
               state = 2;
               
            // unrecognised default letter             
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            } 
            break;   

         // defaults, letter has been stored in def
         case 2:
            // start the value
            if( c == '=' ){
               value = 0;
               
            // digit: update the value
            } else if( is_digit( c )){
               value = ( 10 * value ) + ( c - '0' );
               
            // end of the value: update the default   
            } else if(( c == ':' ) || ( c == ',' )) {
               if( def == 'o'){
                  def_octave = value;
               } else if( def == 'd' ){
                  def_duration = value;
               } else if( def == 'b' ){
                  beat = value;
               } else {
                  HWLIB_TRACE << "def=[" << def << "]";
               }   
               state = ( c == ':' ) ? 3 : 1;
               
            // unrecognised letter in the value of a default
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }
            break;
            
         // note start, set defaults
         case 3:  
            duration = def_duration;
            octave = def_octave;
            state = 4;
            dot = 0;
            
            // ignore a space before a note
            if( c == ' ' ){
                break;
            }
            
            // deliberate fallthrough!!
               
         // duration 1  
         case 4:   
            if( is_digit( c )){
               duration = c -'0';
               state = 5;
               break;
            }            
            // deliberate fallthrough!!
            
         // duration 2 
         case 5:   
            if( is_digit( c )){
               duration = ( duration * 10 ) + ( c -'0' );
               state = 6;
               break;
            }            
            // deliberate fallthrough!!
               
         // note letter   
         case 6:   
            // select the note, or a pause
            if( is_lowercase( c )){
               if( c == 'p' ){
                   frequency = 0;
               } else {
                  frequency = frequencies[ c - 'a' ]; 
               }   
               
            // unrecognised letter in note specification               
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }   
            state = 7;
            break;
               
         // optional #   
         case 7:   
            if( c == '#' ){
               frequency = 10595LL * frequency / 10000;
               state = 8;
               break;
            }
            // deliberate fallthrough!!

         // optional .
         case 8:
            if( c == '.' ){
               dot = 1;
               state = 9;
               break;
            }            
            // deliberate fallthrough!!

         case 9:
            if( is_digit( c )){
               octave = c - '0';
               state = 10;
               break;
            }        
            // deliberate fallthrough!!
               
         case 10:   
            if( ( c == ',' ) || ( c == '\0') ){
               while( octave > 4 ){ --octave; frequency *= 2; }
               int note_duration = ( 4 * 60'000'000 ) / ( duration * beat );
               if( dot ){
                  duration += duration / 2;
               }

               lsp.play( note{ frequency / 1000, note_duration } ); 
			   
               state = 3;

            // unrecognised character in or after note 
            } else {
               HWLIB_TRACE << "c=[" << c << "]";
            }
            if( c == '\0' ){
               state = -1;
            }
            break;            
      }         
   }
}   
