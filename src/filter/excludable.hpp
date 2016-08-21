#ifndef EXCLUDABLE_HPP
#define EXCLUDABLE_HPP

#include <utility>

template<class T>
class excludable
{
public:
        excludable()
                : value(), is_exclusion(false)
        {}

        excludable(const T& value, bool is_exclusion)
                : value(value), is_exclusion(is_exclusion)
        {}

        excludable(T&& value, bool is_exclusion)
                : value(std::move(value)), is_exclusion(is_exclusion)
        {}

        excludable<T>& operator=(const excludable<T>& op){
                this->value = op.value;
                this->is_exclusion = op.is_exclusion;
                return *this;
        }

        excludable<T>& operator=(const T& value){
                this->value = value;
                return *this;
        }

        excludable<T>& operator=(bool is_exclusion){
                this->is_exclusion = is_exclusion;
                return *this;
        }

        excludable<T>& operator=(excludable<T>&& op){
                this->value = std::move(op.value);
                this->is_exclusion = op.is_exclusion;
                return *this;
        }

        excludable<T>& operator=(T&& value){
                this->value = std::move(value);
                return *this;
        }

        bool operator==(excludable<T>&& op){
                return is_exclusion == op.is_exclusion && value == op.value;
        }

        T value;
        bool is_exclusion;
};

#endif // EXCLUDABLE_HPP
