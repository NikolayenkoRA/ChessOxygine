cmake_minimum_required (VERSION 2.6)
project (Chess)

add_subdirectory(../oxygine-framework oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
# file(GLOB SOURCES 
# "../src/main.cpp  "
# "../src/GameConfig.cpp "
# "../src/GameConfig.h "
# "../src/Board.cpp "
# "../src/Board.h "
# "../src/RuleChecker.h "
# "../src/RuleChecker.cpp "
# "../src/Piece.h "
# "../src/Piece.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${OXYGINE_CORE_LIBS})
