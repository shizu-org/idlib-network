#if !defined(IDLIB_NETWORK_WINDOWS_H_INCLUDED)
#define IDLIB_NETWORK_WINDOWS_H_INCLUDED

#include "idlib/network/configure.h"

#if IDLIB_OPERATING_SYSTEM_WINDOWS == IDLIB_OPERATING_SYSTEM

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>

static inline SOCKET wsa_socket(int af, int type, int protocol) {
  return socket(af, type, protocol);
}

static inline int wsa_connect(SOCKET s, const struct sockaddr* name, int namelen) {
  return connect(s, name, namelen);
}

static inline int wsa_shutdown(SOCKET s) {
  return shutdown(s, SD_SEND);
}

static inline int wsa_closesocket(SOCKET s) {
  return closesocket(s);
}

#endif

#endif // IDLIB_NETWORK_WINDOWS_H_INCLUDED
