#include <regex>
#include "PPP.h"

enum class Genre {
    fiction, nonfiction, periodical, biography, children
};

vector<string> genre_tbl = {"fiction", "nonfiction", "periodical", "biography", "children" };

int to_int(Genre g)
{
    return static_cast<int>(g);
}

class Patron {
public:
    Patron(string n, string lcn)
        :name{n}, library_card_number{lcn}, library_fee{0.0}
    {}

    string get_name() { return name; }

    string get_library_card_number() { return library_card_number; }

    double get_library_fee() { return library_fee; }

    void set_library_fee(double fee) { library_fee = fee; }

private:
    string name;
    string library_card_number;
    double library_fee;
};

bool is_fee_owed(Patron patron)
{
    return patron.get_library_fee() != 0.0;
}

class Book {
public:
    Book(string isbn, string t, string a, string cd, bool ico, Genre g)
        :ISBN{isbn}, title{t}, author{a}, copyright_date{cd}, is_checked_out{ico}, genre{g}
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

    string get_genre() { return genre_tbl[to_int(genre)]; }

    bool get_is_checked_out() { return is_checked_out; }

private:
    string ISBN;
    string title;
    string author;
    string copyright_date;
    bool is_checked_out;
    Genre genre;
};

bool operator==(Book book1, Book book2)
{
    return book1.get_ISBN() == book2.get_ISBN();
}

bool operator!=(Book book1, Book book2)
{
    return book1.get_ISBN() != book2.get_ISBN();
}

ostream& operator<<(ostream& os, Book book)
{
    os << "Title: " << book.get_title() << '\n'
       << "Author: " << book.get_author() << '\n'
       << "ISBN: " << book.get_ISBN() << '\n';
    return os;
}