set (example_properties
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX

	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/examples/bin  # .exe, .dll
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/examples/lib  # .so, .dylib
	ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/examples/lib  # .a, .lib
)
set (example_link_libraries
	dmrc_fma
)

set (target_name ex_readme)
add_executable(${target_name}
	ex_readme.cpp
)
set_target_properties(${target_name} PROPERTIES ${example_properties})
target_link_libraries(${target_name} ${example_link_libraries})
