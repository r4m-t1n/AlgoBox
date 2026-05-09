file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(algo_tests ${TEST_SOURCES})

target_link_libraries(algo_tests
    PRIVATE
    GTest::gtest_main
    algobox_lib
    Threads::Threads
    raylib
)

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${TEST_SOURCES})

if(UNIX AND NOT APPLE)
    target_link_libraries(algo_tests PRIVATE m dl rt X11)
endif()

include(GoogleTest)
gtest_discover_tests(algo_tests)