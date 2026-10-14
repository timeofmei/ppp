#include "PPP.h"

class Date {
public:
    Date(int y, int m, int d);
    void add_day(int n);
    int month() { return m; }
    int day() { return d; }
    int year() { return y; }
private:
    int y, m, d;
};

Date::Date(int yy, int mm, int dd)
    :y{yy}, m{mm}, d{dd}
{}

void Date::add_day(int n)
{}

ostream& operator<<(ostream& os, Date d)
{
    return os << d.year() << '/' << d.month() << '/' << d.day();
}

int main()
{
    Date today {2026, 10, 14};
    cout << "Today: " << today << '\n';
}