cmake_minimum_required (VERSION 2.6)
project (ChessGame)

add_subdirectory(../../../ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(ChessGame ../src/main.cpp  ../src/example.h )
target_link_libraries(ChessGame ${OXYGINE_CORE_LIBS})
