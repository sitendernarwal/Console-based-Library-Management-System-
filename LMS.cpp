#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <vector>
#include <limits>

#ifdef _WIN32
#define CLEAR "cls" // Windows command to clear screen
#else
#define CLEAR "clear" // Linux/macOS command to clear screen
#endif

using namespace std;

// Class representing a user's account in the library
class Account
{
    string password; // Account password, private to prevent unauthorized access
    static int id_counter; // Static counter to generate unique IDs for accounts

public:
    int id; // Unique ID for the account
    string name; // Name of the account holder
    set<string> books; // Set of books borrowed by the user

    // Default constructor
    Account() : id(0), name(""), password("") {}

    // Parameterized constructor to initialize account with name and password
    Account(string name, string password)
    {
        this->id = ++id_counter;
        this->name = name;
        this->password = password;
    }

    // Function to authenticate user by matching password
    bool authenticate(string password)
    {
        return this->password == password;
    }
};

// Initialize the static id counter to 0
int Account::id_counter = 0;

// Class representing the Library Management System
class Library
{
public:
    set<string> books; // Set of all available books in the library
    unordered_map<string, Account> accounts; // Map of account name to account object
    string adminPassword = "admin123"; // Default admin password for admin access

    // Function to add a new book to the library
    void addBook(string book)
    {
        books.insert(book);
    }

    // Function to add a new account to the library
    void addAccount(const Account &account)
    {
        accounts[account.name] = account;
    }

    // Function to delete an existing account by account name
    void deleteAccount(const string &account_name)
    {
        if (accounts.find(account_name) != accounts.end())
        {
            accounts.erase(account_name);
            cout << "Account \"" << account_name << "\" deleted successfully." << endl;
        }
        else
        {
            cout << "Account not found!" << endl;
        }
    }

    // Function to allow a user to borrow a book
    void borrow_books(string book, string account_name)
    {
        if (accounts.find(account_name) != accounts.end() && books.find(book) != books.end())
        {
            accounts[account_name].books.insert(book); // Add book to user's borrowed books
            cout << "Book \"" << book << "\" has been issued by " << account_name << endl;
            books.erase(book); // Remove book from library's available books
        }
        else
        {
            cout << "Book or account not found, or book is already issued." << endl;
        }
    }

    // Function to allow a user to return a borrowed book
    void return_books(string book, string account_name)
    {
        if (accounts.find(account_name) != accounts.end())
        {
            accounts[account_name].books.erase(book); // Remove book from user's borrowed books
            books.insert(book); // Add book back to the library's available books
            cout << "Book \"" << book << "\" has been returned by " << account_name << endl;
        }
        else
        {
            cout << "Account not found." << endl;
        }
    }

    // Function to display all available books in the library
    void display_books()
    {
        cout << "\nAvailable Books:\n-----------------\n";
        for (auto book : books)
        {
            cout << book << endl;
        }
        cout << "-----------------\n" << endl;

        // Pause for user input before clearing the screen
        cout << "Press Enter to return to the menu...";
        cin.get(); // Wait for Enter key
    }

    // Function to display books borrowed by a specific user
    void displayBorrowedBooks(const string &account_name)
    {
        if (accounts.find(account_name) != accounts.end())
        {
            cout << "\nBorrowed Books by " << account_name << ":\n-----------------\n";
            for (auto book : accounts[account_name].books)
            {
                cout << book << endl;
            }
            cout << "Press Enter to return to the menu...";
            cout << "-----------------\n";
            cin.get(); // Wait for Enter key
        }
        else
        {
            cout << "Account not found." << endl;
        }
    }

    // Function to search for books based on a partial name
    void searchBook(const string &partial_name)
    {
        cout << "\nSearch Results for \"" << partial_name << "\":\n-----------------\n";
        for (auto book : books)
        {
            if (book.find(partial_name) != string::npos)
            {
                cout << book << endl;
            }
        }
        cout << "-----------------\n";
        cout << "Press Enter to return to the menu...";
        cin.get(); // Wait for Enter key
    }

