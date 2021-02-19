set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

add_library(bgpsim SHARED
    caidareader.cc
    graphsearch.cc
    graph.cc
    reader.cc
)

add_executable(Test test.cc)
add_executable(Test2 test2.cc)

target_link_libraries(Test bgpsim)
target_link_libraries(Test2 bgpsim)

install(TARGETS bgpsim DESTINATION lib)
install(DIRECTORY . DESTINATION include/bgpsim
        FILES_MATCHING PATTERN "*.h")