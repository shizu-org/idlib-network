/*
  IdLib Network
  Copyright (C) 2023-2024 Michael Heilmann. All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "idlib/network.h"

// EXIT_SUCCESS
#include <stdlib.h>

int
main
  (
    int argc,
    char** argv
  )
{
  if (IdLib_Network_startup()) {
    return EXIT_FAILURE;
  }
  IdLib_Network_Socket* socket = NULL;
  if (IdLib_Network_Socket_create(&socket, "google.com", "http")) {
    IdLib_Network_shutdown();
    return EXIT_FAILURE;
  }
  if (IdLib_Network_Socket_httpGetRequest(socket)) {
    IdLib_Network_Socket_destroy(socket);
    socket = NULL;
    IdLib_Network_shutdown();
    return EXIT_FAILURE;
  }
  if (IdLib_Network_Socket_httpGetResponse(socket)) {
    IdLib_Network_Socket_destroy(socket);
    socket = NULL;
    IdLib_Network_shutdown();
    return EXIT_FAILURE;
  }
  IdLib_Network_Socket_destroy(socket);
  socket = NULL;
  IdLib_Network_shutdown();
  return EXIT_SUCCESS;
}

