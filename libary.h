#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 50

char stringInput[128];
typedef struct
{

    char *borrower;
    char *returner;
} LIST_T;

typedef struct
{
    char *title;
    char *author;
    char *publish;
    char *status;
    LIST_T *activity;
} LIST_LIBARY;

void menu()
{
}




// -------------------------------------------------- Check title, author, borrower, returner function ----------------------------------------------------------------
int checkString(char *bookString) // String that input
{
    char *string = bookString;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
            break;
        }
    }

    while (*string != '\0')
    {
        if ((toupper(*string) >= 65 && (toupper(*string) <= 90) || *string == 32))
        {
            string++;
        }
        else
        {
            printf("Invalid string\n");
            return -1;
        }
    }
    return 1;
}

int checkString2(char *bookString) // String that input and not change \n to \0
{
    char *string = bookString;

    while (*string != '\n')
    {
        if ((toupper(*string) >= 65 && (toupper(*string) <= 90) || *string == 32))
        {
            string++;
        }
        else
        {
            printf("Invalid string\n");
            return -1;
        }
    }
    return 1;
}



// -------------------------------------------------- Check Year function ----------------------------------------------------------------
int checkYear(char *year) // Publish Year that input
{
    char *string = year;
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
            break;
        }
    }

    while (*string != '\0')
    {
        if (*string >= 48 && *string <= 57)
        {
            string++;
        }
        else
        {
            printf("Invalid year input\n");
            return -1;
        }
    }
    return 1;
}

int checkYear2(char *year) // Publish Year that input and not change \n to \0
{
    char *string = year;

    while (*string != '\n')
    {
        if (*string >= 48 && *string <= 57)
        {
            string++;
        }
        else
        {
            printf("Invalid year input\n");
            return -1;
        }
    }
    return 1;
}




// -------------------------------------------------- Check amount of books in system ----------------------------------------------------------------
int checkBook()
{
    int index = 0;
    char string[MAX];
    FILE *fp = fopen("status.txt", "r");
    if (fp == NULL)
    {
        return -1;
    }
    while (fscanf(fp, "%s", &string) != EOF)
    {
        index++;
    }
    fclose(fp);
    //printf("index %d\n", index);
    return index;
}


// -------------------------------------------------- Check times of borrowing books----------------------------------------------------------------
int checkHistory()
{
    int count = 0;
    int temp = 0;
    char buffer[MAX];
    printf("Checking history\n");
    FILE *fp = fopen("history.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open history.txt\n");
    }
    while (fgets(buffer, MAX, fp))
    {
        fgets(buffer, MAX, fp);
        count++;
    }
    fclose(fp);
    return count;
}



// -------------------------------------------------- Check times of returning books ----------------------------------------------------------------
int checkReturner()
{
    int count = 0;
    int temp = 0;
    char buffer[MAX];
    printf("Checking returner\n");
    FILE *fp = fopen("returner.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open returner.txt\n");
    }
    while (fgets(buffer, MAX, fp))
    {
        fgets(buffer, MAX, fp);
        count++;
    }
    fclose(fp);
    return count;
}



// -------------------------------------------------- Find index of title ----------------------------------------------------------------
// titleEdit is title of book that want find index
// lists is infromation of book that read from text file
int checkTitle(LIST_LIBARY *lists, char *titleEdit) 
{
    int i = 0;
    int j = 0;
    int count = checkBook();
    int check = 0;
    if (lists == NULL)
    {
        printf("Pass by reference failed\n");
    }
    printf("before loop\n");
    for (i = 0; i < count; i++)
    {
        printf("%s\n", lists[i].title);
        printf("in loop\n");
        if (strcmp(lists[i].title, titleEdit) == 0)
        {
            check = 2;
            printf("i = %d\n", i);
            return i;
        }
    }
    printf("Not Found\n");
    return -1;
}


// -------------------------------------------------- Allocate struct LIST_LIBARY ----------------------------------------------------------------
LIST_LIBARY *createdList()
{
    int count = 0;
    int his = 0;
    char buffer[10] = ".";
    count = checkBook();
    his = checkHistory();
    LIST_LIBARY *list = (LIST_LIBARY *)calloc(count + 1, sizeof(LIST_LIBARY));
    // LIST_T *activity = (LIST_T *)calloc(count + 1, sizeof(LIST_T));

    for (int i = 0; i < count; i++)
    {
        list[i].title = (char *)calloc(MAX, sizeof(char));
        list[i].author = (char *)calloc(MAX, sizeof(char));
        list[i].publish = (char *)calloc(MAX, sizeof(char));
        list[i].status = (char *)calloc(MAX, sizeof(char));
        list[i].activity = (LIST_T *)calloc(his, sizeof(LIST_T));
        
        for (int j = 0; j < his; j++)
        {
            (list[i].activity[j]).borrower = (char *)calloc(MAX, sizeof(char));
            (list[i].activity[j]).borrower[0] = buffer[0];
            (list[i].activity[j]).returner = (char *)calloc(MAX, sizeof(char));
            (list[i].activity[j]).returner[0] = buffer[0];
        }
    }
    if (list == NULL)
    {
        printf("allocate failed\n");
    }
    return list;
}



