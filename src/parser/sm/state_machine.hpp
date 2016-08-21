#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "state.hpp"
#include <forward_list>
#include <vector>

template<class VAL, class ARG = VAL>
class state_machine
{
public:
        state_machine()
        {}

        virtual ~state_machine()
        {
                for(auto s : _states){
                        delete s;
                }
        }

        state<VAL,ARG>* create(bool is_terminal = false){
                return _create(is_terminal);
        }

        state<VAL,ARG>* create(const VAL& value, const std::function<bool(const state<VAL,ARG>*,const ARG&)> eval, bool is_terminal = false){
                return _create(value, eval,is_terminal);
        }

        state<VAL,ARG>* create(const state<VAL,ARG>& state){
                return _create(state);
        }

        state<VAL,ARG>* create(state<VAL,ARG>&& state){
                return _create(state);
        }

        state<VAL,ARG>* process(const ARG& argument)
        {
                return _curr == nullptr
                                ? nullptr
                                : (_curr = _curr->process(argument));
        }

        state<VAL,ARG>* current(){
                return _curr;
        }

        void current(state<VAL,ARG>* state){
                _curr = state;
        }

private:
        state<VAL,ARG>* _curr;
        std::vector<state<VAL,ARG>*> _states;

        state<VAL,ARG>* _create(bool is_terminal){
                _states.push_back(new state<VAL>(VAL(), [](const state<VAL,ARG>*,const ARG&){
                        return false;
                }, is_terminal));
                return _states.back();
        }

        state<VAL,ARG>* _create(const VAL& value, std::function<bool(const state<VAL,ARG>*,const ARG&)> func, bool is_terminal){
                _states.push_back(new state<VAL,ARG>(value, func, is_terminal));
                return _states.back();
        }

        state<VAL,ARG>* _create(const state<VAL,ARG>& s){
                _states.push_back(new state<VAL,ARG>(s));
                return (_states.back());
        }

        state<VAL,ARG>* _create(state<VAL,ARG>&& s){
                _states.push_back(new state<VAL,ARG>(s));
                return (_states.back());
        }
};

#endif // STATE_MACHINE_HPP
