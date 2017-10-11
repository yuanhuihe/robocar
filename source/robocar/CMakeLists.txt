
# 
# External dependencies
# 

#find_package(ZMQ REQUIRED)
#find_package(CZMQ REQUIRED)
#find_package(ZYRE REQUIRED)
#find_package(Qt5 COMPONENTS Widgets Network)
#find_package(Qt5LinguistTools)

# Target name
set(target robocar)

# Tell CMake to run moc when necessary:
#set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#SET(Lang_files ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${target}_zh.ts)
#SET(Lang_en_files ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${target}_en.ts)
#QT5_CREATE_TRANSLATION(LangSrcs ${Lang_files})
#QT5_CREATE_TRANSLATION(LangenSrcs ${Lang_en_files})

#QT5_ADD_RESOURCES(QRC ${CMAKE_CURRENT_SOURCE_DIR}/${target}.qrc)
#set(RC ${CMAKE_CURRENT_SOURCE_DIR}/${target}.rc)

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
        #${ZMQ_INCLUDE_DIR}
        #${CZMQ_INCLUDE_DIR}
        #${ZYRE_INCLUDE_DIR}
        #${Qt5Widgets_INCLUDES}
        #${Qt5Network_INCLUDES}
        ${DEFAULT_INCLUDE_DIRECTORIES}
        ${PROJECT_BINARY_DIR}/source/include
        ${PROJECT_SOURCE_DIR}/source/include
        ${PROJECT_SOURCE_DIR}/thirdparty/
        ${PROJECT_SOURCE_DIR}/thirdparty/XmlParse
        ${PROJECT_SOURCE_DIR}/thirdparty/memory/include
        ${PROJECT_SOURCE_DIR}/thirdparty/msgpack/include
        ${PROJECT_SOURCE_DIR}/thirdparty/pugixml
        ${PROJECT_SOURCE_DIR}/thirdparty/utility
   )

# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
        #Shlwapi
        #Psapi
        ${DEFAULT_LIBRARIES}
        #${ZMQ_LIBRARY}
        #${CZMQ_LIBRARY}
        #${ZYRE_LIBRARY}
        #${Qt5Widgets_LIBRARIES}
        #${Qt5Network_LIBRARIES}
        ${META_PROJECT_NAME}::fiblib
        ${META_PROJECT_NAME}::baselib
        ${META_PROJECT_NAME}::walkdriver
        #ws2_32
        #Wininet
        #Iphlpapi
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
# Install QT language files
file(GLOB QM ${CMAKE_CURRENT_BINARY_DIR}/*.qm)
install(FILES ${QM} DESTINATION ${INSTALL_BIN}/langs COMPONENT runtime)
