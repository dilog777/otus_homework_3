file(GLOB_RECURSE SRC *.h *.hpp *.cpp)

add_executable(allocator ${SRC})

target_include_directories(allocator PRIVATE
	../library
)

target_link_libraries(allocator PRIVATE
	allocator_lib
)
