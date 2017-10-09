########################################################################
# CMake module for finding Eigen
#
# The following variables will be defined:
#
#  Eigen_FOUND
#  Eigen_INCLUDE_DIR
#
  
find_path(Eigen_INCLUDE_DIR
  NAMES Eigen
  PATHS ${PROJECT_SOURCE_DIR}/thirdparty/Eigen-3.3.4/
  NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Eigen DEFAULT_MSG Eigen_INCLUDE_DIR)
