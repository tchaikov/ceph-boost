// https://www.boost.org/doc/libs/1_67_0/doc/html/chrono/users_guide.html#chrono.users_guide.examples

#include <boost/chrono.hpp>
#include <iostream>

namespace I_dont_like_the_default_duration_behavior
{

template <class R>
class zero_default
{
  public:
    typedef R rep;

  private:
    rep rep_;

  public:
    zero_default(rep i = 0) : rep_(i) {}
    operator rep() const { return rep_; }

    zero_default &operator+=(zero_default x)
    {
        rep_ += x.rep_;
        return *this;
    }
    zero_default &operator-=(zero_default x)
    {
        rep_ -= x.rep_;
        return *this;
    }
    zero_default &operator*=(zero_default x)
    {
        rep_ *= x.rep_;
        return *this;
    }
    zero_default &operator/=(zero_default x)
    {
        rep_ /= x.rep_;
        return *this;
    }

    zero_default operator+() const { return *this; }
    zero_default operator-() const { return zero_default(-rep_); }
    zero_default &operator++()
    {
        ++rep_;
        return *this;
    }
    zero_default operator++(int) { return zero_default(rep_++); }
    zero_default &operator--()
    {
        --rep_;
        return *this;
    }
    zero_default operator--(int) { return zero_default(rep_--); }

    friend zero_default operator+(zero_default x, zero_default y) { return x += y; }
    friend zero_default operator-(zero_default x, zero_default y) { return x -= y; }
    friend zero_default operator*(zero_default x, zero_default y) { return x *= y; }
    friend zero_default operator/(zero_default x, zero_default y) { return x /= y; }

    friend bool operator==(zero_default x, zero_default y) { return x.rep_ == y.rep_; }
    friend bool operator!=(zero_default x, zero_default y) { return !(x == y); }
    friend bool operator<(zero_default x, zero_default y) { return x.rep_ < y.rep_; }
    friend bool operator<=(zero_default x, zero_default y) { return !(y < x); }
    friend bool operator>(zero_default x, zero_default y) { return y < x; }
    friend bool operator>=(zero_default x, zero_default y) { return !(x < y); }
};

typedef boost::chrono::duration<zero_default<long long>, boost::nano> nanoseconds;
typedef boost::chrono::duration<zero_default<long long>, boost::micro> microseconds;
typedef boost::chrono::duration<zero_default<long long>, boost::milli> milliseconds;
typedef boost::chrono::duration<zero_default<long long>> seconds;
typedef boost::chrono::duration<zero_default<long long>, boost::ratio<60>> minutes;
typedef boost::chrono::duration<zero_default<long long>, boost::ratio<3600>> hours;
} // namespace I_dont_like_the_default_duration_behavior

int main()
{
    using namespace I_dont_like_the_default_duration_behavior;

    milliseconds ms;
    std::cout << ms.count() << '\n';
}