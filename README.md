# CIS17B-S25-33477-Assignment2

## Features

Manage Books: Add, edit, remove, and search for books by title or author.

Manage Users: Register students or faculty members, edit user details, and remove users.

Manage Transactions: Borrow and return books while handling errors such as unavailable books or unregistered users.

Command-Line Interface (CLI): Interactive menu for easy navigation and usage.

## Design Patterns Implemented

Singleton Pattern: Ensures a single instance of the Library class.

Factory Method: Used to dynamically create Book and User objects.

## Exception Handling

The system includes error handling for cases such as:

Attempting to borrow an unavailable book.

Returning a book that was never borrowed.

Entering invalid user inputs.

### Requirements

C++ compiler (e.g., g++, clang++)

Standard Template Library (STL)
