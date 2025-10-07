#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure Definitions
typedef struct {
    int book_id;
    char title[100];
    int author_id;
    int publisher_id;
    char isbn[20];
    char genre[50];
    int year_published;
    int copies_available;
    char shelf_location[20];
} Book;

typedef struct {
    int author_id;
    char name[100];
    char bio[500];
} Author;

typedef struct {
    int publisher_id;
    char name[100];
    char address[200];
    char contact_info[100];
} Publisher;

typedef struct {
    int member_id;
    char name[100];
    char address[200];
    char phone[20];
    char email[100];
    char date_joined[11];
    char membership_status[20];
} Member;

typedef struct {
    int staff_id;
    char name[100];
    char role[50];
    char email[100];
    char phone[20];
} Staff;

typedef struct {
    int borrowing_id;
    int book_id;
    int member_id;
    char borrow_date[11];
    char due_date[11];
    char return_date[11];
    int staff_id;
} Borrowing;

typedef struct {
    int fine_id;
    int borrowing_id;
    float amount;
    int paid;
    char date_paid[11];
} Fine;

// File names
#define BOOKS_FILE "books.dat"
#define AUTHORS_FILE "authors.dat"
#define PUBLISHERS_FILE "publishers.dat"
#define MEMBERS_FILE "members.dat"
#define STAFF_FILE "staff.dat"
#define BORROWINGS_FILE "borrowings.dat"
#define FINES_FILE "fines.dat"

// Function prototypes
void mainMenu();
void bookMenu();
void authorMenu();
void publisherMenu();
void memberMenu();
void staffMenu();
void borrowingMenu();
void fineMenu();

// Book functions
void addBook();
void viewBooks();
void updateBook();
void deleteBook();
void searchBook();

// Author functions
void addAuthor();
void viewAuthors();
void updateAuthor();
void deleteAuthor();

// Publisher functions
void addPublisher();
void viewPublishers();
void updatePublisher();
void deletePublisher();

// Member functions
void addMember();
void viewMembers();
void updateMember();
void deleteMember();

// Staff functions
void addStaff();
void viewStaff();
void updateStaff();
void deleteStaff();

// Borrowing functions
void borrowBook();
void returnBook();
void viewBorrowings();

// Fine functions
void addFine();
void viewFines();
void payFine();

// Utility functions
int getNextId(const char* filename, size_t recordSize);
void getCurrentDate(char* date);
void clearScreen();
void pressEnterToContinue();

