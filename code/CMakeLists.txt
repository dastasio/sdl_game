add_library( dsdl_mans SHARED
	WindowMan.cpp 
	WindowMan.hpp)

target_link_libraries( dsdl_mans ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

if (${SDL2_INCLUDE_DIR} MATCHES "SDL2")
	STRING(REGEX REPLACE "SDL2" "" SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
endif()
message( ${SDL2_INCLUDE_DIR})
include_directories( ${SDL2_INCLUDE_DIR} ${mylib})


add_executable( ${EXEC_NAME} main.cpp)

target_link_libraries( ${EXEC_NAME} dsdl_mans ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})