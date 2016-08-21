#ifndef REGEX_ENUMS_H
#define REGEX_ENUMS_H

enum class regex_enum{
        NOT_NEWLINE,
        TAB,
        VERTICAL_TAB,
        FORM_FEED,
        CARRIAGE_RETURN,
        CONTROL_CODE,
        ASCII_CHAR,
        UNICODE_CHAR,
        NUL,
        BACK_REFERENCE,
        DIGIT,
        NOT_DIGIT,
        WHITESPACE,
        NOT_WHITESPACE,
        WORD,
        NOT_WORD,
        CHAR,
        CLASS,
        NEGATED_CLASS,
        STAR,
        PLUS,
        OPTIONAL,
        EXACT,
        MIN,
        MIN_MAX,
        GROUP,
        PASSIVE,
        BEGINNING_OF_LINE,
        END_OF_LINE,
        WORD_BOUNDARY,
        NOT_WORD_BOUNDARY,
        POSITIVE_LOOKAHEAD,
        NEGATIVE_LOOKAHEAD,
        ALTERNATION,
        ISALNUM,
        ISALPHA,
        ISBLANK,
        ISCNTRL,
        ISDIGIT,
        ISGRAPH,
        ISLOWER,
        ISPRINT,
        ISPUNCT,
        ISSPACE,
        ISUPPER,
        ISXDIGIT
};

#endif // REGEX_ENUMS_H
