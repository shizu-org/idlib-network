#if !defined(IDLIB_NETWORK_H_INCLUDED)
#define IDLIB_NETWORK_H_INCLUDED

#include "idlib/process.h"

/// @brief Enumeration of network address families.
typedef enum IdLib_Network_AddressFamily {

  /// @brief IPv6 network address family.
  IdLib_Network_AddressFamily_Ipv4,
  
  /// @brief IPv4 network address family.
  IdLib_Network_AddressFamily_Ipv6,

} IdLib_Network_AddressFamily;

idlib_status 
IdLib_Network_AddressFamily_toString
  (
    IdLib_Network_AddressFamily addressFamily,
    char **addressFamilyString
  );

/// @brief Enumeration of network socket types.
typedef enum IdLib_Network_SocketType {

  /// @brief Typical for TCP.
  IdLib_Network_SocketType_Stream,

  /// @brief Typical for UDP.
  IdLib_Network_SocketType_Datagram,

} IdLib_Network_SocketType;

idlib_status
IdLib_Network_SocketType_toString
  (
    IdLib_Network_SocketType socketType,
    char **socketTypeString
  );

/// @brief Enumeration of network protocols.
typedef enum IdLib_Network_Protocol {

  /// @brief TCP network protocol.
  IdLib_Network_Protocol_Tcp,
  
  /// @brief UDP network protocol.
  IdLib_Network_Protocol_Udp,

} IdLib_Network_Protocol;

idlib_status
IdLib_Network_Protocol_toString
  (
    IdLib_Network_Protocol protocol,
    char** protocolString
  );

/// @brief Startup the network service.
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
idlib_status
IdLib_Network_startup
  (
  );

/// @brief Shutdown the network service.
/// @undefined The network service is shutdown while idlib_network_socket objects exist.
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
idlib_status
IdLib_Network_shutdown
  (
  );
  
/// The opaque type of a socket.
typedef struct IdLib_Network_Socket IdLib_Network_Socket;

/// @brief Create a socket.
/// @param [out] socket A pointer to a <code>IdLib_Network_Socket*</code> variable.
/// @param node
/// Pointer to a zero-terminated ANSI symbol sequence.
/// This denotes either a hostname (aka node) or a numeric host addresss.
/// A numeric host address is a
/// - a decimal IPv4 address separated by dots
/// - a hexadecimal IPv6 address seprated by colons
/// @param service
/// Pointer to a zero-terminated ANSI symbol sequence.
/// This denotes either a service name or a port number.
/// A service name is an alias for a port number which is defined by the Internet Engineering Task Force (IETF).
/// For example "http" is an alias for port "80".
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
/// @success <code>*socket</code> was assigned a pointer to the IdLib_Network_Socket object.
idlib_status
IdLib_Network_Socket_create
  (
    IdLib_Network_Socket** socket,
    char const* node,
    char const* service
  );

/// @brief Destroy a socket.
/// @param socket A pointer to the IdLib_Network_Socket object.
idlib_status
IdLib_Network_Socket_destroy
  (
    IdLib_Network_Socket* socket
  );

idlib_status
IdLib_Network_Socket_httpGetRequest
  (
    IdLib_Network_Socket* socket
  );

#endif // IDLIB_NETWORK_H_INCLUDED
