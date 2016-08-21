#ifndef TOKEN_H
#define TOKEN_H

#include <ostream>

template<class T, class V>
class token
{
public:
        token() {}

        token(const token<T,V>& token)
                :_type(token._type), _value(token._value)
        {}

        token(token<T,V>&& token)
                :_type(std::move(token._type)), _value(std::move(token._value))
        {}
        token(const T& type, const V& value)
                :_type(type), _value(value)
        {}
        token(T&& type, V&& value)
                :_type(type), _value(value)
        {}

        virtual ~token() {}

        token<T,V>& operator=(const token<T,V>& op){
                _type = op._type;
                _value = op.value;
                return *this;
        }

        token<T,V>& operator=(token<T,V>&& op){
                _type = std::move(op._type);
                _value = std::move(op.value);
                return *this;
        }

        T type()
        {
                return _type;
        }

        token<T,V>* type(const T& type)
        {
                _type = type;
                return this;
        }

        V value()
        {
                return _value;
        }

        token<T,V>* value(V value)
        {
                _value = value;
                return this;
        }

private:
        T _type;
        V _value;
};

template<class T, class V>
std::ostream& operator<<(std::ostream& os, const token<T,V>& val)
{
        return os << "token[type=" << val._type << ",value=" << val._value << "]";
}

#endif // TOKEN_H
