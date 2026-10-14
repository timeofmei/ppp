#include <regex>
#include "PPP.h"

class Book {
public:
    Book(string isbn, string t, string a, string cd, bool ico)
        :ISBN{isbn}, title{t}, author{a}, copyright_date{cd}, is_checked_out{ico}
    {
        if (!is_valid())
            error("Invalid book");
    }

    bool is_valid()
    {
        return regex_match(ISBN, regex{"(\\d+-\\d+-\\d+-[A-Za-z0-9])"}) && title != "" && author != "" && copyright_date != "";
    }

    void check_in() { is_checked_out = false; }

    void check_out() { is_checked_out = true; }

    string get_ISBN() { return ISBN; }

    string get_title() { return title; }

    string get_author() { return author; }

    string get_copyright_date() { return copyright_date; }

    bool get_is_checked_out() { return is_checked_out; }

private:
    string ISBN;
    string title;
    string author;
    string copyright_date;
    bool is_checked_out;
};