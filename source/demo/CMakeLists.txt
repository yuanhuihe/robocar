
# Check if examples are enabled
if(NOT OPTION_BUILD_DEMOS)
	return()
endif()

# Example applications
add_subdirectory(test_gpio)
add_subdirectory(test_ymq)



