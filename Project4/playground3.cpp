#include <iostream>

template <typename T>
class MyTemplateClass
{
    T value;

public:
    MyTemplateClass(T value) : value(value) {}
    std::ostream &_stream_insertion_operator(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const MyTemplateClass &obj) { return obj._stream_insertion_operator(os); }
};

template <typename T>
std::ostream &MyTemplateClass<T>::_stream_insertion_operator(std::ostream &os) const
{
    os << "Value: " << value;
    return os;
}

int main()
{
    MyTemplateClass<int> intObj(42);
    std::cout << intObj << std::endl;

    return 0;
}
