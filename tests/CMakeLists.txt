# tp1 target
add_executable(tp3 tp3.c)
target_link_libraries(tp3 eibase ${Allegro_LIBRARIES})

# Automatic tests
add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests eibase ${Allegro_LIBRARIES})

enable_testing()
ms_add_catch_tests(unit_tests) 
 
