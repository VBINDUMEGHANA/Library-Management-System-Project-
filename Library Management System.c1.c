#include <iostream>
#include <vector>
#include <algorithm>

class Book {
public:
    Book(int book_id, std::string title, std::string author, bool available = true)
        : book_id(book_id), title(title), author(author), available(available) {}

    int getBookID() const {
        return book_id;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool availability) {
        available = availability;
    }

private:
    int book_id;
    std::string title;
    std::string author;
    bool available;
};

class Library {
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(int book_id) {
        books.erase(std::remove_if(books.begin(), books.end(), [book_id](const Book& book) {
            return book.getBookID() == book_id;
        }), books.end());
    }

    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library." << std::endl;
        } else {
            std::cout << "Books in the library:" << std::endl;
            for (const Book& book : books) {
                std::cout << "Book ID: " << book.getBookID()
                          << ", Title: " << book.getTitle()
                          << ", Author: " << book.getAuthor()
                          << ", Available: " << (book.isAvailable() ? "Yes" : "No")
                          << std::endl;
            }
        }
    }

    const Book* findBook(int book_id) const {
        auto it = std::find_if(books.begin(), books.end(), [book_id](const Book& book) {
            return book.getBookID() == book_id;
        });

        if (it != books.end()) {
            return &(*it);
        }

        return nullptr;
    }

    void checkoutBook(int book_id) {
        Book* book = const_cast<Book*>(findBook(book_id));
        if (book != nullptr) {
            if (book->isAvailable()) {
                book->setAvailable(false);
                std::cout << "Book '" << book->getTitle() << "' has been checked out." << std::endl;
            } else {
                std::cout << "Book '" << book->getTitle() << "' is not available." << std::endl;
            }
        } else {
            std::cout << "Book not found in the library." << std::endl;
        }
    }

    void returnBook(int book_id) {
        Book* book = const_cast<Book*>(findBook(book_id));
        if (book != nullptr) {
            if (!book->isAvailable()) {
                book->setAvailable(true);
                std::cout << "Book '" << book->getTitle() << "' has been returned." << std::endl;
            } else {
                std::cout << "This book is already in the library." << std::endl;
            }
        } else {
            std::cout << "Book not found in the library." << std::endl;
        }
    }

private:
    std::vector<Book> books;
};

int main() {
    Library library;

    // Adding books
    Book book1(1, "Harry Potter and the Sorcerer's Stone", "J.K. Rowling");
    Book book2(2, "To Kill a Mockingbird", "Harper Lee");
    Book book3(3, "1984", "George Orwell");
    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);

    // Displaying books
    library.displayBooks();

    // Checking out a book
    library.checkoutBook(2);

    // Displaying books after checkout
    library.displayBooks();

    // Returning a book
    library.returnBook(2);

    // Displaying books after return
    library.displayBooks();

    return 0;
}
