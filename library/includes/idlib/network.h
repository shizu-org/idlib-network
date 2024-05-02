#if !defined(IDLIB_NETWORK_H_INCLUDED)
#define IDLIB_NETWORK_H_INCLUDED

/// @brief Enumeration of network address families.
typedef enum idlib_network_address_family {

  /// @brief IPv6 network address family.
  idlib_network_address_familiy_ipv4,
  
  /// @brief IPv4 network address family.
  idlib_network_address_familiy_ipv6,

} enum idlib_network_address_familiy;

/// @brief Startup the network service.
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
idlib_status
idlib_network_startup
  (
  );

/// @brief Shutdown the network service.
/// @undefined The network service is shutdown while idlib_network_socket objects exist.
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
idlib_status
idlib_network_shutdown
  (
  );
  
/// The opaque type of a socket.
typedef struct idlib_network_socket idlib_network_socket;

/// @brief Create a socket.
/// @param [out] socket A pointer to a <code>idlib_network_socket*</code> variable.
/// @return #IDLIB_SUCCESS on success.
/// A non-zero IdLib status code on failure.
/// @success <code>*socket</code> was assigned a pointer to the idlib_network_socket object.
idlib_status
idlib_network_socket_create
  (
    idlib_network_socket** socket
  );

/// @brief Destroy a socket.
/// @param socket A pointer to the idlib_network_socket object.
idlib_status
idlib_network_socket_destroy
  (
    idlib_network_socket* socket
  );

#endif // IDLIB_NETWORK_H_INCLUDED