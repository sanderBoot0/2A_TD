#ifndef _NOTE_HPP
#define _NOTE_HPP

// ===========================================================================
//
// frequencies of standard notes
//
// ===========================================================================

class note {
public:

   // from https://www.seventhstring.com/resources/notefrequencies.html
   static const int A4  = 440;
   static const int A4s = 466;
   static const int B4  = 494;
   static const int C5  = 523;
   static const int C5s = 554;
   static const int D5  = 587;
   static const int D5s = 622;
   static const int E5  = 659;
   static const int F5  = 698;
   static const int F5s = 740;
   static const int G5  = 784;
   static const int G5s = 830;
   static const int A5  = 880;
   static const int A5s = 932;
   static const int B5  = 987;
   
   const int frequency;
    
   static const int dF = 1'000'000;  // full measure
   static const int dH = dF / 2;     // half measure
   static const int dQ = dF / 4;     // quarter measure
   
   const int duration;
};

#endif

