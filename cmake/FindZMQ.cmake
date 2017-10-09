########################################################################
# CMake module for finding ZMQ
#
# The following variables will be defined:
#
#  ZMQ_FOUND
#  ZMQ_INCLUDE_DIR
#  ZMQ_LIBRARY
#

find_path(ZMQ_INCLUDE_DIR
  NAMES zmq.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/include
  NO_DEFAULT_PATH)
find_library(ZMQ_LIBRARY
  NAMES libzmq
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/lib
  NO_DEFAULT_PATH)
  
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZMQ DEFAULT_MSG ZMQ_LIBRARY ZMQ_INCLUDE_DIR)
