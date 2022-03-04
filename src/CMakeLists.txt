set (target_name dmrc_fma)

set (target_source_files
	DMRC/FMA/Internal/Comparison.hpp
	DMRC/FMA/Internal/ContainerType.hpp
	DMRC/FMA/Internal/EnableIf.hpp
	DMRC/FMA/Internal/FPTypeTraits.hpp
	DMRC/FMA/Internal/Inline.h
	DMRC/FMA/Internal/Pow.hpp
	DMRC/FMA/Internal/TypeTraits.hpp
	DMRC/FMA/Internal/Container.hpp
	DMRC/FMA/Internal/FPMath.hpp
	DMRC/FMA/Internal/FPShift.hpp
	DMRC/FMA/Internal/Simple.hpp
)

set (target_properties
	CXX_STANDARD 98
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS ON
	LINKER_LANGUAGE CXX

	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin  # .exe, .dll
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib  # .so, .dylib
	ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib  # .a, .lib
)

set (target_include_dirs_public
	${CMAKE_CURRENT_LIST_DIR}
)

set (target_include_dirs_private
	${CMAKE_CURRENT_LIST_DIR}/DMRC/FMA/Internal
)

#
# Actually apply above settings to all the targets
#

add_library(${target_name} INTERFACE ${target_source_files})
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

