/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOfficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_SERIAL
#define NODEPP_SERIAL

/*────────────────────────────────────────────────────────────────────────────*/

#if   _KERNEL_ == NODEPP_KERNEL_WINDOWS
    #include <nodepp/fs.h>
    #include <nodepp/promise.h>
    #include "windows/serial.h"
#elif _KERNEL_ == NODEPP_KERNEL_POSIX
    #include <nodepp/fs.h>
    #include <nodepp/promise.h>
    #include "posix/serial.h"
#else
    #error "This OS Does not support serial.h"
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#endif
