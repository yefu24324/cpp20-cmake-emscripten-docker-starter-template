
add_executable(my_target)

target_set_common_properties(my_target)

target_sources(my_target
	PRIVATE
	main.cpp
)

if (EMSCRIPTEN)

	set_target_properties(my_target PROPERTIES SUFFIX ".html")

endif (EMSCRIPTEN)
