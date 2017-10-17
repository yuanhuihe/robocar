
# Check if examples are enabled
if(NOT OPTION_BUILD_DEMOS)
	return()
endif()

# Example applications
add_subdirectory(gpio_test)
#add_subdirectory(fiblib)



