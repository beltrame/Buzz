add_executable(testbuzzdarray testbuzzdarray.c)
target_link_libraries(testbuzzdarray buzz)

add_executable(testbuzzdict testbuzzdict.c)
target_link_libraries(testbuzzdict buzz)

add_executable(testbuzzmsg testbuzzmsg.c)
target_link_libraries(testbuzzmsg buzz)

add_executable(testbuzzlex testbuzzlex.c)
target_link_libraries(testbuzzlex buzz)

add_executable(testbuzz testbuzz.c)
target_link_libraries(testbuzz buzz)