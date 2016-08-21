#ifndef STATE_HPP
#define STATE_HPP

#include <functional>

template<class VAL, class ARG = VAL>
class state
{
public:
        state(bool is_terminal = false)
                :_value(),
                 _eval( ),
                 _pstate(nullptr),
                 _fstate(nullptr),
                 _is_terminal(is_terminal)
        {};

        state(const VAL& value, const  std::function<bool(const state<VAL,ARG>*,const ARG&)>& eval, bool is_terminal = false)
                :_value(value),
                 _eval(eval),
                 _pstate(nullptr),
                 _fstate(nullptr),
                 _is_terminal(is_terminal)
        {}

        state(
                const VAL& value,
                const  std::function<bool(const state<VAL,ARG>*,const ARG&)>& eval,
                const state<VAL,ARG>* pstate,
                const state<VAL,ARG>* fstate,
                bool is_terminal = false)
                : _value(value),
                  _eval(eval),
                  _pstate(pstate),
                  _fstate(fstate),
                  _is_terminal(is_terminal)
        {}

        state(const state<VAL,ARG>& copy)
                : _value(copy._value),
                  _eval(copy._eval),
                  _pstate(copy._pstate),
                  _fstate(copy._fstate),
                  _is_terminal(copy._is_terminal)
        {}

        state(state<VAL,ARG>&& move)
                : _value(std::move(move._value)),
                  _eval(std::move(move._eval)),
                  _pstate(move._pstate),
                  _fstate(move._fstate),
                  _is_terminal(move._is_terminal)
        {
                move._pstate = nullptr;
                move._fstate = nullptr;
        }

        state<VAL,ARG>& operator=(const state<VAL,ARG>& op)
        {
                _value = op._value;
                _eval = op._eval;
                _pstate = op._pstate;
                _fstate = op._fstate;
                _is_terminal = op._is_terminal;
                return *this;
        }

        state<VAL,ARG>& operator=(state<VAL,ARG>&& op)
        {
                _value = std::move(op._value);
                _eval = std::move(op._eval);
                _pstate = std::move(op._pstate);
                _fstate = std::move(op._fstate);
                _is_terminal = op._is_terminal;

                op._pstate = nullptr;
                op._fstate = nullptr;
                return *this;
        }

        virtual ~state() {}

        state* process(const ARG& argument)
        {
                return _eval(this, argument)
                       ? _pstate
                       : _fstate == nullptr
                       ? nullptr : _fstate->process(argument);
        }

        VAL value() const
        {
                return _value;
        }

        state<VAL,ARG>& value(const VAL& v)
        {
                _value = v;
                return *this;
        }

        state<VAL,ARG>& value(VAL&& v)
        {
                _value = v;
                return *this;
        }

        state<VAL,ARG>& eval(const  std::function<bool(const state<VAL,ARG>*,const ARG&)>& eval)
        {
                _eval = eval;
                return *this;
        }

        state<VAL,ARG>* pstate() const
        {
                return _pstate;
        }

        state<VAL,ARG>& pstate(state<VAL,ARG>* ps)
        {
                _pstate = ps;
                return *this;
        }

        state<VAL,ARG>* fstate() const
        {
                return _fstate;
        }

        state<VAL,ARG>& fstate(state<VAL,ARG>* fs)
        {
                _fstate = fs;
                return *this;
        }

        bool is_terminal()
        {
                return _is_terminal;
        }

        state<VAL,ARG>& is_terminal(bool is_terminal)
        {
                _is_terminal = is_terminal;
                return *this;
        }

private:
        VAL _value;
        std::function<bool(const state<VAL,ARG>*, const ARG&)> _eval;
        state<VAL,ARG>* _pstate;
        state<VAL,ARG>* _fstate;
        bool _is_terminal;
};

#endif // STATE_HPP
