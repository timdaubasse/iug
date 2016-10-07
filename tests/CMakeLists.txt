# tp1 target
add_executable(tp1 tp1.c)
target_link_libraries(tp1 eibase ${Allegro_LIBRARIES})

add_executable(tp2 tp2.c)
target_link_libraries(tp2 ei eibase ${Allegro_LIBRARIES})

add_executable(tp3 tp3.c)
target_link_libraries(tp3 ei eibase ${Allegro_LIBRARIES})

# Automatic tests
add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests ei eibase ${Allegro_LIBRARIES})

enable_testing()
ms_add_catch_tests(unit_tests) 
 
