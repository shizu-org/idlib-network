#include "idlib/network.h"

#include <malloc.h>

#if IDLIB_OPERATING_SYSTEM_WINDOWS == IDLIB_OPERATING_SYSTEM

#include "idlib/network/windows.h"
#if 0
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#endif

#endif

idlib_status
IdLib_Network_AddressFamily_toString
  (
    IdLib_Network_AddressFamily addressFamily,
    char **addressFamilyString
  )
{
  if (!addressFamilyString) {
    return IDLIB_ARGUMENT_INVALID;
  }
  switch (addressFamily) {
    case IdLib_Network_AddressFamily_Ipv4: {
      char *temporary = strdup("IPv4");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *addressFamilyString = temporary;
      return IDLIB_SUCCESS;
    } break;
    case IdLib_Network_AddressFamily_Ipv6: {
      char* temporary = strdup("IPv6");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *addressFamilyString = temporary;
      return IDLIB_SUCCESS;
     } break;
     default: {
       return IDLIB_ARGUMENT_INVALID;
     } break;
  };
}

idlib_status
IdLib_Network_SocketType_toString
  (
    IdLib_Network_SocketType socketType,
    char **socketTypeString
  )
{
  if (!socketTypeString) {
    return IDLIB_ARGUMENT_INVALID;
  }
  switch (socketType) {
    case IdLib_Network_SocketType_Stream: {
      char *temporary = strdup("stream");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *socketTypeString = temporary;
      return IDLIB_SUCCESS;
    } break;
    case IdLib_Network_SocketType_Datagram: {
      char* temporary = strdup("datagram");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *socketTypeString = temporary;
      return IDLIB_SUCCESS;
     } break;
     default: {
       return IDLIB_ARGUMENT_INVALID;
     } break;
  };
}

idlib_status
IdLib_Network_Protocol_toString
  (
    IdLib_Network_Protocol protocol,
    char** protocolString 
  )
{
  if (!protocolString) {
    return IDLIB_ARGUMENT_INVALID;
  }
  switch (protocol) {
    case IdLib_Network_Protocol_Tcp: {
      char* temporary = strdup("TCP");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *protocolString = temporary;
      return IDLIB_SUCCESS;
    } break;
    case IdLib_Network_Protocol_Udp: {
      char* temporary = strdup("UDP");
      if (!temporary) {
        return IDLIB_ALLOCATION_FAILED;
      }
      *protocolString = temporary;
      return IDLIB_SUCCESS;
    } break;
    default: {
      return IDLIB_ARGUMENT_INVALID;
    } break;
  };
}

struct IdLib_Network_Socket {
  /// Pointer to a zero-terminated ANSI symbol sequence.
  /// This denotes either a hostname (aka node) or a numeric host addresss.
  /// A numeric host address is a
  /// - a decimal IPv4 address separated by dots
  /// - a hexadecimal IPv6 address seprated by colons
  char* node;
 
  /// Pointer to a zero-terminated ANSI symbol sequence.
  /// This denotes either a service name or a port number.
  /// A service name is an alias for a port number which is defined by the Internet Engineering Task Force (IETF).
  /// For example "http" is an alias for port "80".
  char* service;

  /// Socket if any, INVALID_SOCKET otherwise.
  SOCKET socket;
};

idlib_status
IdLib_Network_startup
  (
  )
{
  int iResult;
  // Initialize Winsock.
  WSADATA wsaData;
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0) {
    printf("WSAStartup failed: %d\n", iResult);
    return IDLIB_ENVIRONMENT_FAILED;
  }
  return IDLIB_SUCCESS;
}

idlib_status
IdLib_Network_shutdown
  (
  )
{
  // Uninitialize Winsock.
  WSACleanup();
  return IDLIB_SUCCESS;
}

static idlib_status map_addess_family(IdLib_Network_AddressFamily* target, int source) {
  switch (source) {
    default:
    case AF_UNSPEC:
    case AF_NETBIOS: {
      return IDLIB_ARGUMENT_INVALID;
    } break;
    case AF_INET: {
      *target = IdLib_Network_AddressFamily_Ipv4;
      return IDLIB_SUCCESS;
    } break;
    case AF_INET6: {
      *target = IdLib_Network_AddressFamily_Ipv6;
      return IDLIB_SUCCESS;
    } break;
  };
}

static idlib_status map_socket_type(IdLib_Network_SocketType* target, int source) {
  switch (source) {
    default:
    case 0: {
      return IDLIB_ARGUMENT_INVALID;
    } break;
    case SOCK_STREAM: {
      *target = IdLib_Network_SocketType_Stream;
      return IDLIB_SUCCESS;
    } break;
    case SOCK_DGRAM: {
      *target = IdLib_Network_SocketType_Datagram;
      return IDLIB_SUCCESS;
    } break;
  };
}