// -------------------------------------------------- Read name of borrower from text file (history.txt) ----------------------------------------------------------------
// lists is array of struct that keep information that is read from text file 
int readFileBorrow(LIST_LIBARY *lists)
{
    if (lists == NULL)
    {
        printf("Pass by reference failed\n");
        return -1;
    }
    printf("readFileBorrow failed\n");
    int count = 0;
    int his = 0;
    int index = 0;
    int j = 0;
    int n = 0;
    int add = 0;
    char titleRead[MAX];
    char name[MAX];
    
    his = checkHistory();
    printf("his = %d\n", his);
    count = checkBook();
    int countIndex[his + 1];

    for (int i = 0; i < his+1; i++)
    {
        countIndex[i] = -1;
    }

    FILE *fp = fopen("history.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file history\n");
        return -2;
    }
    for (int i = 0; i < his; i++)
    {
        add = 0;
        j = 0;
        fgets(titleRead, MAX, fp);
        fgets(name, MAX, fp);
        index = checkTitle(lists, titleRead);
        printf("index borrower %d\n",index);
        countIndex[i] = index;
        
        while ((countIndex[j] != -1) && (i != 0))
        {
            if (countIndex[j] == index)
            {
                add++;
            }
            j++;
        }
        if (i != 0)
        {
            add = add - 1;
        }
        printf("after index\n");
        n = 0;
        while (name[n] != '\n')
        {
            ((lists[index].activity[add]).borrower)[n] = name[n];
            n++;
        }
        //printf("readFileBorrow failed9\n");
        ((lists[index].activity[add]).borrower)[n] = '\n';
        //printf("name of borrower %s  index(%d)  add(%d)\n",lists[index].activity[add].borrower, index, add);
        //(lists[index].activity[j]).returner = NULL

    }
    fclose(fp);
}



// -------------------------------------------------- Read name of returner from text file (returner.txt) ----------------------------------------------------------------
// lists is array of struct that keep information that is read from text file  
int readFileReturner(LIST_LIBARY *lists)
{
    if (lists == NULL)
    {
        printf("Pass by reference failed\n");
        return -1;
    }
    printf("readFileReturner failed\n");
    int count = 0;
    int his = 0;
    int index = 0;
    int j = 0;
    int n = 0;
    int add = 0;
    char titleRead[MAX];
    char name[MAX];
    
    his = checkReturner();
    printf("re = %d\n", his);
    count = checkBook();
    int countIndex[his + 1];

    for (int i = 0; i < his+1; i++)
    {
        countIndex[i] = -1;
    }

    FILE *fp = fopen("returner.txt", "r");
    if (fp == NULL)
    {
        printf("Cannot open file returner\n");
        return -2;
    }
    for (int i = 0; i < his; i++)
    {
        add = 0;
        j = 0;
        fgets(titleRead, MAX, fp);
        fgets(name, MAX, fp);
        index = checkTitle(lists, titleRead);
        printf("index returner %d\n",index);
        countIndex[i] = index;
        
        while ((countIndex[j] != -1) && (i != 0))
        {
            if (countIndex[j] == index)
            {
                add++;
            }
            j++;
        }
        if (i != 0)
        {
            add = add - 1;
        }
        printf("after index\n");
        n = 0;
        while (name[n] != '\n')
        {
            ((lists[index].activity[add]).returner)[n] = name[n];
            n++;
        }
        printf("readFileReturner failed9\n");
        ((lists[index].activity[add]).returner)[n] = '\n';
        printf("name of returner %s  index(%d)  add(%d)\n",lists[index].activity[add].returner, index, add);
        //(lists[index].activity[j]).returner = NULL
    }
    fclose(fp);
}



