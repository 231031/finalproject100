#include <stdio.h>
#include "libary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    int check = 0;
    int choice = 0;
    int count = 0;
    int num = 0;
    int index = 0;
    char input[50];
    LIST_LIBARY *bookMain = NULL;

    printf("Welcome to CPE Libary Management System\n");
    do
    {
        //menu();
        printf("Menu\n");
        printf("> ");
        fgets(input, sizeof(5), stdin);
        sscanf(input, "%d", &choice);

        // Add book
        if (choice == 1)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            bookInsert(bookMain);
            bookMain = readFile();
        }

        // Remove book
        else if (choice == 2)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            printf("Main %s\n", bookMain[2].title);

            removeBook(bookMain);
            readFile(bookMain);
        }

        // Edit book
        else if (choice == 3)
        {
            count = checkBook();
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            editBook(bookMain);
            // writeFile(bookMain, count);
            // printf("bookMain[3] %s\n", bookMain[3].author);
            readFile(bookMain);
        }

        // show all book
        else if (choice == 4)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }

            showBook(bookMain);
            // readFile(bookMain);
        }

        // Search book
        else if (choice == 5)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            searchBook(bookMain);
        }

        // Borrow book
        else if (choice == 6)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            printf("after reading\n");
            printf("%s\n", (bookMain[4].activity[0]).borrower);
            printf("%s\n", (bookMain[5].activity[0]).borrower);
            borrowBook(bookMain);
            printf("after borrower\n");
            bookMain = readFile();
            printf("after reading after borrower\n");
            printf("%s", (bookMain[4].activity[0]).borrower);
            printf("%s", (bookMain[0].activity[0]).borrower);
        }

        // Return book
        else if (choice == 7)
        {
            if (bookMain == NULL)
            {
                bookMain = readFile();
            }
            printf("check readFile\n");
            returnBook(bookMain);
            printf("after returner\n");
            bookMain = readFile();
            printf("%s", (bookMain[4].activity[0]).returner);
            printf("%s", (bookMain[0].activity[0]).returner);
            printf("%s", (bookMain[0].activity[0]).returner);
        }

    } while (choice != 8);

    return 0;
}