static idlib_status dump_addrinfo(ADDRINFO const* info) {
  idlib_status status;
  //
  IdLib_Network_AddressFamily addressFamily;
  status = map_addess_family(&addressFamily, info->ai_family);
  if (status) {
    return status;
  }
  char* addressFamilyString;
  status = IdLib_Network_AddressFamily_toString(addressFamily, &addressFamilyString);
  if (status) {
    return status;
  }
  fprintf(stdout, "family name : %s\n", addressFamilyString);
  free(addressFamilyString);
  //
  IdLib_Network_SocketType socketType;
  status = map_socket_type(&socketType, info->ai_socktype);
  if (status) {
    return status;
  }
  char* socketTypeString;
  status = IdLib_Network_SocketType_toString(socketType, &socketTypeString);
  if (status) {
    return status;
  }
  fprintf(stdout, "socket type : %s\n", socketTypeString);
  free(socketTypeString);
  return IDLIB_SUCCESS;
}

idlib_status
IdLib_Network_Socket_create
  (
    IdLib_Network_Socket** socket,
    char const *node,
    char const *service
  )
{
  if (!socket || !node || !service) {
    return IDLIB_ARGUMENT_INVALID;
  }
  IdLib_Network_Socket* socket1 = malloc(sizeof(IdLib_Network_Socket));
  if (!socket1) {
    return IDLIB_ALLOCATION_FAILED;
  }
  socket1->node = strdup(node);
  if (!socket1->node) {
    free(socket1);
    socket1 = NULL;
    return IDLIB_ALLOCATION_FAILED;
  }
  socket1->service = strdup(service);
  if (!socket1->service) {
    free(socket1->node);
    socket1->node = NULL;
    free(socket1);
    socket1 = NULL;
    return IDLIB_ALLOCATION_FAILED;
  }
  *socket = socket1;
  return IDLIB_SUCCESS;
}

idlib_status
IdLib_Network_Socket_destroy
  (
    IdLib_Network_Socket* socket
  )
{
  if (!socket) {
    return IDLIB_ARGUMENT_INVALID;
  }
  free(socket->service);
  socket->service = NULL;
  free(socket->node);
  socket->node = NULL;
  free(socket);
  socket = NULL;
  return IDLIB_SUCCESS;
}

static idlib_status
IdLib_Network_Socket_write
  (
    IdLib_Network_Socket* socket,
    char const* bytes,
    size_t numberOfBytes
  )
{
  size_t actual = 0;
  size_t target = numberOfBytes;
  while (actual != target) {
    int result = send(socket->socket, bytes + actual, target - actual, 0);
    if (SOCKET_ERROR == result) {
      return IDLIB_ENVIRONMENT_FAILED;
    }
    actual += (size_t)result;
  }
  return IDLIB_SUCCESS;
}

idlib_status
IdLib_Network_Socket_httpGetRequest
  (
    IdLib_Network_Socket* socket
  )
{
  int result;
  ADDRINFO* addresses;
  result = getaddrinfo(socket->node, socket->service, 0, &addresses);
  if (result) {
    fprintf(stderr, "%s:%d: %s failed\n", __FILE__, __LINE__, "getaddrinfo");
    return IDLIB_ENVIRONMENT_FAILED;
  }
  int i = 0;
  for (ADDRINFO* address = addresses; NULL != address; address = address->ai_next) {
    if (dump_addrinfo(address)) {
      freeaddrinfo(addresses);
      addresses = NULL;
      return IDLIB_ENVIRONMENT_FAILED;
    }
  }
  // Create the socket.
  socket->socket = wsa_socket(addresses->ai_family, addresses->ai_socktype, addresses->ai_protocol);
  if (INVALID_SOCKET == socket->socket) {
    freeaddrinfo(addresses);
    addresses = NULL;
    fprintf(stderr, "%s:%d: %s failed (%d)\n", __FILE__, __LINE__, "socket", WSAGetLastError());
    return IDLIB_ENVIRONMENT_FAILED;
  }

  // Connect to server.
  result = wsa_connect(socket->socket, addresses->ai_addr, addresses->ai_addrlen);
  if (0 != result) {
    wsa_closesocket(socket->socket);
    socket->socket = INVALID_SOCKET;
    freeaddrinfo(addresses);
    addresses = NULL;
    fprintf(stderr, "%s:%d: %s failed (%d)\n", __FILE__, __LINE__, "connect", WSAGetLastError());
    return IDLIB_ENVIRONMENT_FAILED;
  }

  const char* request =
    "GET / HTTP/1.1\n"
    "Host: google.com\n"
    "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\n"
    "\n"
    ;

  idlib_status status = IdLib_Network_Socket_write(socket, request, strlen(request));
  if (status) {
    wsa_shutdown(socket->socket);
    wsa_closesocket(socket->socket);
    socket->socket = INVALID_SOCKET;
    freeaddrinfo(addresses);
    addresses = NULL;
    return status;
  }
  wsa_shutdown(socket->socket);
  wsa_closesocket(socket->socket);
  socket->socket = INVALID_SOCKET;
  freeaddrinfo(addresses);
  addresses = NULL;
  return IDLIB_SUCCESS;
}