// ------------------------ Read information of books from text file (title, author, year, status) and Called function readFileReturner, readFileBorrower----------------------------------------------------------------
LIST_LIBARY *readFile()
{
    LIST_LIBARY *book;
    int count = 0;
    int his = 0;
    his = checkHistory();
    count = checkBook();
    book = createdList();
    if (book == NULL)
    {
        printf("Error\n");
    }

    if (book == NULL)
    {
        printf("ERROR\n");
    }
    FILE *fpTitle = fopen("title.txt", "r");
    FILE *fpAuthor = fopen("author.txt", "r");
    FILE *fpYear = fopen("year.txt", "r");
    FILE *fpStatus = fopen("status.txt", "r");
    // FILE *fpHistory = fopen("history.txt", "r");
    if (fpTitle == NULL || fpAuthor == NULL || fpYear == NULL || fpStatus == NULL)
    {
        printf("File cannot open\n");
    }
    for (int i = 0; i < count; i++)
    {
        fgets(book[i].title, 50, fpTitle);
        // printf("%s\n", book[i].title);
        fgets(book[i].author, 50, fpAuthor);
        fgets(book[i].publish, 50, fpYear);
        fgets(book[i].status, 50, fpStatus);
    }
    fclose(fpTitle);
    fclose(fpAuthor);
    fclose(fpYear);
    fclose(fpStatus);
    // printf("outside %s\n", book[1].publish);
    readFileBorrow(book);
    readFileReturner(book);
    return book;
}



// -------------------------------------------------- Write information in text file when have new input (title, author, year, status) ------------------------------------------------------
// lists is array of struct that keep information that is read from text file  
// count is number of book in present
int writeFile(LIST_LIBARY *list, int count)
{
    if (list == NULL)
    {
        printf("Pass by reference failed\n");
        return -1;
    }
    FILE *fpTitle = fopen("title.txt", "w");
    FILE *fpAuthor = fopen("author.txt", "w");
    FILE *fpYear = fopen("year.txt", "w");
    FILE *fpStatus = fopen("status.txt", "w");
    if (fpTitle == NULL || fpAuthor == NULL || fpYear == NULL || fpStatus == NULL)
    {
        printf("Cannot open file\n");
        return -2;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fpTitle, "%s", list[i].title);
        fprintf(fpAuthor, "%s", list[i].author);
        //printf("lists write %s\n", list[i].author);
        fprintf(fpYear, "%s", list[i].publish);
        fprintf(fpStatus, "%s", list[i].status);
    }
    fclose(fpTitle);
    fclose(fpAuthor);
    fclose(fpYear);
    fclose(fpStatus);
    free(list);
}



// ---------------------------------------------------------------- Add new book function ----------------------------------------------------------------
int bookInsert(LIST_LIBARY *book) // struct LIST_LIBARY book
{
    int count = 0;
    int check = 0;
    char titleInsert[MAX];
    char authorInsert[MAX];
    char publishInsert[MAX];
    char *statusInsert;

    // Input Title
    do
    {
        printf("Title : ");
        fgets(titleInsert, 50, stdin);
        check = checkString(titleInsert);
    } while (check != 1);
    // printf("title[%d]: %s\n", count, titleInsert);

    // Input Author
    do
    {
        printf("Author : ");
        fgets(authorInsert, 50, stdin);
        check = checkString(authorInsert);
    } while (check != 1);
    // printf("author[%d]: %s\n", count, authorInsert);

    // Input Publish Year
    do
    {
        printf("Publish Year : ");
        fgets(publishInsert, 50, stdin);
        check = checkYear(publishInsert);
    } while (check != 1);
    // printf("publish[%d]: %s\n", count, publishInsert);

    statusInsert = "Available";

    // Add information of book in text file
    FILE *fpTitle = fopen("title.txt", "a");
    FILE *fpAuthor = fopen("author.txt", "a");
    FILE *fpYear = fopen("year.txt", "a");
    FILE *fpStatus = fopen("status.txt", "a");

    if (fpTitle == NULL || fpAuthor == NULL || fpYear == NULL || fpStatus == NULL)
    {
        printf("File is not created.\n");
        return -1;
    }

    fprintf(fpTitle, "%s\n", titleInsert);
    fprintf(fpAuthor, "%s\n", authorInsert);
    fprintf(fpYear, "%s\n", publishInsert);
    fprintf(fpStatus, "%s\n", statusInsert);

    fclose(fpTitle);
    fclose(fpAuthor);
    fclose(fpYear);
    fclose(fpStatus);

    free(book);
}

