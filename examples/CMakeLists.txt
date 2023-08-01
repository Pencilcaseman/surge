function(make_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE surge)

    # Ensure all examples finish correctly
    message(STATUS "[ SURGE ] Adding example '${name}'")
    add_test(NAME ${name}
            COMMAND ${name})
endfunction()

make_example(demoWindow)
make_example(simpleSquare)
make_example(bouncingCircle)
make_example(simpleGUI)
