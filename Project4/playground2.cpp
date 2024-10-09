template <class T>
class A;

template <class T>
double f(A<T> const &a);

template <class T>
class A
{
    double p_;
    friend double f<>(A const &a);
};

template <class T>
double f(A<T> const &a) { return a.p_; }

int main()
{
    A<int> a;
    f(a);
}