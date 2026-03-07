cmake_minimum_required (VERSION 2.6)
project (Chess)

add_subdirectory(../oxygine-framework oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")

add_executable(Chess  ../src/main.cpp ../src/GameConfig.cpp ../src/GameConfig.h ../src/Board.cpp ../src/Board.h ../src/RuleChecker.h ../src/RuleChecker.cpp)
target_link_libraries(Chess ${OXYGINE_CORE_LIBS})
