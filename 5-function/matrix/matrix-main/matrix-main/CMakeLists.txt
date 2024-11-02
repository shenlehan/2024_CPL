project(matrix C)

set(CMAKE_C_STANDARD 17)

add_compile_options(-Wno-unused-result -O2)

add_executable(matrix main.c src/matrix.c)
include_directories(include/)
