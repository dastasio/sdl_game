add_library( dsdl_mans SHARED
	WindowMan.cpp InputMan.cpp
	WindowMan.hpp InputMan.hpp)

add_library (dsdl_game SHARED
	Block.cpp
	Block.hpp)

target_link_libraries( dsdl_mans ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

# if sdl include directory includes "/SDL2", "SDL2" is removed
if (${SDL2_INCLUDE_DIR} MATCHES "SDL2")
	STRING(REGEX REPLACE "SDL2" "" SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR})
endif()
include_directories( ${SDL2_INCLUDE_DIR} ${mylib})


add_executable( ${EXEC_NAME} main.cpp)

target_link_libraries( ${EXEC_NAME} dsdl_mans dsdl_game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

# setting c++ version
target_compile_features( dsdl_mans PUBLIC cxx_nullptr)
target_compile_features( dsdl_game PUBLIC cxx_nullptr)
target_compile_features( ${EXEC_NAME} PUBLIC cxx_nullptr)