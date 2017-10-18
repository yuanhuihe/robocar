
# 
# External dependencies
# 

#find_package(ZMQ REQUIRED)

# Target name
set(target gpio_test)

# Exit here if required dependencies are not met
message(STATUS "Demo: ${target}")

# 
# Sources
# 
file(GLOB headers
    "*.h"
)

file(GLOB sources
    "*.cpp"
)


# 
# Create executable
# 

# Build executable
#add_executable(${target} WIN32 ${sources} ${headers} ${QRC} ${RC} ${LangSrcs} ${LangenSrcs})
add_executable(${target} ${sources} ${headers} ${QRC} ${RC} ${LangSrcs} ${LangenSrcs})

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

#qt5_use_modules(MotionClient Widgets Network )
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
        ${DEFAULT_INCLUDE_DIRECTORIES}
   )

# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
        ${DEFAULT_LIBRARIES}
        #${META_PROJECT_NAME}::gpiorw
    )

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

