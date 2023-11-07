
add_library(librvo2 SHARED librvo2.cpp)
target_link_libraries(librvo2 PRIVATE ${RVO_LIBRARY})
target_compile_options(Blocks PRIVATE ${RVO_EXAMPLES_COMPILE_OPTIONS})
set_target_properties(Blocks PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
