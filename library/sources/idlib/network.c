#include "idlib/network.h"

idlib_status
idlib_network_startup
  (
  )
{ return IDLIB_SUCCESS; }

idlib_status
idlib_network_shutdown
  (
  )
{ return IDLIB_SUCCES; }

idlib_status
idlib_network_socket_create
  (
    idlib_network_socket** socket
  )
{
  if (!socket) {
    return IDLIB_ARGUMENT_INVALID;
  }
  idlib_network_socket* socket1 = malloc(sizeof(idlib_network_socket));
  if (!socket1) {
    return IDLIB_ALLOCATION_FAILED;
  }
  *socket = socket1;
  return IDLIB_SUCCESS;
}

idlib_status
idlib_network_socket_destroy
  (
    idlib_network_socket* socket
  )
{
  if (!socket) {
    return IDLIB_ARGUMENT_INVALID;
  }
  free(socket);
  socket = NULL;
  return IDLIB_SUCCESS;
}
