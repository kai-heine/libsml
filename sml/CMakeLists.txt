cmake_minimum_required(VERSION 3.0)
include(GNUInstallDirs)

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
    $<IF:$<CXX_COMPILER_ID:MSVC>,
    /W4,
    -Wall -Wextra -pedantic>
)

find_package(UUID)
if(UUID_FOUND)
    target_link_libraries(sml PUBLIC uuid)
else()
    target_compile_definitions(sml PRIVATE SML_NO_UUID_LIB)
endif()

install(TARGETS sml EXPORT libsmlconfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT libsmlconfig DESTINATION share/libsml/cmake)

export(TARGETS sml FILE libsmlconfig.cmake)