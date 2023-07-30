file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_library(allocator_lib ${SRC})

target_include_directories(allocator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
