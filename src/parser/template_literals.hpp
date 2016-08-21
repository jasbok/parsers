#ifndef TEMPLATE_LITERALS_HPP
#define TEMPLATE_LITERALS_HPP

//
// Source : http://stackoverflow.com/questions/9040247/how-to-express-a-string-literal-within-a-template-parameterized-by-the-type-of-t
//
#define L(C, STR) template_literal<C>(STR, L##STR)

template<class C> constexpr
C template_literal(char c, wchar_t w);

template<typename C>  constexpr
const C * template_literal(const char * c, const wchar_t * w);

template<> constexpr
char template_literal<char>(char c, wchar_t w)
{
    return c;
}

template<> constexpr
wchar_t template_literal<wchar_t>(char c, wchar_t w)
{
    return w;
}

template<> constexpr
const char * template_literal<char>(const char * c, const wchar_t * w)
{
    return c;
}

template<> constexpr
const wchar_t * template_literal<wchar_t>(const char * c, const wchar_t * w)
{
    return w;
}

#endif // TEMPLATE_LITERALS_HPP
