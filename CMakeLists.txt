cmake_minimum_required(VERSION 3.20)
project(flashcards VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLiteCpp QUIET)
if (NOT SQLiteCpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
        GIT_TAG 3.3.1
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(SQLiteCpp)
endif()

set(SOURCE_FILES src/main.cc src/flashcard.cc src/db.cc src/session.cc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLiteCpp)
target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wpedantic -Wextra)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

