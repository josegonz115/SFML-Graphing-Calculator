cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME graphing_calculator)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")
set(SOURCE_FILES main.cpp includes/SFML/animate.h includes/SFML/animate.cpp includes/SFML/button.h
       includes/SFML/graph.h includes/SFML/graph.cpp includes/SFML/graph_constants.h includes/SFML/sidebar.cpp
        includes/SFML/sidebar.h includes/SFML/text_box.h includes/linked_list_functions/linked_list_functions.h
        includes/node/node.h includes/queue/MyQueue.h includes/rpn/rpn.cpp includes/rpn/rpn.h
        includes/shunting_yard/shunting_yard.cpp includes/shunting_yard/shunting_yard.h includes/stack/MyStack.h
        includes/token/constants.h includes/token/function.h includes/token/function.cpp includes/token/integer.cpp includes/token/integer.h includes/token/leftparen.cpp includes/token/leftparen.h includes/token/operator.cpp includes/token/operator.h includes/token/rightparen.cpp includes/token/rightparen.h includes/token/token.cpp includes/token/token.h includes/token/variable.cpp includes/token/variable.h
        includes/tokenizer/tokenizer.h includes/tokenizer/tokenizer.cpp)


if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif ()

set(SFML_ROOT C:/SFML-2.5.1)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
#set(SFML_DIR C:/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML  REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()