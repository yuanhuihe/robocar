########################################################################
# CMake module for finding OpenCV
#
# The following variables will be defined:
#
#  OpenCV_FOUND
#  OpenCV_INCLUDE_DIR
#  OpenCV_LIBRARY
#

unset(OpenCV_INCLUDE_DIR CACHE)
unset(OpenCV_FOUND CACHE)
unset(OpenCV_LIBRARY CACHE)

if (${arch} STREQUAL "i386")
    set(build_arch "x86")
endif (${arch} STREQUAL "i386")
if (${arch} STREQUAL "x86_64")
    set(build_arch "x64")
endif (${arch} STREQUAL "x86_64")

find_path(OpenCV_INCLUDE_DIR
    NAMES opencv opencv2
    PATHS ${PROJECT_SOURCE_DIR}/thirdparty/opencv/include/
    NO_DEFAULT_PATH)

find_library(OpenCV_LIBRARY_DEBUG
    NAMES opencv_world310d
    PATHS  ${PROJECT_SOURCE_DIR}/thirdparty/opencv/x64/debug/
    NO_DEFAULT_PATH)

find_library(OpenCV_LIBRARY_RELEASE
    NAMES opencv_world310
    PATHS  ${PROJECT_SOURCE_DIR}/thirdparty/opencv/x64/release/
    NO_DEFAULT_PATH)

set(OpenCV_LIBRARY optimized ${OpenCV_LIBRARY_RELEASE} debug ${OpenCV_LIBRARY_DEBUG})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenCV DEFAULT_MSG OpenCV_LIBRARY OpenCV_INCLUDE_DIR)
