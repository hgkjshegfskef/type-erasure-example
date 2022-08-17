add_executable(type_erasure circle.cc circle_operations.cc main.cc
                            shape_operations.cc square.cc square_operations.cc)
target_include_directories(type_erasure PRIVATE .)
