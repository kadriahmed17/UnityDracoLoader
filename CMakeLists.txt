cmake_minimum_required(VERSION 3.16)

option(WITH_TESTS "Build Tests" OFF)

set(CMAKE_CXX_STANDARD 17)


# rest of source code
set(LIB_SOURCES
        src/dllmain.cpp
        )


# conan is required hard, library name, version and description are configured from conan
if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
else ()
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif ()

project(${CONAN_PACKAGE_NAME}_PROJECT VERSION ${CONAN_PACKAGE_VERSION} LANGUAGES CXX)

conan_basic_setup(TARGETS)


add_library(${CONAN_PACKAGE_NAME} SHARED
        ${LIB_SOURCES}
        )


conan_target_link_libraries(${CONAN_PACKAGE_NAME})


target_include_directories(${CONAN_PACKAGE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

install(TARGETS ${CONAN_PACKAGE_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
