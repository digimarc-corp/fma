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

set (target_compile_defs
	UNICODE
)

set (target_link_libs_pub
)

set (target_link_libs_priv
)

#
# Actually apply above settings to all the targets
#

add_library(${target_name} SHARED ${target_source_files})

foreach(target IN LISTS target_name)
	set_target_properties(${target} PROPERTIES ${target_properties})

	target_include_directories(${target}
		PUBLIC ${target_include_dirs_public}
		PRIVATE ${target_include_dirs_private}
	)

	target_compile_definitions(${target} PUBLIC ${target_compile_defs})

	target_link_libraries(${target}
		PUBLIC ${target_link_libs_pub}
		PRIVATE ${target_link_libs_priv}
	)
endforeach()
