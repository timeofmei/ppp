#include "PPP.h"

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

int to_int(Month m)
{
    return static_cast<int>(m);
}

Month int_to_month(int x)
{
    if (x<to_int(Month::jan) || to_int(Month::dec)<x)
        error("Bad month");
    return Month{x};
}

Month operator++(Month& m)
{
    m = (m==Month::dec) ? Month::jan : Month{to_int(m)+1};
    return m;
}

vector<string> month_tbl = {"Not a month", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[to_int(m)];
}

int main()
{
    Month m = Month::oct;
    cout << "Month: " << m << '\n';
    for (int i = 0; i < 12; i++) {
        ++m;
        cout << "Next month: " << m << '\n';
    }
}