#include "nodepp/nodepp.h"
#include "nodepp/timer.h"

using namespace nodepp;

ptr_t<uchar> PINS ({ 2,3,4,5 });

void onMain() {

  ptr_t<uchar> pin ( 3, 0 );
  
  for( auto &x: PINS ) pinMode( x, OUTPUT );

  process::add([=](){
  coStart

    if( pin[0] >= PINS.size() ){ coGoto(0); }
    if( pin[2] == 0 )          { coGoto(0); }

    digitalWrite( PINS[pin[0]], pin[1] );

    coGoto(0);
  coStop
  });

  process::add([=](){
    pin[2] = 0;
  coStart

    if( !Serial.available() ){ coGoto(0); }
    
    console::scan("%u-%d",&pin[0],&pin[1]);
    pin[2] = 1; Serial.flush(); 
    
    coGoto(0);
  coStop
  });

}