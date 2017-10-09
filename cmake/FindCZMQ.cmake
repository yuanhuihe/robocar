########################################################################
# CMake module for finding CZMQ
#
# The following variables will be defined:
#
#  CZMQ_FOUND
#  CZMQ_INCLUDE_DIR
#  CZMQ_LIBRARY
#

find_path(CZMQ_INCLUDE_DIR
  NAMES czmq.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libczmq/include
  NO_DEFAULT_PATH)
find_library(CZMQ_LIBRARY
  NAMES libczmq
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libczmq/lib
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CZMQ DEFAULT_MSG CZMQ_LIBRARY CZMQ_INCLUDE_DIR)
