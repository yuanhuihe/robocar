
# 
# Default dependencies for the runtime-package
# 

# Install 3rd-party runtime dependencies into runtime-component
# install(FILES ... COMPONENT runtime)

install(FILES ${PROJECT_SOURCE_DIR}/thirdparty/libczmq/bin/libczmq.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
install(FILES ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/bin/libsodium.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
install(FILES ${PROJECT_SOURCE_DIR}/thirdparty/libzmq/bin/libzmq.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
install(FILES ${PROJECT_SOURCE_DIR}/thirdparty/zyre/bin/libzyre.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)

if(OPTION_ISORNOT_LOAD)

endif()

#install(FILES ${PROJECT_SOURCE_DIR}/thirdparty/syn/syncthing.exe DESTINATION ${INSTALL_ROOT} COMPONENT tool)

# Qt
#find_package(Qt5Core)
#get_target_property(QtCore_location Qt5::Core LOCATION)
#get_filename_component(QT_BIN "${QtCore_location}" PATH)
#install(FILES ${QT_BIN}/Qt5Core.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
#install(FILES ${QT_BIN}/Qt5Gui.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
#install(FILES ${QT_BIN}/Qt5Widgets.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)
#install(FILES ${QT_BIN}/Qt5Network.dll DESTINATION ${INSTALL_ROOT} COMPONENT runtime)

# Qt plugins
#get_filename_component(QT_DIR "${QT_BIN}" DIRECTORY)
#install(DIRECTORY ${QT_DIR}/plugins/platforms DESTINATION ${INSTALL_BIN} COMPONENT runtime)
#install(DIRECTORY ${QT_DIR}/plugins/imageformats DESTINATION ${INSTALL_BIN} COMPONENT runtime)

# 
# Full dependencies for self-contained packages
# 

if(OPTION_SELF_CONTAINED)

    # Install 3rd-party runtime dependencies into runtime-component
    # install(FILES ... COMPONENT runtime)

endif()
