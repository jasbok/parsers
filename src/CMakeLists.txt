list(APPEND SRCS
    "main.cpp"
)

add_subdirectory(css)
add_subdirectory(filter)
add_subdirectory(parser)
add_subdirectory(std)
add_subdirectory(tidy)

add_executable(main ${SRCS})
target_link_libraries(main ${TARGET_LINK_LIBS} ${STATIC_LIBS})
