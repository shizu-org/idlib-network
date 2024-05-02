# Integrate with your CMake project
The proper way to integrate *IdLib Network with your CMake project is by using `FetchContent`:

You need to fetch *IdLib Network* and its dependency *IdLib Process*:

You can do that as follows:

```
include(FetchContent)

#######################################################################################################################

set(idlib-process.repository CACHE STRING "IdLib Process: The Git repository to check out")
if (NOT idlib-process.repository)
  set(idlib-process.repository https://github.com/michaelheilmann/idlib-process.git)
endif()

set(idlib-process.tag CACHE STRING "IdLib Process: The Git tag to check out")
if (NOT idlib-process.tag)
  set(idlib-process.tag 1.4)
endif()

set(idlib-process.source-dir CACHE STRING "IdLib Process: Path to the source directory")
if (NOT idlib-process.source-dir)
  set(idlib-process.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-src")
endif()

set(idlib-process.binary-dir CACHE STRING "IdLib Process: Path to the build directory")
if (NOT idlib-process.binary-dir)
  set(idlib-process.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-bld")
endif()
                    
#######################################################################################################################

set(idlib-network.repository CACHE STRING "IdLib Network: The Git repository to check out")
if (NOT idlib-network.repository)
  set(idlib-network.repository https://github.com/michaelheilmann/idlib-network.git)
endif()

set(idlib-network.tag CACHE STRING "IdLib Network: The Git tag to check out")
if (NOT idlib-network.tag)
  set(idlib-network.tag 1.0)
endif()

set(idlib-network.source-dir CACHE STRING "IdLib Network: Path to the source directory")
if (NOT idlib-network.source-dir)
  set(idlib-network.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-network-1.0-src")
endif()

set(idlib-network.binary-dir CACHE STRING "IdLib Network: Path to the build directory")
if (NOT idlib-network.binary-dir)
  set(idlib-network.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-network-1.0-bld")
endif()

#######################################################################################################################

FetchContent_Declare(idlib-network
                     GIT_REPOSITORY ${idlib-network.repository}
                     GIT_TAG ${idlib-network.tag}
                     SOURCE_DIR ${idlib-network.source-dir}
                     BINARY_DIR ${idlib-network.binary-dir})

```

Now simply add
```
FetchContent_MakeAvailable(idlib-network)
```
And you can use *IdLib Network* by linking the library target `idlib-network` to a target `<target>`
```
target_link_libraries(<target> idlib-network)
```
and by adding the include directive  
```
#include "idlib/network.h"
```
in your C files.
