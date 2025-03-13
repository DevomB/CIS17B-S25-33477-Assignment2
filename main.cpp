#include <iostream>
#include <vector>
#include <memory>
#include <map>

using namespace std;

class Book {
public:
    string title, author, isbn;
    bool available;
    
    Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true) {}
};

class User {
public:
    static int nextID;
    int userID;
    string name;
    vector<Book*> borrowedBooks;
    
    User(string n) : name(n), userID(nextID++) {}
    virtual string getType() = 0;
};
int User::nextID = 0;

class Student : public User {
public:
    Student(string n) : User(n) {}
    string getType() override { return "Student"; }
};

class Faculty : public User {
public:
    Faculty(string n) : User(n) {}
    string getType() override { return "Faculty"; }
};

class Library {
private:
    static Library* instance;
    Library() {}
    map<int, unique_ptr<User>> users;
    vector<unique_ptr<Book>> books;

public:
    static Library* getInstance() {
        if (!instance) instance = new Library();
        return instance;
    }
    
    void addBook(string title, string author, string isbn) {
        books.emplace_back(make_unique<Book>(title, author, isbn));
        cout << "Book Added.\n";
    }
    
    void addUser(string name, int type) {
        if (type == 1)
            users.emplace(User::nextID, make_unique<Student>(name));
        else if (type == 2)
            users.emplace(User::nextID, make_unique<Faculty>(name));
        cout << "User Added with ID " << User::nextID - 1 << "\n";
    }
    
    void borrowBook(string title, int userID) {
        auto userIt = users.find(userID);
        if (userIt == users.end()) { cout << "!! Error: No User with that ID Exists !!\n"; return; }
        for (auto& book : books) {
            if (book->title == title && book->available) {
                book->available = false;
                userIt->second->borrowedBooks.push_back(book.get());    
                cout << "Book checked out by User " << userID << "\n";
                return;
            }
        }
        cout << "!! Error: No book with that title exists or is unavailable !!\n";
    }
    
    void returnBook(string title, int userID) {
        auto userIt = users.find(userID);
        if (userIt == users.end()) { cout << "!! Error: No User with that ID Exists !!\n"; return; }
        for (auto it = userIt->second->borrowedBooks.begin(); it != userIt->second->borrowedBooks.end(); ++it) {
            if ((*it)->title == title) {
                (*it)->available = true;
                userIt->second->borrowedBooks.erase(it);
                cout << "Book returned.\n";
                return;
            }
        }
        cout << "!! Error: Book not borrowed by user !!\n";
    }
    
    void listBooks() {
        cout << "\nList of Books:\n";
        for (const auto& book : books)
            cout << "- " << book->title << " (" << (book->available ? "Available" : "Checked Out") << ")\n";
    }
    
    void listUsers() {
        cout << "\nList of Users:\n";
        for (const auto& p : users) {
            cout << "User " << p.first << ": " << p.second->name << " (" << p.second->getType() << ")\n";
            for (const auto& book : p.second->borrowedBooks)
                cout << "  - " << book->title << "\n";
        }
    }
};
Library* Library::instance = nullptr;

int main() {
    Library* lib = Library::getInstance();
    int choice;
    do {
        cout << "\n1. Manage Books\n2. Manage Users\n3. Manage Transactions\n4. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "1. Add Book\n2. List Books\nEnter choice: ";
            int bookChoice; cin >> bookChoice;
            if (bookChoice == 1) {
                string title, author, isbn;
                cout << "Enter Title: "; cin >> title;
                cout << "Enter Author: "; cin >> author;
                cout << "Enter ISBN: "; cin >> isbn;
                lib->addBook(title, author, isbn);
            } else if (bookChoice == 2) {
                lib->listBooks();
            }
        } else if (choice == 2) {
            cout << "1. Add User\n2. List Users\nEnter choice: ";
            int userChoice; cin >> userChoice;
            if (userChoice == 1) {
                string name;
                int type;
                cout << "Enter 1 for Student, 2 for Faculty: "; cin >> type;
                cout << "Enter Name: "; cin >> name;
                lib->addUser(name, type);
            } else if (userChoice == 2) {
                lib->listUsers();
            }
        } else if (choice == 3) {
            cout << "1. Borrow Book\n2. Return Book\nEnter choice: ";
            int transChoice; cin >> transChoice;
            if (transChoice == 1) {
                string title;
                int userID;
                cout << "Enter Book Title: "; cin >> title;
                cout << "Enter User ID: "; cin >> userID;
                lib->borrowBook(title, userID);
            } else if (transChoice == 2) {
                string title;
                int userID;
                cout << "Enter Book Title: "; cin >> title;
                cout << "Enter User ID: "; cin >> userID;
                lib->returnBook(title, userID);
            }
        }
    } while (choice != 4);
    cout << "Thank you for using the Library System!\n";
    return 0;
}