int main() {
    printf("=== Library Management System ===\n");
    printf("Welcome to the Academic Institution Library\n\n");
    
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n=== MAIN MENU ===\n");
        printf("1. Book Management\n");
        printf("2. Author Management\n");
        printf("3. Publisher Management\n");
        printf("4. Member Management\n");
        printf("5. Staff Management\n");
        printf("6. Borrowing Management\n");
        printf("7. Fine Management\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: bookMenu(); break;
            case 2: authorMenu(); break;
            case 3: publisherMenu(); break;
            case 4: memberMenu(); break;
            case 5: staffMenu(); break;
            case 6: borrowingMenu(); break;
            case 7: fineMenu(); break;
            case 0: 
                printf("Thank you for using Library Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void bookMenu() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n=== BOOK MANAGEMENT ===\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 0: return;
            default:
                printf("Invalid choice! Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void addBook() {
    Book book;
    FILE *file;
    
    clearScreen();
    printf("\n=== ADD NEW BOOK ===\n");
    
    book.book_id = getNextId(BOOKS_FILE, sizeof(Book));
    
    printf("Enter book title: ");
    getchar(); // consume newline
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = 0; // remove newline
    
    printf("Enter author ID: ");
    scanf("%d", &book.author_id);
    
    printf("Enter publisher ID: ");
    scanf("%d", &book.publisher_id);
    
    printf("Enter ISBN: ");
    getchar();
    fgets(book.isbn, sizeof(book.isbn), stdin);
    book.isbn[strcspn(book.isbn, "\n")] = 0;
    
    printf("Enter genre: ");
    fgets(book.genre, sizeof(book.genre), stdin);
    book.genre[strcspn(book.genre, "\n")] = 0;
    
    printf("Enter year published: ");
    scanf("%d", &book.year_published);
    
    printf("Enter copies available: ");
    scanf("%d", &book.copies_available);
    
    printf("Enter shelf location: ");
    getchar();
    fgets(book.shelf_location, sizeof(book.shelf_location), stdin);
    book.shelf_location[strcspn(book.shelf_location, "\n")] = 0;
    
    file = fopen(BOOKS_FILE, "ab");
    if(file != NULL) {
        fwrite(&book, sizeof(Book), 1, file);
        fclose(file);
        printf("\nBook added successfully! Book ID: %d\n", book.book_id);
    } else {
        printf("Error: Could not save book!\n");
    }
    
    pressEnterToContinue();
}

void viewBooks() {
    Book book;
    FILE *file;
    int found = 0;
    
    clearScreen();
    printf("\n=== ALL BOOKS ===\n");
    printf("%-5s %-30s %-10s %-12s %-20s %-15s %-6s %-8s %-15s\n", 
           "ID", "Title", "Author ID", "Publisher ID", "ISBN", "Genre", "Year", "Copies", "Shelf");
    printf("---------------------------------------------------------------------------------------------\n");
    
    file = fopen(BOOKS_FILE, "rb");
    if(file != NULL) {
        while(fread(&book, sizeof(Book), 1, file)) {
            printf("%-5d %-30s %-10d %-12d %-20s %-15s %-6d %-8d %-15s\n",
                   book.book_id, book.title, book.author_id, book.publisher_id,
                   book.isbn, book.genre, book.year_published, book.copies_available,
                   book.shelf_location);
            found = 1;
        }
        fclose(file);
    }
    
    if(!found) {
        printf("No books found!\n");
    }
    
    pressEnterToContinue();
}

void searchBook() {
    Book book;
    FILE *file;
    char searchTitle[100];
    int found = 0;
    
    clearScreen();
    printf("\n=== SEARCH BOOK ===\n");
    printf("Enter book title to search: ");
    getchar();
    fgets(searchTitle, sizeof(searchTitle), stdin);
    searchTitle[strcspn(searchTitle, "\n")] = 0;
    
    file = fopen(BOOKS_FILE, "rb");
    if(file != NULL) {
        printf("\n--- Search Results ---\n");
        while(fread(&book, sizeof(Book), 1, file)) {
            if(strstr(book.title, searchTitle) != NULL) {
                printf("Book ID: %d\n", book.book_id);
                printf("Title: %s\n", book.title);
                printf("Author ID: %d\n", book.author_id);
                printf("Publisher ID: %d\n", book.publisher_id);
                printf("ISBN: %s\n", book.isbn);
                printf("Genre: %s\n", book.genre);
                printf("Year Published: %d\n", book.year_published);
                printf("Copies Available: %d\n", book.copies_available);
                printf("Shelf Location: %s\n", book.shelf_location);
                printf("------------------------\n");
                found = 1;
            }
        }
        fclose(file);
    }
    
    if(!found) {
        printf("No books found matching '%s'!\n", searchTitle);
    }
    
    pressEnterToContinue();
}

void authorMenu() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n=== AUTHOR MANAGEMENT ===\n");
        printf("1. Add Author\n");
        printf("2. View All Authors\n");
        printf("3. Update Author\n");
        printf("4. Delete Author\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addAuthor(); break;
            case 2: viewAuthors(); break;
            case 3: updateAuthor(); break;
            case 4: deleteAuthor(); break;
            case 0: return;
            default:
                printf("Invalid choice! Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void addAuthor() {
    Author author;
    FILE *file;
    
    clearScreen();
    printf("\n=== ADD NEW AUTHOR ===\n");
    
    author.author_id = getNextId(AUTHORS_FILE, sizeof(Author));
    
    printf("Enter author name: ");
    getchar();
    fgets(author.name, sizeof(author.name), stdin);
    author.name[strcspn(author.name, "\n")] = 0;
    
    printf("Enter author bio: ");
    fgets(author.bio, sizeof(author.bio), stdin);
    author.bio[strcspn(author.bio, "\n")] = 0;
    
    file = fopen(AUTHORS_FILE, "ab");
    if(file != NULL) {
        fwrite(&author, sizeof(Author), 1, file);
        fclose(file);
        printf("\nAuthor added successfully! Author ID: %d\n", author.author_id);
    } else {
        printf("Error: Could not save author!\n");
    }
    
    pressEnterToContinue();
}

void viewAuthors() {
    Author author;
    FILE *file;
    int found = 0;
    
    clearScreen();
    printf("\n=== ALL AUTHORS ===\n");
    printf("%-5s %-30s %-50s\n", "ID", "Name", "Bio");
    printf("---------------------------------------------------------------------------------------------\n");
    
    file = fopen(AUTHORS_FILE, "rb");
    if(file != NULL) {
        while(fread(&author, sizeof(Author), 1, file)) {
            printf("%-5d %-30s %-50s\n", author.author_id, author.name, author.bio);
            found = 1;
        }
        fclose(file);
    }
    
    if(!found) {
        printf("No authors found!\n");
    }
    
    pressEnterToContinue();
}

void memberMenu() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n=== MEMBER MANAGEMENT ===\n");
        printf("1. Add Member\n");
        printf("2. View All Members\n");
        printf("3. Update Member\n");
        printf("4. Delete Member\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: addMember(); break;
            case 2: viewMembers(); break;
            case 3: updateMember(); break;
            case 4: deleteMember(); break;
            case 0: return;
            default:
                printf("Invalid choice! Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void addMember() {
    Member member;
    FILE *file;
    
    clearScreen();
    printf("\n=== ADD NEW MEMBER ===\n");
    
    member.member_id = getNextId(MEMBERS_FILE, sizeof(Member));
    
    printf("Enter member name: ");
    getchar();
    fgets(member.name, sizeof(member.name), stdin);
    member.name[strcspn(member.name, "\n")] = 0;
    
    printf("Enter address: ");
    fgets(member.address, sizeof(member.address), stdin);
    member.address[strcspn(member.address, "\n")] = 0;
    
    printf("Enter phone: ");
    fgets(member.phone, sizeof(member.phone), stdin);
    member.phone[strcspn(member.phone, "\n")] = 0;
    
    printf("Enter email: ");
    fgets(member.email, sizeof(member.email), stdin);
    member.email[strcspn(member.email, "\n")] = 0;
    
    getCurrentDate(member.date_joined);
    
    printf("Enter membership status (Active/Inactive): ");
    fgets(member.membership_status, sizeof(member.membership_status), stdin);
    member.membership_status[strcspn(member.membership_status, "\n")] = 0;
    
    file = fopen(MEMBERS_FILE, "ab");
    if(file != NULL) {
        fwrite(&member, sizeof(Member), 1, file);
        fclose(file);
        printf("\nMember added successfully! Member ID: %d\n", member.member_id);
    } else {
        printf("Error: Could not save member!\n");
    }
    
    pressEnterToContinue();
}

void viewMembers() {
    Member member;
    FILE *file;
    int found = 0;
    
    clearScreen();
    printf("\n=== ALL MEMBERS ===\n");
    printf("%-5s %-25s %-30s %-15s %-25s %-12s %-12s\n", 
           "ID", "Name", "Address", "Phone", "Email", "Date Joined", "Status");
    printf("---------------------------------------------------------------------------------------------\n");
    
    file = fopen(MEMBERS_FILE, "rb");
    if(file != NULL) {
        while(fread(&member, sizeof(Member), 1, file)) {
            printf("%-5d %-25s %-30s %-15s %-25s %-12s %-12s\n",
                   member.member_id, member.name, member.address, member.phone,
                   member.email, member.date_joined, member.membership_status);
            found = 1;
        }
        fclose(file);
    }
    
    if(!found) {
        printf("No members found!\n");
    }
    
    pressEnterToContinue();
}

void borrowingMenu() {
    int choice;
    
    while(1) {
        clearScreen();
        printf("\n=== BORROWING MANAGEMENT ===\n");
        printf("1. Borrow Book\n");
        printf("2. Return Book\n");
        printf("3. View All Borrowings\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: borrowBook(); break;
            case 2: returnBook(); break;
            case 3: viewBorrowings(); break;
            case 0: return;
            default:
                printf("Invalid choice! Please try again.\n");
                pressEnterToContinue();
        }
    }
}

void borrowBook() {
    Borrowing borrowing;
    FILE *file;
    
    clearScreen();
    printf("\n=== BORROW BOOK ===\n");
    
    borrowing.borrowing_id = getNextId(BORROWINGS_FILE, sizeof(Borrowing));
    
    printf("Enter book ID: ");
    scanf("%d", &borrowing.book_id);
    
    printf("Enter member ID: ");
    scanf("%d", &borrowing.member_id);
    
    printf("Enter staff ID: ");
    scanf("%d", &borrowing.staff_id);
    
    getCurrentDate(borrowing.borrow_date);
    
    printf("Enter due date (YYYY-MM-DD): ");
    getchar();
    fgets(borrowing.due_date, sizeof(borrowing.due_date), stdin);
    borrowing.due_date[strcspn(borrowing.due_date, "\n")] = 0;
    
    strcpy(borrowing.return_date, "");
    
    file = fopen(BORROWINGS_FILE, "ab");
    if(file != NULL) {
        fwrite(&borrowing, sizeof(Borrowing), 1, file);
        fclose(file);
        printf("\nBook borrowed successfully! Borrowing ID: %d\n", borrowing.borrowing_id);
    } else {
        printf("Error: Could not save borrowing record!\n");
    }
    
    pressEnterToContinue();
}

void viewBorrowings() {
    Borrowing borrowing;
    FILE *file;
    int found = 0;
    
    clearScreen();
    printf("\n=== ALL BORROWINGS ===\n");
    printf("%-5s %-8s %-10s %-12s %-12s %-12s %-8s\n", 
           "ID", "Book ID", "Member ID", "Borrow Date", "Due Date", "Return Date", "Staff ID");
    printf("---------------------------------------------------------------------------------------------\n");
    
    file = fopen(BORROWINGS_FILE, "rb");
    if(file != NULL) {
        while(fread(&borrowing, sizeof(Borrowing), 1, file)) {
            printf("%-5d %-8d %-10d %-12s %-12s %-12s %-8d\n",
                   borrowing.borrowing_id, borrowing.book_id, borrowing.member_id,
                   borrowing.borrow_date, borrowing.due_date, 
                   strlen(borrowing.return_date) > 0 ? borrowing.return_date : "Not Returned",
                   borrowing.staff_id);
            found = 1;
        }
        fclose(file);
    }
    
    if(!found) {
        printf("No borrowings found!\n");
    }
    
    pressEnterToContinue();
}

// Utility functions
int getNextId(const char* filename, size_t recordSize) {
    FILE *file;
    int maxId = 0;
    char buffer[recordSize];
    int currentId;
    
    file = fopen(filename, "rb");
    if(file != NULL) {
        while(fread(buffer, recordSize, 1, file)) {
            // Assuming ID is the first integer in each structure
            currentId = *((int*)buffer);
            if(currentId > maxId) {
                maxId = currentId;
            }
        }
        fclose(file);
    }
    
    return maxId + 1;
}

void getCurrentDate(char* date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Placeholder implementations for remaining functions
void updateBook() { printf("Update Book function - To be implemented\n"); pressEnterToContinue(); }
void deleteBook() { printf("Delete Book function - To be implemented\n"); pressEnterToContinue(); }
void updateAuthor() { printf("Update Author function - To be implemented\n"); pressEnterToContinue(); }
void deleteAuthor() { printf("Delete Author function - To be implemented\n"); pressEnterToContinue(); }
void publisherMenu() { printf("Publisher Menu - To be implemented\n"); pressEnterToContinue(); }
void addPublisher() { printf("Add Publisher function - To be implemented\n"); pressEnterToContinue(); }
void viewPublishers() { printf("View Publishers function - To be implemented\n"); pressEnterToContinue(); }
void updatePublisher() { printf("Update Publisher function - To be implemented\n"); pressEnterToContinue(); }
void deletePublisher() { printf("Delete Publisher function - To be implemented\n"); pressEnterToContinue(); }
void updateMember() { printf("Update Member function - To be implemented\n"); pressEnterToContinue(); }
void deleteMember() { printf("Delete Member function - To be implemented\n"); pressEnterToContinue(); }
void staffMenu() { printf("Staff Menu - To be implemented\n"); pressEnterToContinue(); }
void addStaff() { printf("Add Staff function - To be implemented\n"); pressEnterToContinue(); }
void viewStaff() { printf("View Staff function - To be implemented\n"); pressEnterToContinue(); }
void updateStaff() { printf("Update Staff function - To be implemented\n"); pressEnterToContinue(); }
void deleteStaff() { printf("Delete Staff function - To be implemented\n"); pressEnterToContinue(); }
void returnBook() { printf("Return Book function - To be implemented\n"); pressEnterToContinue(); }
void fineMenu() { printf("Fine Menu - To be implemented\n"); pressEnterToContinue(); }
void addFine() { printf("Add Fine function - To be implemented\n"); pressEnterToContinue(); }
void viewFines() { printf("View Fines function - To be implemented\n"); pressEnterToContinue(); }
void payFine() { printf("Pay Fine function - To be implemented\n"); pressEnterToContinue(); }