add_library (convert convert.c)

target_include_directories (convert PUBLIC convert)
set_target_properties(convert PROPERTIES PUBLIC_HEADER includes/convert.h)

set_target_properties(convert PROPERTIES SOVERSION 1)

install(TARGETS convert
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )



add_library (DES DES.c)

target_include_directories (DES PUBLIC DES)
set_target_properties(DES PROPERTIES PUBLIC_HEADER includes/DES.h)

set_target_properties(DES PROPERTIES SOVERSION 1)

install(TARGETS DES
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )



add_library (display display.c)

target_include_directories (display PUBLIC display)
set_target_properties(display PROPERTIES PUBLIC_HEADER includes/display.h)

set_target_properties(display PROPERTIES SOVERSION 1)

install(TARGETS display
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )