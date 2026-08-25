cmake_minimum_required(VERSION 3.15)

project(
    BaaCorporateBondRateAnalyzer
    VERSION 1.0.0
    DESCRIPTION "Moody's Seasoned Baa Corporate Bond Rate Historical Analyzer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bond_analyzer src/bond_analyzer.cpp)

target_compile_options(bond_analyzer PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Werror -pedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)
