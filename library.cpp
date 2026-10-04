#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool issued;

    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;

        cout << "\nBook added successfully!\n";
    }

    void displayBook()
    {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: ";

        if(issued)
            cout << "Issued";
        else
            cout << "Available";

        cout << "\n-----------------------------\n";
    }
};

void saveBooks(Book books[], int count)
{
    ofstream file("books.txt");

    for(int i = 0; i < count; i++)
    {
        file << books[i].id << endl;
        file << books[i].title << endl;
        file << books[i].author << endl;
        file << books[i].issued << endl;
    }

    file.close();
}

int loadBooks(Book books[])
{
    ifstream file("books.txt");

    int count = 0;

    while(file >> books[count].id)
    {
        file.ignore();

        getline(file, books[count].title);
        getline(file, books[count].author);

        file >> books[count].issued;

        count++;

        if(count >= 100)
            break;
    }

    file.close();

    return count;
}

int main()
{
    Book books[100];

    int count = loadBooks(books);
    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                if(count < 100)
                {
                    books[count].addBook();
                    count++;

                    saveBooks(books, count);
                }
                else
                {
                    cout << "\nLibrary is full!\n";
                }

                break;
            }

            case 2:
            {
                if(count == 0)
                {
                    cout << "\nNo books available.\n";
                }
                else
                {
                    cout << "\n========== ALL BOOKS ==========\n";

                    for(int i = 0; i < count; i++)
                    {
                        books[i].displayBook();
                    }
                }

                break;
            }

            case 3:
            {
                int searchId;
                bool found = false;

                cout << "\nEnter Book ID to search: ";
                cin >> searchId;

                for(int i = 0; i < count; i++)
                {
                    if(books[i].id == searchId)
                    {
                        cout << "\nBook Found!\n";
                        books[i].displayBook();

                        found = true;
                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nBook not found!\n";
                }

                break;
            }

            case 4:
            {
                int issueId;
                bool found = false;

                cout << "\nEnter Book ID to issue: ";
                cin >> issueId;

                for(int i = 0; i < count; i++)
                {
                    if(books[i].id == issueId)
                    {
                        found = true;

                        if(books[i].issued)
                        {
                            cout << "\nBook is already issued!\n";
                        }
                        else
                        {
                            books[i].issued = true;

                            saveBooks(books, count);

                            cout << "\nBook issued successfully!\n";
                        }

                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nBook not found!\n";
                }

                break;
            }

            case 5:
            {
                int returnId;
                bool found = false;

                cout << "\nEnter Book ID to return: ";
                cin >> returnId;

                for(int i = 0; i < count; i++)
                {
                    if(books[i].id == returnId)
                    {
                        found = true;

                        if(!books[i].issued)
                        {
                            cout << "\nBook is already available!\n";
                        }
                        else
                        {
                            books[i].issued = false;

                            saveBooks(books, count);

                            cout << "\nBook returned successfully!\n";
                        }

                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nBook not found!\n";
                }

                break;
            }

            case 6:
            {
                int deleteId;
                bool found = false;

                cout << "\nEnter Book ID to delete: ";
                cin >> deleteId;

                for(int i = 0; i < count; i++)
                {
                    if(books[i].id == deleteId)
                    {
                        found = true;

                        for(int j = i; j < count - 1; j++)
                        {
                            books[j] = books[j + 1];
                        }

                        count--;

                        saveBooks(books, count);

                        cout << "\nBook deleted successfully!\n";

                        break;
                    }
                }

                if(!found)
                {
                    cout << "\nBook not found!\n";
                }

                break;
            }

            case 7:
                cout << "\nThank you for using the Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while(choice != 7);

    return 0;
}