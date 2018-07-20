// https://www.boost.org/doc/libs/1_67_0/doc/html/atomic/usage_examples.html#boost_atomic.usage_examples.example_ringbuffer

#include <boost/chrono.hpp>
#include <boost/type_traits.hpp>

#include <iostream>

using namespace boost::chrono;

template <class To, class Rep, class Period>
To round_up(boost::chrono::duration<Rep, Period> d)
{
    To result = boost::chrono::duration_cast<To>(d);
    if (result < d)
        ++result;
    return result;
}

struct xtime
{
    long sec;
    unsigned long usec;
};

template <class Rep, class Period>
xtime to_xtime_truncate(boost::chrono::duration<Rep, Period> d)
{
    xtime xt;
    xt.sec = static_cast<long>(boost::chrono::duration_cast<seconds>(d).count());
    xt.usec = static_cast<long>(boost::chrono::duration_cast<microseconds>(d - seconds(xt.sec)).count());
    return xt;
}

template <class Rep, class Period>
xtime to_xtime_round_up(boost::chrono::duration<Rep, Period> d)
{
    xtime xt;
    xt.sec = static_cast<long>(boost::chrono::duration_cast<seconds>(d).count());
    xt.usec = static_cast<unsigned long>(round_up<boost::chrono::microseconds>(d - boost::chrono::seconds(xt.sec)).count());
    return xt;
}

microseconds
from_xtime(xtime xt)
{
    return boost::chrono::seconds(xt.sec) + boost::chrono::microseconds(xt.usec);
}

void print(xtime xt)
{
    std::cout << '{' << xt.sec << ',' << xt.usec << "}\n";
}

int main()
{
    xtime xt = to_xtime_truncate(seconds(3) + boost::chrono::milliseconds(251));
    print(xt);
    boost::chrono::milliseconds ms = boost::chrono::duration_cast<boost::chrono::milliseconds>(from_xtime(xt));
    std::cout << ms.count() << " milliseconds\n";
    xt = to_xtime_round_up(ms);
    print(xt);
    xt = to_xtime_truncate(boost::chrono::seconds(3) + nanoseconds(999));
    print(xt);
    xt = to_xtime_round_up(boost::chrono::seconds(3) + nanoseconds(999));
    print(xt);
}