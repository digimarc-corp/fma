set(target_name test_all)

enable_testing()

set (target_source_files
	Test_ContainerType.cpp
	Test_FPMath.cpp
	Test_FPTypeTraits.cpp
	Test_Simple.cpp
	Test_Typedefs.cpp
)

set (target_properties
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX

	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin  # .exe, .dll
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib  # .so, .dylib
	ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib  # .a, .lib
)

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/heads/main.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${target_name} ${target_source_files})
set_target_properties(${target_name} PROPERTIES ${target_properties})
target_link_libraries(${target_name}
	gtest_main
	dmrc_fma
)

# Enroll the test in ctest
include(GoogleTest)
gtest_discover_tests(${target_name})
