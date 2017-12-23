########################################################################
# CMake module for finding ZMQ
#
# The following variables will be defined:
#
#  ZMQ_FOUND
#  ZMQ_INCLUDE_DIR
#  ZMQ_LIBRARY
#

if (${UNIX})
  if(${APPLE})
    set(build_platform "mac")
  else()
    set(build_platform "linux")
  endif()
else()
  set(build_platform "windows")
endif()


if (${arch} STREQUAL "i386")
    set(build_arch "x86")
endif (${arch} STREQUAL "i386")
if (${arch} STREQUAL "x86_64")
    set(build_arch "x64")
endif (${arch} STREQUAL "x86_64")

find_path(ZMQ_INCLUDE_DIR
  NAMES zmq.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/include
  NO_DEFAULT_PATH)
find_library(ZMQ_LIBRARY
  NAMES zmq libzmq
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/lib/${build_platform}/${build_arch}
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZMQ DEFAULT_MSG ZMQ_LIBRARY ZMQ_INCLUDE_DIR)
