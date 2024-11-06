Certainly! Here is a `README.md` file for your Library Management System project, which you can use on GitHub. This document covers all the essential details of the project.

---

# Library Management System

### Author: Sitender Narwal

## Project Overview
This Library Management System is a console-based application written in C++. It provides a simple yet functional interface for managing a library's book inventory, user accounts, and an admin panel with special permissions. Users can create accounts, borrow and return books, search for books, and view available books in the library. The admin panel allows for additional functionality, such as adding and deleting books and managing user accounts.

## Features
- **User Management**:
  - Allows users to create an account with a unique ID and password.
  - Allows users to log in and access library functionalities.
- **Book Management**:
  - Users can view all available books.
  - Users can borrow and return books, which updates the library's book list.
  - Admins can add or delete books in the library.
- **Admin Panel**:
  - Accessible with an admin password.
  - Provides control over library inventory and user management.

## Project Structure
The project is built with two main classes:

### 1. `Account` Class
- **Purpose**: Manages user information, including ID, name, and password.
- **Attributes**:
  - `id`: A unique identifier for each user.
  - `name`: User's name.
  - `books`: A set containing books borrowed by the user.
- **Functions**:
  - `authenticate`: Verifies if the entered password matches the account's password.

### 2. `Library` Class
- **Purpose**: Manages the library’s book inventory and user accounts.
- **Attributes**:
  - `books`: A set of all available books in the library.
  - `accounts`: An unordered map containing user accounts.
  - `adminPassword`: A hard-coded password for admin access.
- **Functions**:
  - `addBook`: Adds a new book to the library.
  - `addAccount`: Adds a new user account.
  - `deleteAccount`: Removes a user account from the library.
  - `borrow_books`: Allows users to borrow a book if it's available.
  - `return_books`: Allows users to return a borrowed book.
  - `display_books`: Shows all available books in the library.
  - `displayBorrowedBooks`: Displays the list of books borrowed by a user.
  - `searchBook`: Searches for books based on a partial name.
  - `adminPanel`: Provides the admin interface to add or delete books.

## Sample Code Snippets
### Adding a Book
```cpp
void addBook(string book) {
    books.insert(book);
    cout << "Book \"" << book << "\" added to the library." << endl;
}
```

### Borrowing a Book
```cpp
void borrow_books(string book, string account_name) {
    if (accounts.find(account_name) != accounts.end() && books.find(book) != books.end()) {
        accounts[account_name].books.insert(book);
        books.erase(book);
        cout << "Book \"" << book << "\" has been issued to " << account_name << endl;
    } else {
        cout << "Book or account not found, or book is already issued." << endl;
    }
}
```

### Returning a Book
```cpp
void return_books(string book, string account_name) {
    if (accounts.find(account_name) != accounts.end()) {
        accounts[account_name].books.erase(book);
        books.insert(book);
        cout << "Book \"" << book << "\" has been returned by " << account_name << endl;
    } else {
        cout << "Account not found." << endl;
    }
}
```

## Usage Instructions
1. **Compile the Program**:
   ```bash
   g++ -o LibraryManagementSystem main.cpp
   ```
2. **Run the Program**:
   ```bash
   ./LibraryManagementSystem
   ```
3. **Menu Options**:
   - **1. Add New Account**: Create a new user account with a unique ID and password.
   - **2. Login Existing Account**: Access the library system using your name and password.
   - **3. Admin Login**: Log in as an admin with the password to access advanced functionalities.
   - **0. Exit Library**: Exit the application.

## Admin Credentials
- Default admin password: **admin123**

## Example Walkthrough
1. Run the program.
2. Choose "Add New Account" to create a new user account.
3. Login with the created account, and choose "Borrow Book" to borrow an available book.
4. If you’re an admin, use the "Admin Login" option to add or delete books in the library.

## System Requirements
- C++ Compiler (e.g., GCC)
- Works on Windows, macOS, and Linux

## Additional Notes
- The project uses `unordered_map` and `set` from the C++ Standard Library for efficient data storage and retrieval.
- Cross-platform screen clearing (`cls` for Windows and `clear` for Linux/macOS) has been implemented.

---

Feel free to customize this `README.md` file for your repository and make any additional notes or modifications!
