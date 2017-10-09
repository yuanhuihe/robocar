########################################################################
# CMake module for finding rapid xml
#
# The following variables will be defined:
#
#  RapidXml_FOUND
#  RapidXml_INCLUDE_DIR
#

find_path(RapidXml_INCLUDE_DIR
  NAMES rapidxml.hpp
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/XmlParse/
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RapidXml DEFAULT_MSG RapidXml_INCLUDE_DIR)
