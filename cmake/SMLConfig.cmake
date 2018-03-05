get_filename_component(SML_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

if(NOT TARGET SML::sml)
    include("${SML_CMAKE_DIR}/SMLTargets.cmake")
endif()

set(SML_LIBRARIES SML::sml)