/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_WINDOWS_SERIAL
#define NODEPP_WINDOWS_SERIAL

/*────────────────────────────────────────────────────────────────────────────*/

#include <windows.h>

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class serial_t : public file_t {
protected:

	int GETBAUD( uint baud ) const noexcept {
		switch( baud ){
			case 110:     return CBR_110;    break;
			case 300:     return CBR_300;    break;
			case 600:     return CBR_600;    break;
			case 1200:    return CBR_1200;   break;
			case 2400:    return CBR_2400;   break;
			case 4800:    return CBR_4800;   break;
			case 9600:    return CBR_9600;   break;
			case 19200:   return CBR_19200;  break;
			case 38400:   return CBR_38400;  break;
			case 57600:   return CBR_57600;  break;
			case 115200:  return CBR_115200; break;
			default:      return CBR_9600;   break;
		}
	}

	void set_baud_rate( const HANDLE& fd, uint baud ) const noexcept {
		DCB dcbSerialParams; memset( &dcbSerialParams, 0, sizeof(DCB) );

		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
		dcbSerialParams.BaudRate  = GETBAUD(baud);
		dcbSerialParams.ByteSize  = 8;
		dcbSerialParams.Parity    = NOPARITY;
		dcbSerialParams.StopBits  = ONESTOPBIT;

		SetCommState( fd, &dcbSerialParams );
	}

public:

	serial_t( const string_t& path, uint baud=0, const ulong& _size=CHUNK_SIZE )
	: file_t( path, nullptr ){ 
		auto self = type::bind(this); set_baud_rate( this->get_fd(), baud );
		process::add([=](){ this->onOpen.emit(); return -1; });
	}
	
	serial_t() noexcept : file_t() {}

};}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace serial {

    template <class... T> 
	promise_t<serial_t,except_t> connect( const T&... args ){ 
		return promise_t<serial_t,except_t>([=]( function_t<void,serial_t> res, function_t<void,except_t> rej ){
		try  { serial_t socket( args... ); res( socket ); } 
		catch( except_t err ) { rej( err ); } }); 
	}

    template <class... T>
    serial_t await( const T&... args ){ return serial_t( args... ); }

	inline array_t<string_t> get_devices(){
		queue_t<string_t> result; for( auto x=0; x<=255; x++ ){
			if( fs::exists_file( string::format("COM%d",x) ) )
			  { result.push( string::format("COM%d",x) ); }
		}	return result.data();
	}

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/