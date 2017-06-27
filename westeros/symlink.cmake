macro(install_symlink sympath filepath)
    message(STATUS "Created symlink: $ENV{DESTDIR}${sympath} -> ${filepath}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} $ENV{DESTDIR}${sympath})
endmacro()
