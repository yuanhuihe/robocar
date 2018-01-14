
# 
# External dependencies
# 

#find_package(Qt5 COMPONENTS Widgets Network)
#find_package(Qt5LinguistTools)

# Target name
set(target robocar)
add_definitions(-DUNICODE -D_UNICODE)

# Exit here if required dependencies are not met
message(STATUS "App: ${target}")

# 
# Sources
# 
file(GLOB headers
    "*.h"
    "*.hpp"
    "router/*.h"
    "${PROJECT_SOURCE_DIR}/source/include/Logger.h"
    "${PROJECT_SOURCE_DIR}/source/include/CRCCode.h"
)

file(GLOB sources
    "*.cpp"
    "router/*.cpp"
    "${PROJECT_SOURCE_DIR}/source/include/Logger.cpp"
    "${PROJECT_SOURCE_DIR}/source/include/CRCCode.cpp"
)


# 
# Create executable
# 

# Build executable
add_executable(${target} ${sources} ${headers})

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

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
        #${Qt5Widgets_INCLUDES}
        #${Qt5Network_INCLUDES}
        ${DEFAULT_INCLUDE_DIRECTORIES}
        ${PROJECT_BINARY_DIR}/source/include
        ${PROJECT_SOURCE_DIR}/source/include
        ${PROJECT_SOURCE_DIR}/thirdparty/
        ${PROJECT_SOURCE_DIR}/thirdparty/memory/include
        ${PROJECT_SOURCE_DIR}/thirdparty/utility
   )

# 
# Libraries
# 
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(${target}
        PRIVATE
            ${DEFAULT_LIBRARIES}
            ${META_PROJECT_NAME}::rmq
            ${META_PROJECT_NAME}::executive
        )
else ()
    target_link_libraries(${target}
        PRIVATE
            -lwiringPi
            -pthread
            -lm
            -lrt          # shm_open
            -lcrypt       # crypt
            ${DEFAULT_LIBRARIES}
            ${META_PROJECT_NAME}::rmq
            ${META_PROJECT_NAME}::executive
        )
endif ()

# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
        ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(${target}
    PRIVATE		
    	${DEFAULT_COMPILE_OPTIONS}
		-Wall
		-pipe
		
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
        ${DEFAULT_LINKER_OPTIONS}
)


# 
# Deployment
# 

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT runtime
)


