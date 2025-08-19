// C++ Bookshop Management System
// Author: [Your Name]
// Description: A console-based bookshop management system using file handling

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#ifdef _WIN32
    #include <cstdlib>
#else
    #include <cstdlib>
    #define system(x) std::system(x)
#endif

using namespace std;

class BookShop {
private:
    const string filename = "data/book.txt";
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void pauseScreen() {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

public:
    void displayMenu();
    void addBook();
    void displayAllBooks();
    void searchBook();
    void updateBook();
    void deleteBook();
    void createDataDirectory();
};

// Create data directory if it doesn't exist
void BookShop::createDataDirectory() {
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
}

// Function to display the main menu
void BookShop::displayMenu() {
    clearScreen();
    cout << "\n" << string(60, '=') << endl;
    cout << "\t\t\tBOOKSHOP MANAGEMENT SYSTEM" << endl;
    cout << string(60, '=') << endl;
    cout << "\n\t1. ADD BOOK" << endl;
    cout << "\t2. DISPLAY ALL BOOKS" << endl;
    cout << "\t3. SEARCH BOOK" << endl;
    cout << "\t4. UPDATE BOOK" << endl;
    cout << "\t5. DELETE BOOK" << endl;
    cout << "\t6. EXIT" << endl;
    cout << "\n" << string(60, '=') << endl;
}

// Function to add a new book
void BookShop::addBook() {
    clearScreen();
    fstream file;
    string bookId, bookName, authorName;
    int numberOfCopies;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "\t\t\tADD NEW BOOK" << endl;
    cout << string(50, '=') << endl;
    
    cout << "\nEnter Book ID: ";
    cin >> bookId;
    cin.ignore(); // Clear input buffer
    
    cout << "Enter Book Name: ";
    getline(cin, bookName);
    
    cout << "Enter Author Name: ";
    getline(cin, authorName);
    
    cout << "Enter Number of Copies: ";
    cin >> numberOfCopies;
    
    // Replace spaces with underscores for file storage
    for(char &c : bookName) if(c == ' ') c = '_';
    for(char &c : authorName) if(c == ' ') c = '_';
    
    // Open file in append mode
    file.open(filename, ios::out | ios::app);
    if(file.is_open()) {
        file << bookId << " " << bookName << " " << authorName << " " << numberOfCopies << "\n";
        file.close();
        cout << "\n✓ Book added successfully!" << endl;
    } else {
        cout << "\n✗ Error: Could not open file for writing!" << endl;
    }
    
    pauseScreen();
}

// Function to display all books
void BookShop::displayAllBooks() {
    clearScreen();
    fstream file;
    string bookId, bookName, authorName;
    int numberOfCopies;
    bool hasBooks = false;
    
    cout << "\n" << string(80, '=') << endl;
    cout << "\t\t\t\tALL BOOKS IN INVENTORY" << endl;
    cout << string(80, '=') << endl;
    
    file.open(filename, ios::in);
    if(!file) {
        cout << "\n✗ Error: Could not open file or no books found!" << endl;
        pauseScreen();
        return;
    }
    
    cout << "\n" << left << setw(10) << "Book ID" 
         << setw(25) << "Book Name" 
         << setw(20) << "Author" 
         << setw(10) << "Copies" << endl;
    cout << string(65, '-') << endl;
    
    while(file >> bookId >> bookName >> authorName >> numberOfCopies) {
        // Replace underscores with spaces for display
        for(char &c : bookName) if(c == '_') c = ' ';
        for(char &c : authorName) if(c == '_') c = ' ';
        
        cout << left << setw(10) << bookId 
             << setw(25) << bookName 
             << setw(20) << authorName 
             << setw(10) << numberOfCopies << endl;
        hasBooks = true;
    }
    
    file.close();
    
    if(!hasBooks) {
        cout << "\nNo books found in inventory." << endl;
    }
    
    pauseScreen();
}

// Function to search for a specific book
void BookShop::searchBook() {
    clearScreen();
    fstream file;
    string bookId, bookName, authorName, searchId;
    int numberOfCopies;
    bool found = false;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "\t\t\tSEARCH BOOK" << endl;
    cout << string(50, '=') << endl;
    
    file.open(filename, ios::in);
    if(!file) {
        cout << "\n✗ Error: Could not open file!" << endl;
        pauseScreen();
        return;
    }
    
    cout << "\nEnter Book ID to search: ";
    cin >> searchId;
    
    while(file >> bookId >> bookName >> authorName >> numberOfCopies) {
        if(searchId == bookId) {
            clearScreen();
            cout << "\n" << string(50, '=') << endl;
            cout << "\t\t\tBOOK FOUND!" << endl;
            cout << string(50, '=') << endl;
            
            // Replace underscores with spaces for display
            for(char &c : bookName) if(c == '_') c = ' ';
            for(char &c : authorName) if(c == '_') c = ' ';
            
            cout << "\nBook ID: " << bookId << endl;
            cout << "Book Name: " << bookName << endl;
            cout << "Author: " << authorName << endl;
            cout << "Number of Copies: " << numberOfCopies << endl;
            found = true;
            break;
        }
    }
    
    file.close();
    
    if(!found) {
        cout << "\n✗ Book with ID '" << searchId << "' not found!" << endl;
    }
    
    pauseScreen();
}

// Function to update book information
void BookShop::updateBook() {
    clearScreen();
    fstream file, tempFile;
    string bookId, bookName, authorName, searchId;
    string newBookName, newAuthorName;
    int numberOfCopies, newCopies;
    bool found = false;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "\t\t\tUPDATE BOOK" << endl;
    cout << string(50, '=') << endl;
    
    file.open(filename, ios::in);
    tempFile.open("data/temp.txt", ios::out);
    
    if(!file) {
        cout << "\n✗ Error: Could not open file!" << endl;
        pauseScreen();
        return;
    }
    
    cout << "\nEnter Book ID to update: ";
    cin >> searchId;
    cin.ignore();
    
    while(file >> bookId >> bookName >> authorName >> numberOfCopies) {
        if(searchId == bookId) {
            cout << "\nBook found! Enter new details:" << endl;
            cout << "New Book Name: ";
            getline(cin, newBookName);
            cout << "New Author Name: ";
            getline(cin, newAuthorName);
            cout << "New Number of Copies: ";
            cin >> newCopies;
            
            // Replace spaces with underscores for file storage
            for(char &c : newBookName) if(c == ' ') c = '_';
            for(char &c : newAuthorName) if(c == ' ') c = '_';
            
            tempFile << bookId << " " << newBookName << " " << newAuthorName << " " << newCopies << "\n";
            found = true;
            cout << "\n✓ Book updated successfully!" << endl;
        } else {
            tempFile << bookId << " " << bookName << " " << authorName << " " << numberOfCopies << "\n";
        }
    }
    
    file.close();
    tempFile.close();
    
    if(found) {
        remove(filename.c_str());
        rename("data/temp.txt", filename.c_str());
    } else {
        remove("data/temp.txt");
        cout << "\n✗ Book with ID '" << searchId << "' not found!" << endl;
    }
    
    pauseScreen();
}

// Function to delete a book
void BookShop::deleteBook() {
    clearScreen();
    fstream file, tempFile;
    string bookId, bookName, authorName, searchId;
    int numberOfCopies;
    bool found = false;
    
    cout << "\n" << string(50, '=') << endl;
    cout << "\t\t\tDELETE BOOK" << endl;
    cout << string(50, '=') << endl;
    
    file.open(filename, ios::in);
    tempFile.open("data/temp.txt", ios::out);
    
    if(!file) {
        cout << "\n✗ Error: Could not open file!" << endl;
        pauseScreen();
        return;
    }
    
    cout << "\nEnter Book ID to delete: ";
    cin >> searchId;
    
    while(file >> bookId >> bookName >> authorName >> numberOfCopies) {
        if(searchId == bookId) {
            found = true;
            cout << "\n✓ Book with ID '" << searchId << "' deleted successfully!" << endl;
            // Don't write this record to temp file (effectively deleting it)
        } else {
            tempFile << bookId << " " << bookName << " " << authorName << " " << numberOfCopies << "\n";
        }
    }
    
    file.close();
    tempFile.close();
    
    if(found) {
        remove(filename.c_str());
        rename("data/temp.txt", filename.c_str());
    } else {
        remove("data/temp.txt");
        cout << "\n✗ Book with ID '" << searchId << "' not found!" << endl;
    }
    
    pauseScreen();
}

// Main function
int main() {
    BookShop bookshop;
    int choice;
    
    // Create data directory
    bookshop.createDataDirectory();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "\t\tWELCOME TO BOOKSHOP MANAGEMENT SYSTEM" << endl;
    cout << string(60, '=') << endl;
    
    while(true) {
        bookshop.displayMenu();
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                bookshop.addBook();
                break;
            case 2:
                bookshop.displayAllBooks();
                break;
            case 3:
                bookshop.searchBook();
                break;
            case 4:
                bookshop.updateBook();
                break;
            case 5:
                bookshop.deleteBook();
                break;
            case 6:
                cout << "\n✓ Thank you for using Bookshop Management System!" << endl;
                cout << "Goodbye!" << endl;
                exit(0);
            default:
                cout << "\n✗ Invalid choice! Please enter a number between 1-6." << endl;
                bookshop.createDataDirectory(); // Just to pause
                #ifdef _WIN32
                    system("pause");
                #else
                    system("read -p 'Press Enter to continue...' var");
                #endif
        }
    }
    
    return 0;
}
