file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(allocator_lib ${SRC})
