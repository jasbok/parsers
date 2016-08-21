list(APPEND CSS_SRCS
    "selector.cpp"
)

add_library(css STATIC ${CSS_SRCS})

