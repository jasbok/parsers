#ifndef REGEX_H
#define REGEX_H

#include "sm/state_machine.hpp"
#include "buffer_functions.hpp"

#include <iostream>

template<class C>
class regex
{
public:
        regex(const C* regex)
                : _regex(regex),
                  _sm(),
                  _start_state(nullptr),
                  _end_state(nullptr)
        {
                _build();
        }

        bool match(const C* str, bool exact = true)
        {
                while(!::end(str) && process(::read(str)));
                return exact ? match() && ::end(str) : _partial_match;
        }

        bool process(C ch)
        {
                if(ch != L(C,'\0')) {
                        state<C>* state = _sm.process(ch);
                        if(state != nullptr && state->is_terminal()) {
                                _partial_match = true;
                        }
                        return state != nullptr;
                }
                return false;
        }

        bool match()
        {
                return _sm.current() != nullptr && _sm.current()->is_terminal();
        }

        void reset()
        {
                _partial_match = false;
                _sm.current(_start_state);
        }

private:
        const C* _regex;
        state_machine<C> _sm;
        state<C>* _start_state;
        state<C>* _end_state;
        bool _partial_match;

        std::function<bool(const state<C>*, const C&)> _fmatch(const C& arg)
        {
                return [](const state<C>* s, const C& arg) {
                        return s->value() == arg;
                };
        }

        state<C>* _build_match(const C& ch)
        {
                auto state = _sm.create(ch, _fmatch(ch));
                auto next  = _build_state(state);
                if(state->pstate() == nullptr) {
                        state->pstate(next);
                }
                return state;
        }

        state<C>* _build_quantifier_optional(state<C>* prev)
        {
                state<C>* next = _build_state(prev);
                prev->pstate(next);
                prev->fstate(next);
                if(next->is_terminal()) {
                        prev->is_terminal(true);
                }
                return next;
        }

        state<C>* _build_quantifier_zero_or_more(state<C>* prev)
        {
                state<C>* next = _build_state(prev);
                prev->pstate(prev);
                prev->fstate(next);
                return next;
        }

        state<C>* _build_quantifier_one_or_more(state<C>* prev)
        {
                state<C>* more = _sm.create(*prev);
                state<C>* next = _build_state(prev);
                if(next->is_terminal()) {
                        more->is_terminal(true);
                }
                more->pstate(more);
                more->fstate(next);
                return more;
        }

        state<C>* _build_final()
        {
                _end_state = _sm.create(true);
                return _end_state;
        }

        void _build()
        {
                _start_state = _build_state(nullptr);
                _sm.current(_start_state);
        }

        state<C>* _build_state(state<C>* prev)
        {
                state<C>* state = nullptr;
                C ch = ::read(_regex);
                switch(ch) {
                case L(C, '\\'):
                        break;
                case L(C, '.'):
                        break;
                case L(C, '^'):
                        break;
                case L(C, '$'):
                        break;
                case L(C, '|'):
                        break;
                case L(C, '*'):
                        state = _build_quantifier_zero_or_more(prev);
                        break;
                case L(C, '+'):
                        state = _build_quantifier_one_or_more(prev);
                        break;
                case L(C, '?'):
                        state =  _build_quantifier_optional(prev);
                        break;
                case L(C, '['):
                        break;
                case L(C, ']'):
                        break;
                case L(C, '('):
                        break;
                case L(C, ')'):
                        break;
                case L(C, '{'):
                        break;
                case L(C, '}'):
                        break;
                case L(C,'\0'):
                        state = _build_final();
                        break;
                default:
                        state =  _build_match(ch);
                        break;
                }
                return state;
        }
};

#endif // REGEX_H
