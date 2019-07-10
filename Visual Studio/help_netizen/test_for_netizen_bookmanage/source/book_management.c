#pragma warning(disable:4996)   //shielding 4996 warning in vs2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* macro definition */
#define ARRAY_ROW(array)    ((sizeof(array)) / (sizeof(array[0])))  //caculate the number of array rows


#define NUM     10      //the number of books


/* type define */
typedef struct tagbookinfo
{
    char ISBN[10];      //book number
    char book[30];      //book name
    char author[20];    //author
    int edition;        //version number
    char press[50];     //press name
    int year;           //press year
}BookInfo;

typedef struct tagbooktable //include info and number
{
    BookInfo bookinfo;
    int number_record;
}BookTable;

/* variables that are used only for this source file */
#if 0
static BookInfo l_book_table[10] = 
{   /*number        name        author  version     press_name      press_year*/
    {"1182",    "高等数学",     "刘浩荣",   5,      "同济大学出版社",   2013},
    {"7300",    "物理化学",     "王明德",   2,      "化学工业出版社",   2015},
};
#endif
static BookTable *l_book_table;	//book table pointer

/* functions that are used only for this source file */
static int Input(BookInfo *dictList, int n);    //input bookinfo
static void Display(BookInfo *dictList, int n); //display bookinfo
static int Delete(BookInfo *dictList, int n, char *book);   //delete bookinfo
static void Sort_by_name(BookInfo *dictList, int n);    //sort bookinfo by name
static int Insert(BookInfo *dictList, int n, Dictionary *s);    //insert orderly by name
static int Insert_a_record(BookInfo *dictList, int n);  //insert a bookinfo
static int Query(BookInfo *dictList, int n, BookInfo *book);    //query book and display
static int AddfromText(BookInfo *dictList, int n, char *filename);
static void WritetoText(BookInfo *dictList, int n, char *filename);
static void Display_main_menu(void);    //display menu
static BookTable *create_book_table(void);   //create bookinfo struct array



/* main function */
int main(void)
{
    int step = 0;

    l_book_table = create_book_table();

    while(1)
    {
        Display_main_menu();
        scanf("%d", &step);
        switch(step)
        {
            case 1:
                Input(&l_book_table->bookinfo, l_book_table->number_record);
                break;
            case 2:
                Display(&l_book_table->bookinfo, l_book_table->number_record);
                break;
            case 3:
                Delete(&l_book_table->bookinfo, l_book_table->number_record, char *book);
                break;
            case 4:
                Sort_by_name(&l_book_table->bookinfo, l_book_table->number_record);
                break;
            case 5:
                Insert(&l_book_table->bookinfo, l_book_table->number_record, Dictionary *s);
                break;
            case 6:
                Query(&l_book_table->bookinfo, l_book_table->number_record, BookInfo *book);
                break;
            case 7:
                AddfromText(&l_book_table->bookinfo, l_book_table->number_record, char *filename);
                break;
            case 8:
                WritetoText(&l_book_table->bookinfo, l_book_table->number_record, char *filename);
                break;
            case 0:
                exit(0);    //stop running and exit;
            default:
				printf("please re-input the number of your choose!");
                break;
        }
    }

    return 0;
}


BookTable *create_book_table(void)
{
    BookTable *p = (BookTable *)malloc(sizeof(BookTable));
    if(p == NULL)
    {
        printf("create a bookinfo failed!\n");
        return NULL;
    }
    memset(p, 0, sizeof(BookTable));    //initialize to 0

    return p;
}

void Display_main_menu(void)
{
    ;
}

int Input(BookInfo *dictList, int n)
{
    ;
}

