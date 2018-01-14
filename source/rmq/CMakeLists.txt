
# 
# External dependencies
# 

# find_package(THIRDPARTY REQUIRED)

# 
# Library name and options
# 

# Target name
set(target rmq)

# Exit here if required dependencies are not met
message(STATUS "Lib ${target}")

# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}_features.h")
set(export_file  "include/${target}_api.h")
set(export_macro "${target_upper}_API")


# 
# Sources
# 
set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")

file(GLOB headers
    "${include_path}/*.h" 
    "${include_path}/*.hpp"
	"${PROJECT_SOURCE_DIR}/source/include/_inl.hpp"
)
file(GLOB sources
    "${source_path}/*.h"
    "${source_path}/*.hpp"
    "${source_path}/*.cpp"
    "${source_path}/arb/*.h"
    "${source_path}/arb/*.cpp"
    "${source_path}/OptiReader/*.h"
    "${source_path}/OptiReader/*.cpp"
    "${PROJECT_SOURCE_DIR}/source/include/*.cpp"
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# 
# Create library
# 
add_library(${target}
    ${sources}
    ${headers}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})

# Export library for downstream projects
export(TARGETS ${target} NAMESPACE ${META_PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/cmake/${target}/${target}-export.cmake)

# Create feature detection header
# Compilers: https://cmake.org/cmake/help/v3.1/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE_%3CLANG%3E_COMPILER_ID
# Feature: https://cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html

# Check for availability of module; use pre-generated version if not found
if (WriterCompilerDetectionHeaderFound)
    write_compiler_detection_header(
        FILE ${feature_file}
        PREFIX ${target_upper}
        COMPILERS AppleClang Clang GNU MSVC
        FEATURES cxx_alignas cxx_alignof cxx_constexpr cxx_final cxx_noexcept cxx_nullptr cxx_sizeof_member cxx_thread_local
        VERSION 3.2
    )
else()
    file(
        COPY ${PROJECT_SOURCE_DIR}/codegeneration/${target}_features.h
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/${target}
        USE_SOURCE_PERMISSIONS
    )
endif()

# Create API export header
generate_export_header(${target}
    EXPORT_FILE_NAME  ${export_file}
    EXPORT_MACRO_NAME ${export_macro}
)


# 
# Project options
# 

set_target_properties(${target}
    PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


# 
# Include directories
# 
target_include_directories(${target}
    PRIVATE
		${MemQueue_INCLUDE_DIR}
		${ZMQ_INCLUDE_DIR}
		${CZMQ_INCLUDE_DIR}
		${MAJORDOMO_INCLUDE_DIR}
		${LIBG3_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/include
		${PROJECT_BINARY_DIR}/source/include
		${PROJECT_SOURCE_DIR}/source/include
        ${PROJECT_SOURCE_DIR}/source/include/pattern
		${PROJECT_SOURCE_DIR}/source/include/framework
		${PROJECT_SOURCE_DIR}/thirdparty
        ${PROJECT_SOURCE_DIR}/thirdparty/pugixml
        ${PROJECT_SOURCE_DIR}/thirdparty/XmlParse
        ${PROJECT_SOURCE_DIR}/thirdparty/memory/include
    PUBLIC
        ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        
)


# 
# Libraries
# 
target_link_libraries(${target}
    PRIVATE
        ${DEFAULT_LIBRARIES}
        ${ZMQ_LIBRARY}
		${CZMQ_LIBRARY}
		${MAJORDOMO_LIBRARY}
    PUBLIC
        ${DEFAULT_LIBRARIES}

    INTERFACE
)

# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE

    PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${target_upper}_STATIC_DEFINE>
        ${DEFAULT_COMPILE_DEFINITIONS}

    INTERFACE
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE

    PUBLIC
        ${DEFAULT_COMPILE_OPTIONS}

    INTERFACE
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE

    PUBLIC
        ${DEFAULT_LINKER_OPTIONS}

    INTERFACE
)


# 
# Deployment
# 

# Library
install(TARGETS ${target}
    EXPORT  "${target}-export"            COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN}    COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_SHARED} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB}    COMPONENT dev
)

# Header files
install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# Generated header files
install(DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE}
    COMPONENT dev
)

# CMake config
install(EXPORT ${target}-export
    NAMESPACE   ${META_PROJECT_NAME}::
    DESTINATION ${INSTALL_CMAKE}/${target}
    COMPONENT   dev
)
