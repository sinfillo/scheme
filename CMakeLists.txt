project(scheme)

set(CMAKE_CXX_STANDARD 20)

add_library(src_project
    src/tokenizer.cpp
    src/parser.cpp
    src/scheme.cpp
    src/object.cpp
)

add_executable(main repl/main.cpp)
target_link_libraries(main src_project)