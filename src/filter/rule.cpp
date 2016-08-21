#include "rule.h"

using namespace std;

rule::rule()
        : is_exception(false),
          expression(),
          css_selector(),
          domains(),
          domains_excp(),
          options(),
          options_excp()
{}

rule::rule(const rule &r)
        : is_exception(r.is_exception),
          expression(r.expression),
          css_selector(r.css_selector),
          domains(r.domains),
          domains_excp(r.domains_excp),
          options(r.options),
          options_excp(r.options_excp)
{}

rule::rule(rule &&r)
        : is_exception(r.is_exception),
          expression(r.expression),
          css_selector(r.css_selector),
          domains(std::move(r.domains)),
          domains_excp(std::move(r.domains_excp)),
          options(std::move(r.options)),
          options_excp(std::move(r.options_excp))
{}

void rule::operator=(const rule &r)
{
        is_exception = r.is_exception;
        expression = r.expression;
        css_selector = r.css_selector;
        domains = r.domains;
        domains_excp = r.domains_excp;
        options = r.options;
        options_excp = r.options_excp;
}

void rule::operator=(rule &&r)
{
        is_exception = r.is_exception;
        expression = r.expression;
        css_selector = r.css_selector;
        domains = std::move(r.domains);
        domains_excp = std::move(r.domains_excp);
        options = std::move(r.options);
        options_excp = std::move(r.options_excp);
}

void rule::add(const excludable<string> &domain)
{
        if(domain.is_exclusion){
                domains_excp.push_back(domain.value);
        }
        else{
                domains.push_back(domain.value);
        }
}

void rule::add(excludable<string> &&domain)
{
        if(domain.is_exclusion){
                domains_excp.push_back(domain.value);
        }
        else{
                domains.push_back(domain.value);
        }
}

void rule::add(const excludable<Option> &option)
{
        if(option.is_exclusion){
                options_excp.push_back(option.value);
        }
        else{
                options.push_back(option.value);
        }
}

void rule::add(excludable<Option> &&option)
{
        if(option.is_exclusion){
                options_excp.push_back(option.value);
        }
        else{
                options.push_back(option.value);
        }
}
