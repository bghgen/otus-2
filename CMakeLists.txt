cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.1)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PROJECT_VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif (DEFINED ENV{TRAVIS_BUILD_NUMBER})


find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(ip_filter ip_filter.cpp)
add_library(ip_filter_lib lib.cpp)
add_executable(gtest test.cpp)



target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

target_link_libraries(gtest
    ${GTEST_LIBRARIES}
    ip_filter_lib
)

target_link_libraries( gtest
${CMAKE_THREAD_LIBS_INIT}
ip_filter_lib )

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(gtest PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT trypic@gmail.com)

include(CPack)


enable_testing()


add_test(gtest gtest)
