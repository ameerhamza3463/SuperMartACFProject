#include <stdio.h>
// #include<iostream>
// #include <unistd.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
// using namespace std;
// STRUCTURES
#define COLOR_BOLD "\x1B[1m"
#define COLOR_OFF "\x1B[0m"
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"
#define UNDERLINE "\033[4m"
#define CLOSEUNDERLINE "\033[0m"

struct items
{
    int code;
    char name[30];
    int quantity;
    int price;
};
struct user
{
    int code;
    char name[30];
} customer, employee;
int monthly_sales;
// FUNCTIONS
int greeting();
void reportGenerationLoadingScreen();
int Accounts(void);
void RepeatOnInvalid1(void);
int printing();
// int countproduct();
int countcart(struct items *);
int adminPortal();
int adminMenu();
int addProduct();
int deleteProduct();
int addEmploye();
int remEmploye();
int employeePortal();
void updating_sales(int);

// MAIN
int main(int argc, char const *argv[])
{
    // To clean previous lines.
    system("cls");
    struct items *product, *cart;
    FILE *ptr;
    ptr = fopen("Products.txt", "r+");
    if (ptr == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    strcpy(employee.name, "ALI");

    // productQuantity = Qunatity of products in Products.txt
    int productQuantity;
    fscanf(ptr, "%d", &productQuantity);
    product = (struct items *)calloc(productQuantity, sizeof(struct items));
    cart = (struct items *)calloc(productQuantity, sizeof(struct items));

    int DidYouGreet = 0, IsCustomerAvailable = 0;
    while (1)
    {
        if (DidYouGreet == 0)
        {
            DidYouGreet = greeting();
        }
        if (DidYouGreet == 1)
        {
            if (IsCustomerAvailable == 0)
            {
                IsCustomerAvailable = Accounts();
            }
            else
            {
                system("cls");
                IsCustomerAvailable = printing(ptr, product, cart, productQuantity);
            }

            // Opening Products.txt file for updating data.
            // Temporary work to stop screen
            // printf("\n");
            // fflush(stdin);
            // getchar();
        }
    }
    return 0;
}
int greeting()
{
    int choice;
    do
    {
        system("cls");
        printf("\t\t\t\t\tWELCOME TO MAAD MART\n\t\t\t\t\t    LOGIN PROTAL\n\n");
        printf("\t\t\t\tSelect the respective option:\n");
        printf("\t\t\t\tLogin as Admin\t\t\t1\n");
        printf("\t\t\t\tLogin as Employee\t\t2\n\n");
        printf("\t\t\t\t\tInput: ");
        fflush(stdin);
        scanf(" %d", &choice);
        if (choice != 1 && choice != 2)
        {
            printf("\t\t\t\t     INVALID INPUT (O-o)\n");
            sleep(1);
        }

    } while (choice != 1 && choice != 2);

    switch (choice)
    {
    case 1:
    {
        choice = adminPortal();
        break;
    }
    case 2:
    {
        choice = employeePortal();
        break;
    }
    }
    return choice;
}
void LoadingScreen()
{
    int counter = 0, i, j, k;
    for (i = 0; i < 101; i++)
    {
        if (i % 5 == 0)
        {
            counter += 2;
        }
        system("cls");
        printf("\n\n\n\n\t\t\t   GENERATING REPORT `\\(^ o ^)/`\n\n\t\t\t");
        for (j = 0; j < counter; j += 10)
        {
            printf("_______");
        }
        printf("\n\n\t\t\t\t\t%d %c\n\n\n", i, 37);
        if (i == 5 || i == 17 || i == 87)
        {
            sleep(1);
        }
        else if (i == 99)
        {
            sleep(2);
        }
        else
        {
            usleep(20000);
        }
    }
}
struct pro
{
    char name[20];
    float profit;
} * Profits;
void reportGenerationLoadingScreen()
{
    int i = 0, j = 0;
    system("cls");
    printf("\x1B[1;%dm", 29);
    printf("\t\t\t\t\t<--- SALE REPORT --->\n\n");
    FILE *fileptr;
    fileptr = fopen("./Products.txt", "r");
    if (fileptr == NULL)
    {
        printf("\t\t\t\tCould not open the file. (! . !)\n");
        exit(1);
    }

    int code, quantity, price, productQuantity;
    char name[20];
    fscanf(fileptr, "%d", &productQuantity);

    int *OpeningStock;
    struct items *ClosingStock;
    OpeningStock = (int *)calloc(productQuantity, sizeof(int));
    ClosingStock = (struct items *)calloc(productQuantity, sizeof(struct items));
    // struct pro *Profits;
    Profits = (struct pro *)calloc(productQuantity, sizeof(struct pro));

    i = 0;
    while (fscanf(fileptr, "%d %s %d %d", &code, name, &quantity, &price) != EOF)
    {
        OpeningStock[i] = quantity;
        i++;
    }
    fclose(fileptr);

    // FILE *fileptr;
    fileptr = fopen("Products Data.txt", "r");
    if (fileptr == NULL)
    {
        printf("\t\t\t\tCould not open the file. (! . !)\n");
        exit(1);
    }

    i = 0;
    while (fscanf(fileptr, "%d %s %d %d", &code, name, &quantity, &price) != EOF)
    {
        ClosingStock[i].code = code;
        strcpy(ClosingStock[i].name, name);
        ClosingStock[i].quantity = quantity;
        ClosingStock[i].price = price;
        i++;
    }

    float TotalSaleInAmount = 0, TotalCost = 0, TotalMarUp = 0;
    for (i = 0; i < productQuantity; i++)
    {
        // int SaleInAmount = ClosingStock[i].price * (OpeningStock[i] - ClosingStock[i].quantity);
        int SaleInAmount = ClosingStock[i].price * (ClosingStock[i].quantity - OpeningStock[i]);
        float Cost = SaleInAmount / 1.2;
        float MarkUp = SaleInAmount - Cost;
        TotalSaleInAmount += SaleInAmount;
        TotalCost += Cost;
        TotalMarUp += MarkUp;
        strcpy(Profits[i].name, ClosingStock[i].name);
        Profits[i].profit = round(MarkUp);
    }

    for (i = 0; i < productQuantity; i++)
    {
        for (j = i; j < productQuantity; j++)
        {
            if (Profits[i].profit < Profits[j].profit)
            {
                struct pro temp = Profits[j];
                Profits[j] = Profits[i];
                Profits[i] = temp;
            }
        }
    }

    for (i = 100; i >= 0; i -= 2)
    {
        if (i <= Profits[0].profit + 2)
        {
            // printf("i:%d\n",i);
            printf("\x1B[0;%dm", 29);
            printf("\t\t\t%d\t", i);
            int j;
            for (j = 0; j < 6; j++)
            {
                printf("\x1B[0;%dm", 30 + j);
                if (Profits[j].profit >= i)
                {
                    printf("\t%c", 219);
                }
                else
                {
                    printf("\t%c", 0);
                }
            }
            printf("\n");
        }
    }
    printf("\t\t");
    printf("\x1B[0;%dm", 29);
    for (i = 0; i < 9; i++)
    {
        printf("________");
    }
    printf("\n\n\t\t\tLegends:\n\t\t\t");
    for (i = 0; i < 6; i++)
    {
        printf("\x1B[0;%dm", 30 + i);
        printf("%c ", 254);
        printf("\x1B[0;%dm", 29);
        printf("%s\t", Profits[i].name);
    }

    printf("\x1B[1;%dm", 29);
    printf("\n\n\n\t\tProduct Name\t\tSale Per Unit\tSale in Amount\tCost\t\tMarkup/Profit\n\t\t");
    printf("\x1B[0;%dm", 29);
    for (i = 0; i < productQuantity; i++)
    {

        // int SaleInAmount = ClosingStock[i].price * (OpeningStock[i] - ClosingStock[i].quantity);
        int SaleInAmount = ClosingStock[i].price * (ClosingStock[i].quantity - OpeningStock[i]);
        float Cost = SaleInAmount / 1.2;
        float MarkUp = SaleInAmount - Cost;
        printf("%s\t\t\t%d\t\t%d\t\t%.2f\t\t%.2f\n\t\t", ClosingStock[i].name, ClosingStock[i].price, SaleInAmount, Cost, MarkUp);
    }

    for (i = 0; i < 11; i++)
    {
        printf("=======");
    }

    printf("\n\t\tTOTAL:\t\t\t\t\t%.2f\t\t%.2f\t\t%.2f\n\n", TotalSaleInAmount, TotalCost, TotalMarUp);
    free(OpeningStock);
    free(ClosingStock);
    free(Profits);

    fflush(stdin);
    printf("Press any key to go forward...\n");
    getchar();
}
void cashbook(int x, int y)
{
    int amt = x;
    int amt1 = y;
    time_t t; // not a primitive datatype

    time(&t);
    printf("\t\t\t=====================%s CASH BOOK %s======================\n\t\t\t\t   %sDATE:%s",AC_CYAN , AC_NORMAL,AC_GREEN, ctime(&t));
    // printf("\t\t\t\t\t    NOVEMBER 2022\n");
    printf("%s", AC_NORMAL);
    printf("\t\tDEBIT(RECIEPTS)\t\t\t\t\t\tCREDIT(PAYMENTS)\n");
    printf("  DATE\t\tDESCRIPTION\tQuantity\tAMOUNT\t|\tDATE\tDESCRIPTION\t\t\tAMOUNT\n");
    printf("2/11/2022\tApple\t\t  20\t\t%d/-\t|    5/11/2022\tNote Payable-Sattar sheikh\t%d/-\n", amt * 20, amt1 * 120);
    printf("6/11/2022\tRice\t\t  5\t\t%d/-\t|    5/11/2022\tSalary expense\t\t\t%d/-\n", amt * 5, amt1 * 145);
    printf("9/11/2022\tOil\t\t  30\t\t%d/-\t|    5/11/2022\tK-Electric Bill\t\t\t%d/-\n", amt * 30, amt1 * 111);
    printf("11/11/2022\tApple\t\t  25\t\t%d/-\t|    5/11/2022\tDrawings\t\t\t%d/-\n", amt * 25, amt1 * 50);
    printf("14/11/2022\tFish\t\t  40\t\t%d/-\t|    5/11/2022\tChai paani\t\t\t%d/-\n", amt * 40, amt1 * 130);
    printf("15/11/2022\tBanana\t\t  10\t\t%d/-\t|    5/11/2022\tNote Payable-Haseeb Dharwarwala\t%d/-\n", amt * 10, amt1 * 175);
    printf("16/11/2022\tRice\t\t  14\t\t%d/-\t|    5/11/2022\tLED light bulbs\t\t\t%d/-\n", amt * 14, amt1 * 25);
    printf("15/11/2022\tApple\t\t  7\t\t%d/-\t|    5/11/2022\tpedestrial fans\t\t\t%d/-\n", amt * 7, amt1 * 15);
    int t1 = (amt * 20) + (amt * 5) + (amt * 30) + (amt * 25) + (amt * 40) + (amt * 10) + (amt * 14) + (amt * 7);
    int t2 = (amt1 * 120) + (amt1 * 145) + (amt1 * 111) + (amt1 * 50) + (amt1 * 130) + (amt1 * 175) + (amt1 * 25) + (amt1 * 15);
    printf("\t\tTOTAL:\t\t\t\t%d/- |\t\tTOTAL:\t\t\t\t%d", t1, t2);
    printf("\nPress Any Key To Continue\n");
    getch();
}
float incomeStatement(int noOfEmp)
{
    float THELEADTERM = 1000.00f;
    printf("%s%s                            TINY TYCOON                          %s\n", COLOR_BOLD, AC_CYAN, COLOR_OFF);
    printf("%s%s===================== INCOME STATEMENT ======================%s\n", COLOR_BOLD, AC_GREEN, COLOR_OFF);
    printf("%s                 Year Ended: December 31, 2021\n", AC_BLUE);
    printf("%s", AC_NORMAL);
    // time_t t;
    // time(&t);
    printf("%sREVENUES: \n%s", COLOR_BOLD, COLOR_OFF);
    printf("\t\tInventory Sales:\t\t\t$%.2f\n", 2 * THELEADTERM + THELEADTERM * 88.0f / 100.0f);
    printf("\t\tCost Of Goods Sold:\t\t\t$%.2f\n", THELEADTERM * 140.f / 100.f);
    printf("%sEXPENSES: \n%s", COLOR_BOLD, COLOR_OFF);
    printf("\t\tAdevertising/Marketing Expense:\t\t$%.2f\n", THELEADTERM * 52 / 100.f);
    printf("\t\tSalary Expense: \t\t\t$%.2f\n", noOfEmp * THELEADTERM / 2);
    printf("\t\tRent Expense: \t\t\t\t$%.2f\n", THELEADTERM);
    printf("\t\tIncome Tax: \t\t\t\t$%.2f\n", THELEADTERM * 45 / 100);
    float total = (2 * THELEADTERM + THELEADTERM * 88.0f / 100.0f) + (THELEADTERM * 140.f / 100.f) - THELEADTERM * 52 / 100.f - (noOfEmp * THELEADTERM / 2) - (THELEADTERM) - (THELEADTERM * 45 / 100);
    printf("%sNET INCOME: \t\t\t\t$%.2f %s", COLOR_BOLD, total, COLOR_OFF);
    return total;
}
float RetainedEarnings(int e)
{
    float total = incomeStatement(e);
    printf("\n");
    printf("%s%s=============== Statement of Retained Earnings ===============%s\n", COLOR_BOLD, AC_GREEN, COLOR_OFF);
    printf("%s                 Year Ended: December 31, 2021\n", AC_BLUE);
    printf("%s", AC_NORMAL);
    printf("Retained Earnings, January 1 , 2021\t\t\t%.2f\n", 0.f);
    printf("Net Income For The Year\t\t\t\t\t%.2f\n", total);
    printf("Dividends\t\t\t\t\t\t%.2f\n", 0.f);
    printf("\nRetained Earnings, December 31, 2021 \t\t\t%.2f\n", total);
    return total;
}

int createBalanceSheet(emp)
{
    system("cls");
    float profit_loss = RetainedEarnings(emp);
    printf("\n\n");
    printf("%s%s====================== BALANCE SHEET ======================\n%s", COLOR_BOLD, AC_GREEN, COLOR_OFF);
    printf("%s                 Year Ended: December 31, 2021\n", AC_BLUE);
    printf("%s", AC_NORMAL);
    printf("%sAssets%s\n", COLOR_BOLD, COLOR_OFF);
    float KEYTERM = 10000.f;
    printf("Cash: \t\t\t\t\t\t\t$%.2f\n", KEYTERM * 2.4);
    printf("Account Recievable: \t\t\t\t\t$%.2f\n", KEYTERM * 0.85);
    printf("Inventory: \t\t\t\t\t\t$%.2f\n", KEYTERM * 1.5);
    printf("Prepaid Expenses: \t\t\t\t\t$%.2f\n", KEYTERM * 1);
    printf("------------------------------------\n");
    printf("%s%sTotal Assets%s%s", COLOR_BOLD, UNDERLINE, CLOSEUNDERLINE, COLOR_OFF);
    float assets = KEYTERM * 2.4 + KEYTERM * 0.85 + KEYTERM * 1.5 + KEYTERM * 1;
    printf("\t\t\t\t\t\t$%.2f\n\n", assets);
    printf("%sLiabilities%s\n", COLOR_BOLD, COLOR_OFF);
    printf("Accounts Payable: \t\t\t\t\t$%.2f\n", KEYTERM * 0.25);
    printf("Income Tax Payable: \t\t\t\t\t$%.2f\n", KEYTERM * 0.05);
    printf("Others Liabilities: \t\t\t\t\t$%.2f\n", KEYTERM * 1.45);
    printf("------------------------------------\n");
    printf("%s%sTotal Liabilities%s%s", COLOR_BOLD, UNDERLINE, CLOSEUNDERLINE, COLOR_OFF);
    float Liabilities = KEYTERM * 0.25 + KEYTERM * 0.05 + KEYTERM * 1.45;
    printf("\t\t\t\t\t$%.2f\n\n", Liabilities);
    float equity = assets - Liabilities;
    printf("%sShareholder Equity%s\n", COLOR_BOLD, COLOR_OFF);
    printf("Common Stock:\t\t\t\t\t\t$%.2f\n", equity - profit_loss);
    printf("Retained Earnings:\t\t\t\t\t$%.2f\n", profit_loss);
    printf("------------------------------------\n");
    printf("%s%sTotal Shareholder's Equity%s%s", COLOR_BOLD, UNDERLINE, CLOSEUNDERLINE, COLOR_OFF);
    printf("\t\t\t\t$%.2f\n\n", equity);

    getch();
}

int Accounts(void)
{
    system("cls");
    unsigned long int Inputed_Number, Customer_Number;
    int a_check, b_check, c_check, a = 0, x, cont = 1;
    char name[30];
    do
    {
        system("cls");
        printf("\t\t\t\tDo you have the membership card of our store ?\n\t\t\t\t\tYES\t\t1\n\t\t\t\t\tNo\t\t2\n\t\t\t\t\tExit\t\t3\n\t\t\tInput: ");
        scanf(" %d", &a_check);
    } while (a_check != 1 && a_check != 2 && a_check != 3);

    FILE *fileptr;
    if (a_check == 1)
    {
        fileptr = fopen("Customer Info.txt", "r");
        if (fileptr == NULL)
        {
            printf("\t\t\t\tCould not open the file. (! . !)\n");
            exit(1);
        }
        // cont means continue
        while (cont)
        {
            rewind(fileptr);
            fscanf(fileptr, " %d", &customer.code);
            int x = 0;
            printf("\t\t\t\tEnter Customer's mobile number:\n\t\t\t\t");
            scanf(" %lu", &Inputed_Number);
            while (fscanf(fileptr, "%d %s %lu", &customer.code, customer.name, &Customer_Number) != EOF)
            {
                if (Customer_Number == Inputed_Number)
                {
                    printf("\n\t\t\t\tCustomer Id\tName\t\tMobile Number\n");
                    printf("\t\t\t\t%d\t\t%s\t\t%lu\n", customer.code, customer.name, Customer_Number);
                    x = 1;
                    fclose(fileptr);
                    break;
                }
            }
            if (x == 1)
            {
                printf("\n\t\t\t\t     Welcome Back %s `\\(^o^)/`!\n", customer.name);
                fflush(stdin);
                printf("\t\t\t\t\tPress any key to continue.....");
                getchar();
                cont = 0;
            }
            else
            {
                printf("\t\t\t\t\tNO DATA FOUND(o_O)\n\n");
                printf("\t\t\tIf You Want To Input Agian\t\t1\n");
                printf("\t\t\tContinue Without Membership\t\t2\n\t\t\t\tInput: ");
                scanf(" %d", &b_check);
                if (b_check == 1 || b_check < 1)
                {
                    // system("cls");
                    RepeatOnInvalid1();
                    cont = 1;
                }
                else if (b_check == 2)
                {
                    customer.code = 0;
                    strcpy(customer.name, "Unknown");
                    cont = 0;
                }
                else
                {
                    RepeatOnInvalid1();
                }
            }
        }
        fclose(fileptr);
        return 1;
    }
    else if (a_check == 2)
    {
        do
        {
            printf("\t\t\t\tDo you want to become our member?\n\t\t\t\t\tYES\t\t1\n\t\t\t\t\tNo\t\t2\n\t\t\tInput: ");
            scanf(" %d", &c_check);
        } while (c_check != 1 && c_check != 2);

        if (c_check == 1)
        {
            char name2[30];
            x = 0;
            printf("\t\t\tEnter Customer's Name: ");
            fflush(stdin);
            gets(name2);
            printf("\t\t\tEnter Customer's Phone number: ");
            scanf(" %lu", &Inputed_Number);
            fileptr = fopen("Customer Info.txt", "r+");
            fscanf(fileptr, " %d", &customer.code);
            while (fscanf(fileptr, "%d %s %lu", &customer.code, customer.name, &Customer_Number) != EOF)
            {
                if (Customer_Number == Inputed_Number)
                {
                    printf("\n\t\t\t\tThis Number already exists in our Data Base.\n");
                    printf("\n\t\t\t\tCustomer Id\tName\t\tMobile Number\n\t\t\t\t%d\t\t%s\t\t%lu\n", customer.code, customer.name, Customer_Number);
                    x = 1;
                    fflush(stdin);
                    printf("\t\t\t\t\tPress any key to continue.....");
                    getchar();
                    return 1;
                    break;
                }
            }
            if (x == 0)
            {
                rewind(fileptr);
                fscanf(fileptr, " %d", &customer.code);
                fseek(fileptr, 0, SEEK_SET);
                fprintf(fileptr, "%d", ++customer.code);
                fseek(fileptr, 0, SEEK_END);
                fprintf(fileptr, "\n%d %s %lu", customer.code, name2, Inputed_Number);
                // return 1;
            }
            fclose(fileptr);
        }
        else if (c_check == 2)
        {
            customer.code = 0;
            strcpy(customer.name, "Unknown");
        }
        return 1;
    }
    else if (a_check == 3)
    {
        exit(0);
    }
}
int printing(FILE *ptr, struct items *product, struct items *cart, int productQuantity)
{
    int userCode, total = 0, tQuan = 0;
    // Accessing new data.
    int i = 0, j, k;
    while (fscanf(ptr, "%d %s %d %d", &product[i].code, product[i].name, &product[i].quantity, &product[i].price) != EOF)
    {
        i++;
    }

    printf("\n");
    printf("\t\t\t\t\tWELCOME TO MAAD MART\n");
    for (i = 0; i < 10; i++)
    {
        printf("===========");
    }
    printf("\n\tEmployee's Name: %s\n\tCustomer's Name: %s, ID: %d\n", employee.name, customer.name, customer.code);
    printf("\n\tInput 99 for special tools\n\tInput 100 to check out\n\n");
    for (i = 0; i < 10; i++)
    {
        printf("===========");
    }

    printf("\n\t\t\tPRODUCTS\t\t\t\t\tCART\n");
    for (i = 0; i < 10; i++)
    {
        printf("-----------");
    }
    printf("\nCODES\tPRODUCT NAMES\tQUANTITY\tPRICES   |   CODES\tPRODUCT NAMES\tQUANTITY\tPRICES\n");
    for (i = 0; i < 10; i++)
    {
        printf("-----------");
    }
    printf("\n");
    for (i = 0; i < productQuantity; i++)
    {
        printf("%i\t%s\t\t%i\t\t%i\t |", product[i].code, product[i].name, product[i].quantity, product[i].price);
        if (cart[i].quantity != 0)
        {
            printf("   %i\t%s\t\t%i\t\t%i", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price);
            // total += cart[i].quantity * cart[i].price;
            total += cart[i].price;
            tQuan += cart[i].quantity;
        }
        printf("\n");
    }
    printf("\t\t\t\t\t\t |      TOTAL : \t\t\t\t%d\n", total);

    for (i = 0; i < 10; i++)
    {
        printf("-----------");
    }

    fflush(stdin);
    printf("\nInput: ");
    scanf(" %d", &userCode);

    if (userCode == 99)
    {
        printf("SPECIAL TOOLS OPEN\n");
        int input_code, input_quantity, product_code;
        int choice, n, choice1, choice2, m, j;
        printf("\t\t\tTOOLS\t\t\t");
        printf("\nInput a code");
        printf("\nSelect your option:\nDelete an item from Cart\t\t1\nRemove all items from Cart\t\t2\nGo back\t\t\t\t\t3\n========\n");
        scanf("%d", &choice);

        switch (choice)
        {
        // DELETE AN ITEM
        case 1:
        {
            printf("\nDelete an item: ");

            do
            {
                printf("\n\tEnter the item code you want to delete: ");
                scanf(" %d", &product_code);

                if (product_code < 101 || product_code > 106)
                {
                    printf("Invalid Input!");
                    break;
                }

                int cont = 0;
                // cont = 1;
                for (i = 0; i <= countcart(cart); i++)
                {
                    if (product_code == cart[i].code)
                    {
                        printf("Enter quantity you want to remove: ");
                        scanf(" %d", &n);
                        if (n > cart[i].quantity || cart[i].quantity < 0 || n < 0)
                        {
                            printf("\nYour input is invalid. Please enter the quantity of your cart items only.");
                        }

                        else
                        {
                            cont = 1;
                            for (j = 0; j < countcart(cart); j++)
                            {
                                for (k = 0; k < productQuantity; k++)
                                {
                                    if (cart[j].code == product[k].code)
                                    {
                                        printf("Inside If\n");
                                        product[k].quantity += n;
                                        cart[j].quantity -= n;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    break;
                }

                printf("\nDo you want to remove any other item?\nPress 1 for yes\nPress 0 for no\n");
                scanf(" %d", &choice1);

                if (choice1 != 0 && choice1 != 1)
                {
                    printf("Invalid input");
                    break;
                }

            } while (choice1);

            return 1;
        }
            // REMOVE ALL ITEMS FROM CART
        case 2:
        {
            printf("Are you sure you want to remove all items from your cart?\nPress 1 to confirm: ");
            scanf(" %d", &choice2);
            if (choice2 == 1)
            {
                for (i = 0; i < countcart(cart); i++)
                {
                    for (j = 0; j < productQuantity; j++)
                    {
                        if (cart[i].code == product[j].code)
                        {
                            product[j].quantity += cart[i].quantity;
                            cart[i].quantity -= cart[i].quantity;
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("\nInvalid Input!");
            }
            break;
        }
        case 3:
        {
            printf("\n\t\tGo back to menu: ");
            break;
        }
        }
    }
    else if (userCode == 100)
    {

        system("cls");
        printf("\t\t\t\t\tMAAD MART\n  \t\t\tFAST CAMPUS Khi\n\t\t\tEMAIL: info@maad_mart.com.pk\n\t\t\tLOG ON: www.facebook.com/maad_supermart\n\t\t\tContact Number: 0298581844\n");

        printf("\n\t\t\tCustomer Name: %s", customer.name);
        printf("\t\tCustomer ID: %i", customer.code);
        printf("\n\t\t\tEmployee Name: %s", employee.name);

        printf("\n\t\t\t\t-------------------------------\n");

        printf("\t\t\t\t\t ORIGINAL RECIEPT\n");
        printf("\t\t\t\t-------------------------------\n");

        printf("\t\t\t\t\tProduct Description\n");
        printf("\t\t\tCODES\t  PRODUCT NAMES\t   QUANTITY\t PRICES");
        printf("\n\t\t\t-------------------------------------------------\n");
        for (i = 0; i < countcart(cart); i++)
        {
            printf("\n\t\t\t%i\t\t%s\t\t%i\t\t%i", cart[i].code, cart[i].name, cart[i].quantity, cart[i].price);
        }
        printf("\n\t\t\t-------------------------------------------------\n");

        printf("\n\n\t\t\tTotal items / quantity\t\t\t%i", tQuan);
        printf("\n\t\t\tDiscount\t\t\t\t%i", 0);
        printf("\n\t\t\tINVOICE VALUE\t\t\t\tRs.%i", total);
        updating_sales(total);
        printf("\n\t\t\t*************************************************");
        printf("\n\t\t\t\t\tThank You For Shopping\n");
        printf("\t\t\t*************************************************");

        printf("\n\n\t\t\tCHECKED OUT\n\t\t\tPress any key to continue ...");
        fflush(stdin);
        getchar();

        // NEW WORK
        FILE *fileptr, *temp;
        fileptr = fopen("Customer Data.txt", "r+");
        temp = fopen("Customer Data.txt", "r+");
        if (fileptr == NULL || temp == NULL)
        {
            printf("\t\t\t\tCould not open the file. (! . !)\n");
            exit(1);
        }

        int Customer_Number, found = 0;
        char name[30];
        char check[2];
        char c;
        while (fscanf(temp, "%s", check) != EOF)
        {
            if (strcmp(check, "ID") == 0)
            {
                fscanf(temp, "%d %s", &Customer_Number, name);
                if (Customer_Number == customer.code)
                {
                    found = 1;
                    printf("%d", ftell(temp));
                    fseek(fileptr, ftell(temp), SEEK_CUR);
                    float total = 0;
                    for (i = 0; i < countcart(cart); i++)
                    {
                        fprintf(fileptr, "\n%d\t", cart[i].code);
                        if (strlen(cart[i].name) <= 3)
                        {
                            fprintf(fileptr, "%s  \t%d\tRs %d\tRs %d", cart[i].name, cart[i].quantity, cart[i].price, cart[i].quantity * cart[i].price);
                        }
                        else
                        {
                            fprintf(fileptr, "%s\t%d\tRs %d\tRs %d", cart[i].name, cart[i].quantity, cart[i].price, cart[i].quantity * cart[i].price);
                        }
                        total += cart[i].quantity * cart[i].price;
                    }
                    fprintf(fileptr, "\nTOTAL:\t\t\t\t\tRs %.2f\n", total);
                    for (i = 0; i < 10; i++)
                    {
                        fprintf(fileptr, "...");
                    }
                    while ((c = fgetc(temp)) != EOF)
                    {
                        fprintf(fileptr, "%c", c);
                    }
                    break;
                }
            }
        }
        if (found == 0)
        {
            fseek(fileptr, 0, SEEK_END);
            fprintf(fileptr, "\nID\t%d\t%s", customer.code, customer.name);
            float total = 0;
            for (i = 0; i < countcart(cart); i++)
            {
                fprintf(fileptr, "\n%d\t", cart[i].code);
                if (strlen(cart[i].name) <= 3)
                {
                    fprintf(fileptr, "%s  \t%d\tRs %d\tRs %d", cart[i].name, cart[i].quantity, cart[i].price, cart[i].quantity * cart[i].price);
                }
                else
                {
                    fprintf(fileptr, "%s\t%d\tRs %d\tRs %d", cart[i].name, cart[i].quantity, cart[i].price, cart[i].quantity * cart[i].price);
                }

                total += cart[i].quantity * cart[i].price;
            }
            fprintf(fileptr, "\nTOTAL:\t\t\t\t\tRs %.2f\n", total);
            for (i = 0; i < 10; i++)
            {
                fprintf(fileptr, "___");
            }
        }

        fclose(fileptr);
        fclose(temp);

        // Cleaning Cart for next iteration
        for (i = 0; i < productQuantity; i++)
        {
            strcpy(cart[i].name, "");
            cart[i].code = NULL;
            cart[i].quantity = NULL;
            cart[i].price = NULL;
        }
        FILE *ptr2;
        ptr2 = fopen("Products.txt", "w");
        fprintf(ptr2, "%d\n", productQuantity);
        for (i = 0; i < productQuantity; i++)
        {
            fprintf(ptr2, "%d %s %d %d\n", product[i].code, product[i].name, product[i].quantity, product[i].price);
        }
        fclose(ptr2);
        return 0;
    }
    else
    {
        // checkCode = Flag if we are able to find the given code in our products list then "1" else "0"
        int checkCode = 0, cont, userQuantity;
        for (i = 0; i < productQuantity; i++)
        {
            if (userCode == product[i].code)
            {
                checkCode = 1;
                if (product[i].quantity != 0)
                {
                    do
                    {
                        cont = 0;
                        printf("Input the quantity: ");
                        scanf(" %d", &userQuantity);
                        if (userQuantity < 0 || userQuantity > product[i].quantity)
                        {
                            cont = 1;
                            printf("Invalid Input\n");
                            sleep(1);
                        }

                    } while (cont);

                    int present = -1;
                    for (j = 0; j < productQuantity; j++)
                    {
                        if (product[i].code == cart[j].code)
                        {

                            present = j;
                            break;
                        }
                    }
                    if (present > -1)
                    {
                        cart[present].quantity += userQuantity;
                        cart[present].price += userQuantity * product[i].price;
                        product[i].quantity -= userQuantity;
                    }
                    else
                    {
                        int count = 0;
                        while (cart[count].code > 0)
                        {
                            count++;
                        }
                        strcpy(cart[count].name, product[i].name);
                        cart[count].code = product[i].code;
                        cart[count].quantity = userQuantity;
                        cart[count].price = userQuantity * product[i].price;
                        product[i].quantity -= userQuantity;
                    }
                }
                else
                {
                    printf("%s Is Currently Out Of Stock\n", product[i].name);
                    sleep(2);
                }
                break;
            }
        }
        if (checkCode == 0)
        {
            printf("Given code is invalid (o_O)\n");
            fflush(stdin);
            printf("Press any key to continue ... ");
            getchar();
        }
        return 1;
    }
}
void RepeatOnInvalid1(void)
{
    system("cls");
    printf("\t\t\t\tDo you have the membership card of our store ?\n\t\t\t\t\tYES\t\t1\n\t\t\t\t\tNo\t\t2\n\t\t\tInput: ");
    printf("Input : 1\n");
}
int countcart(struct items *cart)
{
    int c = 0;
    while (cart[c].code > 0)
    {
        c++;
    }
    return c;
}
int adminPortal()
{
    int choice = 0;
    char masterID[20] = "panther";
    char adminID[20];
    int masterPassword = 10651;
    int adminPassword;
    do
    {
        system("cls");
        fflush(stdin);
        printf("\t\t\t\t\t    LOGIN PROTAL\n\n\t\t\tEnter username or ID: ");
        gets(adminID);
        printf("\t\t\tEnter password: ");
        scanf(" %d", &adminPassword);
        fflush(stdin);
        choice = 0;
        if (strcmp(adminID, masterID) != 0 || masterPassword != adminPassword)
        {
            printf("\n\n\t\t\t\t\tINVALID CREDENTIAL\n");
            if (strcmp(adminID, masterID) != 0)
            {
                printf("\n\n\t\t\t\t\tWRONG USERNAME\n");
            }
            else if (masterPassword != adminPassword)
            {
                printf("\n\n\t\t\t\t\tWRONG PASSWORD\n");
            }
            printf("\t\t\t\tSelect the respective option:\n");
            printf("\t\t\t\tGo Back\t\t\t\t1\n\t\t\t\tRe-Enter\t\t\t2\n");
            do
            {
                printf("\t\t\t\tInput: ");
                scanf(" %d", &choice);
                fflush(stdin);
            } while (choice != 1 && choice != 2);
        }
        else
        {
            choice = adminMenu();
        }

    } while (choice == 2);
    return 0;
}
int adminMenu()
{
    int choice = 1;

    while (choice)
    {
        do
        {
            system("cls");
            printf("\t\t\t\t\t    ADMIN PROTAL\n\t\t\t\tSelect the respective option\n");
            printf("\t\t\t\tAdd A Product\t\t\t1\n\t\t\t\tDelete A Product\t\t2\n\t\t\t\tAdd An Employee\t\t\t3\n\t\t\t\tRemove An Employee\t\t4\n\t\t\t\tReport Generation\t\t5\n\t\t\t\tCASH BOOK\t\t\t6\n\t\t\t\tBalanceSheet\t\t\t7\n\t\t\t\tLOG OUT\t\t\t\t8\n");
            printf("\t\t\t\tInput: ");
            fflush(stdin);
            scanf(" %d", &choice);
        } while (choice < 1 || choice > 7);
        switch (choice)
        {
        case 1:
        {
            choice = addProduct();
            break;
        }
        case 2:
        {
            choice = deleteProduct();
            break;
        }
        case 3:
        {
            choice = addEmploye();
            break;
        }
        case 4:
        {
            choice = remEmploye();
            break;
        }
        case 5:
        {
            // LoadingScreen();
            reportGenerationLoadingScreen();
            break;
        }
        case 6:
        {
            cashbook(125, 95);
            // sleep(1);
            break;
        }
        case 7:
        {
            createBalanceSheet(4);
            break;
        }
        case 8:
        {
            printf("\t\t\t\t      LOGING OUT ... `\\(^ o ^)/`\n");
            sleep(1);
            choice = 0;
            return 0;
            break;
        }
        default:
        {
            printf("\n\n\t\t\t\t\tINVALID INPUT @ . @\n");
            sleep(1);
        }
        }
        if (choice == 0)
        {
            break;
        }
    }
}

int addProduct()
{
    system("cls");
    int num;
    FILE *ptr1, *ptr2, *ptr02;
    ptr1 = fopen("Products Data.txt", "a+");
    ptr2 = fopen("Products.txt", "r");
    ptr02 = fopen("Products.txt", "r+");
    if (ptr1 == NULL && ptr2 == NULL && ptr02 == NULL)
    {
        printf("ERROR\n");
        exit(1);
    }
    int code, quantity, price, code_B, quantity_B, price_B;
    char name[20], name_B[20];

    fflush(stdin);
    printf("Enter the name of item you want to add to store: ");
    gets(name_B);
    if (strlen(name_B) == 0)
    {
        printf("INVALID NAME (* - *)\n");
        fclose(ptr1);
        fclose(ptr2);
        fclose(ptr02);
        sleep(1);
        return 1;
    }
    printf("Enter the price of \"%s\": ", name_B);
    scanf(" %d", &price_B);
    printf("Enter the quantity which will be available in the mart: ");
    scanf("%i", &quantity_B);

    fscanf(ptr2, "%d", &num);
    num++;
    fseek(ptr02, 0, SEEK_SET);
    fprintf(ptr02, "%d", num);

    while (fscanf(ptr2, "%d %s %d %d", &code, name, &quantity, &price) != EOF)
    {
        fprintf(ptr02, "\n%d %s %d %d", code, name, quantity, price);
    }

    code++;
    fprintf(ptr1, "\n%d %s %d %d", code, name_B, quantity_B, price_B);
    fseek(ptr02, 0, SEEK_END);
    fprintf(ptr02, "\n%d %s %d %d", code, name_B, quantity_B, price_B);
    printf("DONE! Now customers can buy %s by %i as code", name_B, code);
    sleep(1);
    fclose(ptr1);
    fclose(ptr2);
    fclose(ptr02);

    return 1;
}
int deleteProduct()
{
    system("cls");
    FILE *ptr1;
    ptr1 = fopen("./Products.txt", "r+");
    if (ptr1 == NULL)
    {
        printf("\t\t\t\tError in opening file.\n");
        sleep(1);
        exit(1);
    }

    int productQuantity, code, quantity, price, num, found = 0, cursor1;
    char name[20];
    fscanf(ptr1, "%d", &productQuantity);
    cursor1 = ftell(ptr1);
    printf("\t\t\t\tDELETE SECTION:\n\n");
    while (fscanf(ptr1, "%d %s %d %d", &code, name, &quantity, &price) != EOF)
    {
        printf("\t\t\t\t%d %s %d %d\n", code, name, quantity, price);
    }

    printf("\n\t\tEnter the code of the item you want to delete: ");
    scanf(" %d", &num);

    FILE *ptr2 = fopen("./copy.txt", "w+");
    if (ptr2 == NULL)
    {
        printf("\t\t\t\tError in opening file.\n");
        sleep(1);
        exit(1);
    }
    fprintf(ptr2, "%d\n", productQuantity - 1);
    fseek(ptr1, cursor1, SEEK_SET);
    while (fscanf(ptr1, "%d %s %d %d", &code, &name, &quantity, &price) != EOF)
    {
        found = 1;

        if (code != num)
        {
            fprintf(ptr2, "%d %s %d %d\n", code, name, quantity, price);
        }
    }
    fclose(ptr1);
    if (found == 0)
    {
        printf("\t\t\t\tINVALID CODE (@ o @)\n");
        sleep(1);
    }
    else
    {
        ptr1 = fopen("./Products.txt", "w+");
        fprintf(ptr1, "%d\n", productQuantity - 1);
        fseek(ptr2, cursor1, SEEK_SET);
        while (fscanf(ptr2, "%d %s %d %d", &code, name, &quantity, &price) != EOF)
        {
            fprintf(ptr1, "%d %s %d %d\n", code, name, quantity, price);
        }
        fclose(ptr1);
        fclose(ptr2);
    }

    return 1;
}
int addEmploye()
{
    system("cls");
    int code = 0;
    char name[30], emName[30];
    printf("\t\t\t\tADDING EMPLOYEE\n\n\t\t\t  Enter the name of employee: ");
    fflush(stdin);
    gets(name);
    if (strlen(name) < 1)
    {
        printf("\t\t\t\tINVALID NAME (@ o @)\n");
        sleep(1);
        return 1;
    }
    FILE *ptr;
    ptr = fopen("./Employees.txt", "a+");
    if (ptr == NULL)
    {
        printf("\t\t\t\tError in opening file\n");
        sleep(1);
    }
    while (fscanf(ptr, "%d %s", &code, emName) != EOF)
        ;
    if (code == 0)
    {
        code = 10001;
        fprintf(ptr, "%d %s\n", code, name);
    }
    else
    {
        code++;
        fprintf(ptr, "\n%d %s", code, name);
    }
    printf("\n\n\t\t\t\tEMPLOYEE NAME: %s\n\t\t\t\tCODE: %d\n", name, code);
    fclose(ptr);
    return 1;
}
int remEmploye()
{
    system("cls");
    int code1, code, found = 0;
    char name[30];
    printf("\t\t\t\tDELETING AN EMPLOYEE\n\n\t\t\t  Enter the unique ID of employee: ");
    fflush(stdin);
    scanf(" %d", &code1);

    FILE *ptr1;
    ptr1 = fopen("./Employees.txt", "r");
    if (ptr1 == NULL)
    {
        printf("\t\t\t\tError in opening file.\n");
        sleep(1);
        return 1;
    }

    while (fscanf(ptr1, "%d %s", &code, name) != EOF)
    {
        if (code == code1)
        {
            printf("\t\t\t\tName of Employee: %s\n\t\t\t\tID: %d\n\t\t\t\tHAS BEEN REMOVED", name, code);
            found = 1;
            rewind(ptr1);
            FILE *ptr2;
            ptr2 = fopen("./copy.txt", "w+");
            while (fscanf(ptr1, "%d %s", &code, name) != EOF)
            {
                if (code != code1)
                {
                    fprintf(ptr2, "%d %s\n", code, name);
                }
            }
            fclose(ptr1);
            ptr1 = fopen("Employees.txt", "w+");
            rewind(ptr2);
            while (fscanf(ptr2, "%d %s", &code, name) != EOF)
            {
                fprintf(ptr1, "%d %s\n", code, name);
            }
            fclose(ptr1);
            fclose(ptr2);
            break;
        }
    }

    if (found == 0)
    {
        printf("\t\t\t\tINVALID CODE (@ o @)\n");
        sleep(1);
    }
    return 1;
}
int employeePortal()
{
    int num, code, found = 0;
    char name[30];
    system("cls");
    printf("\t\t\t\t\t     EMPLOYEES PORTAL\n\t\t\t\tInput the unique ID of employee: ");
    fflush(stdin);
    scanf(" %d", &num);
    FILE *ptr = fopen("./Employees.txt", "r+");
    while (fscanf(ptr, "%d %s", &code, name) != EOF)
    {
        if (num == code)
        {
            employee.code = code;
            strcpy(employee.name, name);
            found = 1;
            printf("\n\t\t\t\t\tWELCOME \"%s\" `\\(^ o ^)/`", employee.name);
            sleep(1);
            fclose(ptr);
            return 1;
        }
    }
    if (found == 0)
    {
        printf("\t\t\t\t\tINVALID CREDENTIAL (@ o @)\n");
        sleep(1);
        return 0;
    }
}

void updating_sales(int total)
{
    monthly_sales = total;
    int sales;
    FILE *ptr = fopen("MonthlySales.txt", "r");
    if (ptr == NULL)
    {
        printf("\t\t\t\tCould not open the file. (! . !)\n");
        exit(1);
    }
    fscanf(ptr, " %d", &sales);
    monthly_sales += sales;
    fclose(ptr);
    FILE *ptr001 = fopen("MonthlySales.txt", "w");
    if (ptr001 == NULL)
    {
        printf("\t\t\t\tCould not open the file. (! . !)\n");
        exit(1);
    }
    fprintf(ptr001, "%d", monthly_sales);
    fclose(ptr001);
}
