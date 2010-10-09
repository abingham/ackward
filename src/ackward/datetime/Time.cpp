#include <ackward/datetime/Time.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/GetClass.hpp>
#include <ackward/datetime/TimeDelta.hpp>

namespace ackward { namespace datetime
{

#include <ackward/datetime/Time_akw.ipp>

Time Time::replace(unsigned int h,
                   unsigned int m,
                   unsigned int s,
                   unsigned int ms) const
{
    if (h == 0) h = hour();
    if (m == 0) m = minute();
    if (s == 0) s = second();
    if (ms == 0) ms = microsecond();

    return _replace(h, m, s, ms);
}

bool Time::operator<(const Time& other) const
{
    try {
        return obj() < other.obj();
    } TRANSLATE_PYTHON_EXCEPTION();
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return lhs.obj() == rhs.obj();
}

std::ostream& operator<<(std::ostream& os, const Time& t)
{
    os << t.isoformat();
    return os;
}

}}
