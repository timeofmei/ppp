#include "PPP.h"

class Year {
public:
    Year(int yy)
        :y{yy}
    {}
    int year() const { return y; }
private:
    int y;
};

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
    class Invalid {};
    Date();
    Date(Year y, Month m, int d);
    Month month() const { return m; }
    int day() const { return d; }
    Year year() const { return y; }
    bool is_valid() const;
    void add_day(int n);
private:
    Year y {2001};
    Month m;
    int d;
};

Date::Date(Year yy, Month mm, int dd)
    :y{yy}, m{mm}, d{dd}
{
    if (!is_valid())
        throw Invalid{};
}

int to_int(Month m)
{
    return static_cast<int>(m);
}

bool Date::is_valid() const
{
    return 0 < to_int(m) && to_int(m) < 13 && 0 < d && d < 32;
}

void Date::add_day(int n) {
    d += n;
}

ostream& operator<<(ostream& os, Year y)
{
    return os << y.year();
}

ostream& operator<<(ostream& os, Month m)
{
    return os << to_int(m);
}

ostream& operator<<(ostream& os, Date d)
{
    return os << d.year() << '/' << d.month() << '/' << d.day();
}

int main()
{
    const Date today {Year {2020}, Month::feb, 2};
    Date tomorrow = today;
    tomorrow.add_day(1);
    cout << "Today: " << today << '\n';
    cout << "Tomorrow: " << tomorrow << '\n';
}