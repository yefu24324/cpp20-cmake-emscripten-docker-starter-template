# Set the target properties that all targets from this project are using.
function(target_set_common_properties Target)

	set_target_properties(${Target}
		PROPERTIES
		# C++ 20 is required for co-routines
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF

		# Always treat warnings as errors
		COMPILE_WARNING_AS_ERROR ON
	)

	# Enable more warnings
	if (MSVC)
		target_compile_options(${Target} PRIVATE /W4)
	else()
		target_compile_options(${Target} PRIVATE -Wall -Wextra)
		# You may want to selectively remove some warnings here
	endif()

	# Place the target in the "co-realm" directory in the IDEs project structure
	set_target_properties(${Target} PROPERTIES FOLDER "my_project")

endfunction(target_set_common_properties)
