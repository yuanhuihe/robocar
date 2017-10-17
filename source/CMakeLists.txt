
# 
# Configuration for all sub-projects
# 

# Generate version-header
string(TOUPPER ${META_PROJECT_NAME} META_PROJECT_NAME_UPPER)

if(WIN32)
    # Date for filling in rc file information
    set(STAMP_FORMAT "%Y")
    unset(ENV{SOURCE_DATE_EPOCH})
    string(TIMESTAMP CURRENT_YEAR "${STAMP_FORMAT}")
    set(META_NAME "@META_NAME@")
    configure_file(version.rc.in ${PROJECT_BINARY_DIR}/version.rc)
else(WIN32)
    configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME}/${META_PROJECT_NAME}-version.h)
endif(WIN32)

# 
# Sub-projects
# 

# Libraries
set(IDE_FOLDER "DLL")
add_subdirectory(baselib)
add_subdirectory(fiblib)
add_subdirectory(gpiorw)
add_subdirectory(walkdriver)


# App
set(IDE_FOLDER "App")
add_subdirectory(robocar)

# Tests
set(IDE_FOLDER "Tests")
add_subdirectory(tests)

# Demos
set(IDE_FOLDER "Demo")
add_subdirectory(demo)


# 
# Deployment
# 

# Deploy generated headers
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/${META_PROJECT_NAME} DESTINATION include COMPONENT dev)
