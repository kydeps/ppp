add_executable(example1
        example1.cc
        )
target_link_libraries(example1
        PRIVATE ppp::nastl
        )
kydepspackagetarget(example1)

add_executable(example
        example.cc
        )
target_link_libraries(example
        PRIVATE ppp::nastl
        )
kydepspackagetarget(example)
