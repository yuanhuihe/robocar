########################################################################
# CMake module for finding ZYRE
#
# The following variables will be defined:
#
#  ZYRE_FOUND
#  ZYRE_INCLUDE_DIR
#  ZYRE_LIBRARY
#

find_path(ZYRE_INCLUDE_DIR
  NAMES zyre.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/zyre/include
  NO_DEFAULT_PATH)
find_library(ZYRE_LIBRARY
  NAMES libzyre
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/zyre/lib
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZYRE DEFAULT_MSG ZYRE_LIBRARY ZYRE_INCLUDE_DIR)
