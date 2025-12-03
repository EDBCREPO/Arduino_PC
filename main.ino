#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain() {

  ptr_t<uchar> pin  ( 3, 0 );
  ptr_t<uchar> PINS ({ 2,3,4,5 });

  for( auto &x: PINS ){ pinMode( x, OUTPUT ); }

  process::add( coroutine::add( COROUTINE(){
  coBegin while( true ) {

    if( pin[0] >= PINS.size() ){ coGoto(0); }
    if( pin[2] == 0 )          { coGoto(0); }

    digitalWrite( PINS[pin[0]], pin[1] );

  coNext; } coFinish
  })); 

  process::add( coroutine::add( COROUTINE(){
    pin[2] = 0;
  coBegin while( true ) {

    if( !Serial.available() ){ return 1; }
    
    console::scan("%u-%d",&pin[0],&pin[1]);
    pin[2] = 1; Serial.flush(); 

  coNext; } coFinish
  })); 

}