int showBook(LIST_LIBARY *lists)
{
    int count = checkBook();
    int his = checkHistory();

    for (int i = 0; i < count; i++)
    {
        printf("Title : %s", lists[i].title);
        printf("Author Name: %s", lists[i].author);
        printf("Publish Year : %s", lists[i].publish);
        printf("Status : %s", lists[i].status);
        printf("Borrow History :\n");
        for (int j = 0; j < his; j++)
        {
            if ((lists[i].activity[j]).borrower[0] != '.')
            {
                printf("- Borrow by %s", (lists[i].activity[j]).borrower);
            }
            if ((lists[i].activity[j]).returner[0] != '.')
            {
                printf("- Return by %s", (lists[i].activity[j]).returner);
            }
            
        }
        printf("\n");
    }
}

int searchBook(LIST_LIBARY *lists)
{
    int check = 0;
    int count = checkBook();
    char titleSearch[MAX];
    char authorSearch[MAX];
    char *temp;
    char *tempTitle;
    char *tempAuthor;
    do
    {
        printf("Enter title (leave blank to include all titles): ");
        fgets(titleSearch, 50, stdin);
        if (*titleSearch == '\n')
        {
            break;
        }
        else
        {
            check = checkString(titleSearch);
        }
    } while (check != 1);

    do
    {
        printf("Enter author name (leave blank to include all titles): ");
        fgets(authorSearch, 50, stdin);
        if (*authorSearch == '\n')
        {
            break;
        }
        else
        {
            check = checkString(authorSearch);
        }
    } while (check != 1);

    for (int i = 0; i < count; i++)
    {

        if (*authorSearch == '\n')
        {
            tempTitle = titleSearch;
            temp = lists[i].title;
            while (*temp != '\n')
            {
                if (*temp == *tempTitle)
                {
                    while (*tempTitle != '\0')
                    {
                        if (*temp == *tempTitle)
                        {
                            tempTitle++;
                            temp++;
                        }
                        else
                        {
                            break;
                            tempTitle = titleSearch;
                        }
                    }
                }
                if (*tempTitle == '\0')
                {
                    break;
                }
                temp++;
            }

            if (*tempTitle == '\0')
            {
                printf("%s", lists[i].title);
                printf("%s", lists[i].author);
                printf("%s", lists[i].publish);
            }
        }

        else if (*titleSearch == '\n')
        {
            tempAuthor = authorSearch;
            temp = lists[i].author;
            while (*temp != '\n')
            {
                if (*temp == *tempAuthor)
                {
                    while (*tempAuthor != '\0')
                    {
                        if (*temp == *tempAuthor)
                        {
                            tempAuthor++;
                            temp++;
                        }
                        else
                        {
                            tempAuthor = titleSearch;
                            break;
                        }
                    }
                }
                else if (*tempAuthor == '\0')
                {
                    break;
                }
                else if (*temp != *tempAuthor)
                {
                    break;
                }
                temp++;
            }
            if (*tempAuthor == '\0')
            {
                printf("%s", lists[i].title);
                printf("%s", lists[i].author);
                printf("%s", lists[i].publish);
            }
        }
    }
}

int editBook(LIST_LIBARY *lists)
{
    int check = 0;
    int count = checkBook();
    int i = 0;
    char *newTitle;
    char *newAuthor;
    char *newPublish;
    char *new;
    char *titleEdit;
    int index = 0;

    do
    {
        printf("Enter title to edit: ");
        fgets(titleEdit, MAX, stdin);
        printf("input loop\n");
        check = checkString2(titleEdit);
    } while (check != 1);

    index = checkTitle(lists, titleEdit);

    printf("%s\n", lists[index].author);

    do
    {
        if (check != 1)
        {
            printf("New title (leave blank to retain old value): ");
            fgets(newTitle, MAX, stdin);
        }
        if (*newTitle == '\n')
        {
            break;
        }
        check = checkString2(newTitle);
    } while (check != 1);

    new = newTitle;
    if (*new != '\n')
    {
        while (*new != '\n')
        {
            (lists[index].title)[i] = *new;
            new ++;
            i++;
        }
    }

    i = 0;
    check = 0;
    do
    {
        if (check != 1)
        {
            printf("New author (leave blank to retain old value): ");
            fgets(newAuthor, MAX, stdin);
        }
        if (*newAuthor == '\n')
        {
            break;
        }
        check = checkString2(newAuthor);
    } while (check != 1);

    new = newAuthor;
    if (*new != '\n')
    {
        while (*new != '\n')
        {
            (lists[index].author)[i] = *new;
            new ++;
            i++;
        }
        // new = newAuthor;
        // lists[index].author = new;
        printf("lists edit function %s\n", lists[index].author);
    }

    check = 0;
    i = 0;
    do
    {
        if (check != 1)
        {
            printf("New publish year (leave blank to retain old value): ");
            fgets(newPublish, MAX, stdin);
        }
        if (*newPublish == '\n')
        {
            break;
        }
        check = checkYear2(newPublish);
    } while (check != 1);

    new = newPublish;
    if (*new != '\n')
    {

        while (*new != '\n')
        {
            (lists[index].publish)[i] = *new;
            new ++;
            i++;
        }
        // printf("new publish %s\n",)
        //  new = newPublish;
        //  lists[index].publish = new;
    }
    printf("new publish %s\n", lists[index].publish);
    printf("count %d\n", count);

    titleEdit = NULL;
    writeFile(lists, count);
}

