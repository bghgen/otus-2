cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.1)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(PROJECT_VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif (DEFINED ENV{TRAVIS_BUILD_NUMBER})

add_executable(ip_filter ip_filter.cpp)

set(CMAKE_C_COMPILER "gcc-6")
set(CMAKE_CXX_COMPILER "g++-6")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")


target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)



if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
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

