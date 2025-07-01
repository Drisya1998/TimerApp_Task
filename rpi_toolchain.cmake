# rpi_toolchain.cmake# Target platform
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# Toolchain
SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)

# SET(CMAKE_SYSROOT /path/to/rpi/sysroot)

# Set C flags
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")