int removeBook(LIST_LIBARY *lists)
{
    int check = 0;
    int i = 0;
    int j = 0;
    int temp = 0;
    int count = checkBook();
    char *tempTitle;
    char *tempTitle2;
    char titleMove[MAX];
    do
    {
        printf("Enter title to be removed: ");
        fgets(titleMove, MAX, stdin);
        check = checkString2(titleMove);
    } while (check != 1);

    for (i = 0; i < count; i++)
    {
        if (strcmp(lists[i].title, titleMove) == 0)
        {
            check = 2;
            printf("i = %d\n", i);
            break;
        }
    }

    if (check != 2)
    {
        printf("Invalid title\n");
        return -1;
    }

    printf("check temp\n");
    for (temp = i; temp < count; temp++)
    {
        lists[temp].title = lists[temp + 1].title;
        lists[temp].author = lists[temp + 1].author;
        lists[temp].publish = lists[temp + 1].publish;
        lists[temp].status = lists[temp + 1].status;
    }
    writeFile(lists, count - 1);
}

int borrowBook(LIST_LIBARY *lists)
{
    // input title and name of borrowers then check string that input and check index of title that is borrowed 
    //in checkTitle function and then write title and borrow name in history text file
    int check = 0;
    char titleBorrow[MAX];
    char name[MAX];
    int index = 0;
    int count = checkBook(lists);
    char *borrow = "Borrowed\n";
    if (lists == NULL)
    {
        printf("Pass by reference failed\n");
        return -1;
    }

    do
    {
        printf("Enter borrower name: ");
        fgets(name, MAX, stdin);
        check = checkString2(name);
    } while (check != 1);

    do
    {
        printf("Enter title to borrow: ");
        fgets(titleBorrow, MAX, stdin);
        check = checkString2(titleBorrow);
    } while (check != 1);
    index = checkTitle(lists, titleBorrow);

    if (strcmp (lists[index].status, borrow) == 0)
    {
        printf("This book is borrowed\n");
        return -1;
    }


    FILE *fp = fopen("history.txt", "a");
    if (fp == NULL)
    {
        printf("Cannot open history file.\n");
        return -1;
    }
    lists[index].status = "Borrowed\n";
    fprintf(fp, "%s", lists[index].title);
    fprintf(fp, "%s", name);
    // list->activity.borrower = borrow;
    // list->status = "Borrowed";
    // printf("borrower[%d]: %s\n", index, list->activity.borrower);
    fclose(fp);

    FILE *fpStatus = fopen("status.txt","w");
    for (int i = 0; i < count; i++)
    {
        printf("check status %s", lists[index].status);
        fprintf(fpStatus, "%s", lists[i].status);
    }
    fclose(fpStatus);
    free(lists);
}

int returnBook(LIST_LIBARY *lists)
{
    int check = 0;
    int count = checkBook();
    char titleReturn[MAX];
    char name[MAX];
    int index = 0;

    if (lists == NULL)
    {
        printf("Pass by reference failed\n");
        return -1;
    }

    do
    {
        printf("Enter returner name: ");
        fgets(name, MAX, stdin);
        check = checkString2(name);
    } while (check != 1);

    do
    {
        printf("Enter title to return: ");
        fgets(titleReturn, MAX, stdin);
        check = checkString2(titleReturn);
    } while (check != 1);
    index = checkTitle(lists, titleReturn);

    FILE *fp = fopen("returner.txt", "a");
    if (fp == NULL)
    {
        printf("Cannot open returner file.\n");
        return -1;
    }
    lists[index].status = "Available\n";
    fprintf(fp, "%s", lists[index].title);
    fprintf(fp, "%s", name);
    fclose(fp);

    FILE *fpStatus = fopen("status.txt","w");
    for (int i = 0; i < count; i++)
    {
        fprintf(fpStatus, "%s", lists[i].status);
    }
    fclose(fpStatus);
    free(lists);
}

