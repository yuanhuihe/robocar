########################################################################
# CMake module for finding CZMQ
#
# The following variables will be defined:
#
#  CZMQ_FOUND
#  CZMQ_INCLUDE_DIR
#  CZMQ_LIBRARY
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


find_path(CZMQ_INCLUDE_DIR
  NAMES czmq.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libczmq/include
  NO_DEFAULT_PATH)
find_library(CZMQ_LIBRARY
  NAMES czmq libczmq
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/libczmq/lib/${build_platform}/
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CZMQ DEFAULT_MSG CZMQ_LIBRARY CZMQ_INCLUDE_DIR)
