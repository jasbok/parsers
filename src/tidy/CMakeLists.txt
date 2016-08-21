list(APPEND TIDY_SRCS
    "tidy++.cpp"
    )

add_library(tidy++ STATIC ${TIDY_SRCS})
