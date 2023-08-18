//NIKAZE INANGORORE Clarat Kim 222020823
//ISHIMWE Stacy Agray 222005937
//IZERE BUGINGO Vainqueur Beryl 222019837


#include <iostream>
#include <vector>
using namespace std;

class Book {
private:
    string ISBN;
    string Title;
    string Author;
    int CopyrightDate;
    bool CheckedOut;
    enum Genre { Fiction, NonFiction, Periodical, Biography, Children };
    Genre bookGenre;

public:
    Book(string isbn, string title, string author, int copyright_date, Genre genre)
        : ISBN(isbn), Title(title), Author(author), CopyrightDate(copyright_date), CheckedOut(false), bookGenre(genre) {}

    string getISBN() const { return ISBN; }
    string getTitle() const { return Title; }
    string getAuthor() const { return Author; }
    bool isCheckedOut() const { return CheckedOut; }
    Genre getGenre() const { return bookGenre; }

    void checkOut() { CheckedOut = true; }
    void checkIn() { CheckedOut = false; }

    bool operator==(const Book& other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& os, const Book& book);
};

ostream& operator<<(ostream& os, const Book& book) {
    os << "Title: " << book.Title << endl;
    os << "Author: " << book.Author << endl;
    os << "ISBN: " << book.ISBN << endl;
    os << "Genre: ";
    switch (book.bookGenre) {
        case Book::Fiction:
            os << "Fiction";
            break;
        case Book::NonFiction:
            os << "NonFiction";
            break;
        case Book::Periodical:
            os << "Periodical";
            break;
        case Book::Biography:
            os << "Biography";
            break;
        case Book::Children:
            os << "Children";
            break;
    }
    os << endl;
    return os;
}

class Patron {
private:
    string UserName;
    string CardNumber;
    int OwedFees;

public:
    Patron(string username, string card_number) : UserName(username), CardNumber(card_number), OwedFees(0) {}

    string getUserName() const { return UserName; }
    string getCardNumber() const { return CardNumber; }
    int getOwedFees() const { return OwedFees; }

    bool owesFees() const { return OwedFees > 0; }
    void setFees(int fees) { OwedFees = fees; }
};

class Transaction {
private:
    Book book;
    Patron patron;
    string Activity;
    string Date;

public:
    Transaction(const Book& b, const Patron& p, string activity, string date)
        : book(b), patron(p), Activity(activity), Date(date) {}
};

class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book) { books.push_back(book); }
    void addPatron(const Patron& patron) { patrons.push_back(patron); }
    void addTransaction(const Transaction& transaction) { transactions.push_back(transaction); }

    vector<string> getPatronsWithFees() {
        vector<string> patrons_with_fees;
        for (const Patron& patron : patrons) {
            if (patron.owesFees()) {
                patrons_with_fees.push_back(patron.getUserName());
            }
        }
        return patrons_with_fees;
    }
};

int main() {
    // Sample usage of the classes
    Book book1("978-0743273565", "To Kill a Mockingbird", "Harper Lee", 1960, Book::Fiction);
    Book book2("978-0307474278", "1984", "George Orwell", 1949, Book::Fiction);
    Patron patron1("John Doe", "123456");
    Patron patron2("Jane Smith", "654321");
    Transaction transaction1(book1, patron1, "Check Out", "2023-08-01");
    Transaction transaction2(book2, patron2, "Check In", "2023-08-02");

    Library library;
    library.addBook(book1);
    library.addBook(book2);
    library.addPatron(patron1);
    library.addPatron(patron2);
    library.addTransaction(transaction1);
    library.addTransaction(transaction2);

    cout << "Books in the library:" << endl;
    for (const Book& book : library.books) {
        cout << book << endl;
    }

    cout << "Patrons with fees:" << endl;
    vector<string> patrons_with_fees = library.getPatronsWithFees();
    for (const string& patron : patrons_with_fees) {
        cout << patron << endl;
    }

    return 0;

