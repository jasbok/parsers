#ifndef CSS_SELECTOR_READER_ENUMS_H
#define CSS_SELECTOR_READER_ENUMS_H

#include <ostream>
#include <vector>

#define ENUM_ENTRY(VAR) VAR,
#define ENUM_LABEL(VAR) #VAR,
#define ENUM(DO) \
	DO(UNKNOWN = 0) \
	DO(ID) \
	DO(CLASS) \
	DO(ATTRIBUTE) \
	DO(END) \
	\
	DO(ENUM_SIZE)

enum class css_token{
	ENUM(ENUM_ENTRY)
};

constexpr const char* css_token_strings[] = {
	ENUM(ENUM_LABEL)
};

std::ostream& operator<<(std::ostream& os, const css_token& val)
{
	return  val >= css_token::UNKNOWN && val < css_token::ENUM_SIZE
			? os << css_token_strings[(int)val]
			: os << "???";
}

#endif // CSS_SELECTOR_READER_ENUMS_H
