#include "../src/filter/rule_parser.h" // Include first to avoid tag::Type::DOMAIN conflict.
#include "common.h"

namespace filter_catch
{

void EQUALS(const rule& actual, const rule& expected)
{
        CHECK(actual.is_exception == expected.is_exception);
        CHECK(actual.expression == expected.expression);
        CHECK(actual.css_selector == expected.css_selector);
        CHECK_EQUALS("Domains", actual.domains, expected.domains);
        CHECK_EQUALS("Domain Exceptions", actual.domains_excp, expected.domains_excp);
        CHECK_EQUALS("Options", actual.options, expected.options);
        CHECK_EQUALS("Option Exceptions", actual.options_excp, expected.options_excp);
}

SCENARIO("rule => /banner/*/img.gif")
{
        std::string rule_str = "/banner/*/img.gif";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.expression = "/banner/*/img.gif";
        EQUALS(actual, expected);
}

SCENARIO("rule => ###div")
{
        std::string rule_str = "###div";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.css_selector = "#div";
        EQUALS(actual, expected);
}

SCENARIO("rule => /banner/*/img.gif###div")
{
        std::string rule_str = "/banner/*/img.gif###div";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.expression = "/banner/*/img.gif";
        expected.css_selector = "#div";
        EQUALS(actual, expected);
}

SCENARIO("rule => ###div$script,~object")
{
        std::string rule_str = "###div$script,~object";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.css_selector = "#div";
        expected.options = {Option::SCRIPT};
        expected.options_excp = {Option::OBJECT};
        EQUALS(actual, expected);
}

SCENARIO("rule => /banner/*/img.gif###div$script,~object")
{
        std::string rule_str = "/banner/*/img.gif###div$script,~object";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.expression = "/banner/*/img.gif";
        expected.css_selector = "#div";
        expected.options = {Option::SCRIPT};
        expected.options_excp = {Option::OBJECT};
        EQUALS(actual, expected);
}

SCENARIO("rule => /banner/*/img.gif###div$script,~object,domain=abc|~def|ghi")
{
        std::string rule_str = "/banner/*/img.gif###div$script,~object,domain=abc|~def|ghi";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.expression = "/banner/*/img.gif";
        expected.css_selector = "#div";
        expected.options = {Option::SCRIPT};
        expected.options_excp = {Option::OBJECT};
        expected.domains = {"abc", "ghi"};
        expected.domains_excp = {"def"};
        EQUALS(actual, expected);
}

SCENARIO("rule => /banner/*/img.gif###div$script,domain=abc|~def|ghi,~object,image")
{
        std::string rule_str = "/banner/*/img.gif###div$script,domain=abc|~def|ghi,~object,image";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.expression = "/banner/*/img.gif";
        expected.css_selector = "#div";
        expected.options = {Option::SCRIPT, Option::IMAGE};
        expected.options_excp = {Option::OBJECT};
        expected.domains = {"abc", "ghi"};
        expected.domains_excp = {"def"};
        EQUALS(actual, expected);
}

SCENARIO("rule => @@.png?*#$domain=abc|def")
{
        std::string rule_str = "@@.png?*#$object,domain=abc|def";
        rule_parser parser;
        rule actual = parser.parse(rule_str);
        rule expected;
        expected.is_exception = true;
        expected.expression = ".png?*#";
        expected.domains = {"abc", "def"};
        expected.options = {Option::OBJECT};
        EQUALS(actual, expected);
}

}
