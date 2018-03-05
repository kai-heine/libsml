cmake_minimum_required(VERSION 3.0)
project(libsml_example C)

add_executable(sml_server sml_server.c)
target_link_libraries(sml_server PUBLIC SML::sml m)
target_compile_options(sml PUBLIC
	$<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
		-Wall -Wextra
	>
)