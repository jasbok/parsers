list(APPEND PARSER_SRCS
	"basic_reader.cpp"
	"buffer_reader.cpp"
	"css_selector_reader.cpp"
	"regex.cpp"
	"stream_reader.cpp"
	"token.cpp"
)

add_library(parser STATIC ${PARSER_SRCS})