    // Admin panel for managing books in the library
    void adminPanel()
    {
        int choice;
        do
        {
            cout << "\n-- Admin Panel --\n1. Add New Book\n2. Delete Book\n3. Display Available Books\n0. Logout\nEnter choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1)
            {
                string book;
                cout << "Enter book name to add: ";
                getline(cin, book);
                addBook(book);
                cout << "Book \"" << book << "\" added to the library." << endl;
                system(CLEAR); // Clear screen after adding book
            }
            else if (choice == 2)
            {
                string book;
                cout << "Enter book name to delete: ";
                getline(cin, book);
                if (books.find(book) != books.end())
                {
                    books.erase(book);
                    cout << "Book \"" << book << "\" deleted from the library." << endl;
                }
                else
                {
                    cout << "Book not found in library!" << endl;
                }
                system(CLEAR); // Clear screen after deleting book
            }
            else if (choice == 3)
            {
                system(CLEAR);
                display_books();
            }
        } while (choice != 0);
        system(CLEAR); // Clear screen after admin logout
    }
};

int main()
{
    Library lib;

    // Initialize library with some books
    lib.addBook("Book1");
    lib.addBook("Book2");
    lib.addBook("Book3");
    lib.addBook("Book4");

    cout << "\n------------------- Welcome to the Library -------------------\n";
    while (1)
    {
        cout << "\n1. Add New Account\n2. Login Existing Account\n3. Admin Login\n0. Exit Library\nEnter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) // Exit the program
        {
            cout << "Thanks for using the Library!" << endl;
            break;
        }
        else if (choice == 1) // Create a new user account
        {
            string name, password, temp;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password (new password): ";
            cin >> password;
            cout << "Verify your password: ";
            cin >> temp;

            while (temp != password) // Password verification
            {
                cout << "Password didn't match. Please re-enter: ";
                cin >> temp;
            }

            Account newAccount(name, password);
            lib.addAccount(newAccount);
            cout << "Account created successfully." << endl;
            cout << "Your ID is " << newAccount.id << endl;
            system(CLEAR); // Clear screen after account creation
        }
        else if (choice == 2) // User login
        {
            string name, password;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;

            if (lib.accounts.find(name) != lib.accounts.end() && lib.accounts[name].authenticate(password))
            {
                cout << "Login successful!" << endl;
                system(CLEAR);
                int user_choice;
                do
                {
                    cout << "\n-- User Panel --\n1. Borrow Book\n2. Return Book\n3. Display Available Books\n4. View My Borrowed Books\n5. Search Book\n6. Delete My Account\n0. Logout\nEnter choice: ";
                    cin >> user_choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (user_choice == 1) // Borrow a book
                    {
                        string book;
                        cout << "Enter book name to borrow: ";
                        getline(cin, book);
                        lib.borrow_books(book, name);
                        system(CLEAR);
                    }
                    else if (user_choice == 2) // Return a book
                    {
                        string book;
                        cout << "Enter book name to return: ";
                        getline(cin, book);
                        lib.return_books(book, name);
                        system(CLEAR);
                    }
                    else if (user_choice == 3) // Display available books
                    {
                        system(CLEAR);
                        lib.display_books();
                        system(CLEAR);
                    }
                    else if (user_choice == 4) // View borrowed books
                    {
                        system(CLEAR);
                        lib.displayBorrowedBooks(name);
                        system(CLEAR);
                    }
                    else if (user_choice == 5) // Search for a book
                    {
                        string search_term;
                        cout << "Enter book name or part of it to search: ";
                        getline(cin, search_term);
                        lib.searchBook(search_term);
                        system(CLEAR);
                    }
                    else if (user_choice == 6) // Delete user's account
                    {
                        cout << "Are you sure you want to delete your account? (y/n): ";
                        char confirmation;
                        cin >> confirmation;
                        if (confirmation == 'y' || confirmation == 'Y')
                        {
                            lib.deleteAccount(name);
                            user_choice = 0; // Force logout after deletion
                        }
                    }
                } while (user_choice != 0);
                cout << "Logged out successfully.\n";
                system(CLEAR); // Clear screen after user logout
            }
            else
            {
                cout << "Incorrect username or password!" << endl;
            }
        }
        else if (choice == 3) // Admin login
        {
            string password;
            cout << "Enter admin password: ";
            cin >> password;

            if (password == lib.adminPassword)
            {
                cout << "Admin login successful!" << endl;
                lib.adminPanel();
                system(CLEAR); // Clear screen after exiting admin panel
            }
            else
            {
                cout << "Incorrect admin password!" << endl;
            }
        }
    }
    return 0;
}
