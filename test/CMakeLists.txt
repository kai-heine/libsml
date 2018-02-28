cmake_minimum_required(VERSION 3.0)

add_library(unity 
    unity/unity.c
    unity/unity_fixture.c
)
target_include_directories(unity PUBLIC unity)

add_executable(test_run
    test_main.c
    src/test_helper.c
    src/sml_octet_string_test.c
    src/sml_buffer_test.c
    src/sml_number_test.c
    src/sml_boolean_test.c
    src/sml_value_test.c
    src/sml_status_test.c
    src/sml_list_test.c
    src/sml_time_test.c
    src/sml_tree_test.c
    src/sml_file_test.c
    src/sml_open_request_test.c
    src/sml_get_profile_pack_request_test.c
    src/sml_message_test.c
)
target_link_libraries(test_run PUBLIC unity sml)

add_test(libsml_test test_run)