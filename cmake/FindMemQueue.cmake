########################################################################
# CMake module for finding MemQueue
#
# The following variables will be defined:
#
#  MemQueue_FOUND
#  MemQueue_INCLUDE_DIR
#

find_path(MemQueue_INCLUDE_DIR
    NAMES ProducerConsumerQueue.h
    PATHS ${PROJECT_SOURCE_DIR}/thirdparty/memory/include/
    NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MemQueue DEFAULT_MSG MemQueue_INCLUDE_DIR)
