cmake_minimum_required(VERSION 3.10)
project(AlgoBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        5.0
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(algobox_lib INTERFACE)
target_include_directories(algobox_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)

add_executable(linear_search_example examples/linear_search.cpp)
add_executable(linear_search_recursive_example examples/linear_search_recursive.cpp)
add_executable(binary_search_example examples/binary_search.cpp)
add_executable(bubble_sort_example examples/bubble_sort.cpp)
add_executable(insertion_sort_example examples/insertion_sort.cpp)
add_executable(selection_sort_example examples/selection_sort.cpp)
add_executable(merge_sort_example examples/merge_sort.cpp)
add_executable(quick_sort_example examples/quick_sort.cpp)

target_link_libraries(linear_search_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(linear_search_recursive_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(binary_search_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(bubble_sort_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(insertion_sort_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(selection_sort_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(merge_sort_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)
target_link_libraries(quick_sort_example
    PRIVATE
    algobox_lib
    raylib
    Threads::Threads
)

if(UNIX AND NOT APPLE)
    target_link_libraries(linear_search_example PRIVATE m dl rt X11)
endif()