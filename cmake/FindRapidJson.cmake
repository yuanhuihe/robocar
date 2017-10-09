########################################################################
# CMake module for finding Rapid Json
#
# The following variables will be defined:
#
#  RAPIDJSON_FOUND
#  RAPIDJSON_INCLUDE_DIR
#

find_path(RAPIDJSON_INCLUDE_DIR
  NAMES rapidjson/rapidjson.h
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/rapidjson/include
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RapidJson DEFAULT_MSG RAPIDJSON_INCLUDE_DIR)
