cmake_minimum_required(VERSION 3.0)

add_library(sml
	src/sml_file.c
	src/sml_attention_response.c
	src/sml_transport.c
	src/sml_octet_string.c
	src/sml_shared.c
	src/sml_number.c
	src/sml_message.c
	src/sml_time.c
	src/sml_list.c
	src/sml_status.c
	src/sml_value.c
	src/sml_tree.c
	src/sml_boolean.c
	src/sml_crc16.c
	src/sml_open_request.c
	src/sml_open_response.c
	src/sml_get_list_request.c
	src/sml_get_list_response.c
	src/sml_close_request.c
	src/sml_close_response.c
	src/sml_set_proc_parameter_request.c
	src/sml_get_proc_parameter_request.c
	src/sml_get_proc_parameter_response.c
	src/sml_get_profile_pack_request.c
	src/sml_get_profile_pack_response.c
	src/sml_get_profile_list_request.c
	src/sml_get_profile_list_response.c
	src/sml_list_type.c
	src/sml_cosem_value.c
)

target_include_directories(sml PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_options(sml PRIVATE
	$<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
		-Wall -Wextra
	>
)

target_compile_definitions(sml
	PUBLIC $<$<BOOL:${SML_WITHOUT_TRANSPORT}>:SML_NO_TRANSPORT>
	PRIVATE SML_NO_UUID_LIB
)

set_target_properties(sml PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED TRUE
	C_EXTENSIONS OFF
)

add_library(SML::sml ALIAS sml)

# Installation

include(GNUInstallDirs)

install(TARGETS sml
	EXPORT sml-targets
	ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
	DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT sml-targets
	FILE SMLTargets.cmake
	NAMESPACE SML::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SML
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/SMLConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/SMLConfig.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SML
)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/SMLConfig.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SML
)

export(EXPORT sml-targets
	FILE ${CMAKE_CURRENT_BINARY_DIR}/SMLTargets.cmake
	NAMESPACE SML::
)

export(PACKAGE SML)