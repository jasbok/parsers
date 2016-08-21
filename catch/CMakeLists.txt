list(APPEND tests
    # Catch Main
    "catch.cpp"

    # Show common.h in IDE source tree
    "common.h"

    # Tests
    "filter.cpp"
    "reader.cpp"
    "regex.cpp"
)
add_executable(catch ${tests})
target_link_libraries(catch ${TARGET_LINK_LIBS} ${STATIC_LIBS})
