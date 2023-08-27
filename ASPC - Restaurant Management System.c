/*
    CSE115 - Section 5
    Project Name: ASP.C - Restaurant Management System
    Project Group no.: 3
    Group Members:-
        1. Arman Mokammel - 2232450642
        2. Mahmuda Zannat Punny - 2231518642
        3. Soraiyah Samantha - 2231590642
*/

#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Account
{
    int ID;
    char Password[50];
    char Category[12];
    char Name[100];
};

struct Employee
{
    int ID;
    char Name[100];
    char Designation[20];
    int AccountID;
};

struct items
{
    char Item[20];
    float UPrice;
    float CPrice;
    int Qty;
};

struct menuItem
{
    int ID;
    char Item[20];
    float Price;
    float Cost;
};

struct orders
{
    char Customer[50];
    char Date[50];
    int numOfItems;
    char ServedBy[100];
    float Discount;
    struct items Itm[15];
};

void adminMenu(char Name[], int ID, char Category[]); //Arman
void orderMenu(char Name[], int ID, char Category[]); //Arman
void superAdmin(char Name[], int ID, char Category[]); //Arman
int createAccount(int superAdmin); //Soraiyah
void deleteAccount(int superAdmin); //Soraiyah
void addMenuItem(); //Punny
void updateItemMenu(); //Punny
void removeMenuItem(); //Punny
int viewItemMenu(int TOrder); //Punny
int viewAccounts(); //Soraiyah
int viewEmployees(); //Soraiyah
void addEmployee(int superAdmin); //Soraiyah
void removeEmployee(); //Punny
void updateEmployee(); //Soraiyah
void prt_Title(); //Arman
void prt_StartupScreen(); //Arman
void prt_Title2(); //Arman
void generateBill(char servedBy[]); //Arman
void viewBills(); //Arman
void searchBill(); //Arman
void checkFinances(); //Arman

struct Account act[30];
struct Employee employee[50];
struct menuItem mnItm[30];

void generateBillHeader(char name[], char date[], char servedBy[]) //Punny
{
    printf("----------------------------------------------------------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\nServed By: %s\n", servedBy);
    printf("----------------------------------------------------------------\n\n");
    printf("================================================================\n");
    printf("\xBA\tItem Name\t\xBA  QTY  \xBA  Unit Price  \xBA  Total Price  \xBA");
    printf("\n================================================================\n");
}

void generateBillBody(char item[], int qty, float price) //Punny
{
    printf("\xBA %-20s  \xBA  %-3d  \xBA  %-10.2f  \xBA  %-11.2f  \xBA", item, qty, price, qty * price);
    printf("\n----------------------------------------------------------------\n");
}

void generateBillFooter(float total, float discount) //Punny
{
    printf("\n");
    float dis = (discount/100) * total;
    float netTotal = total - dis;
    float SD = 0.1 * netTotal;
    float VAT = 0.05 * netTotal;
    float grandTotal = netTotal + SD + VAT;
    printf("----------------------------------------------------------------\n");
    printf("-GROSS TOTAL :                                 \xBA  %.2f\n", total);
    printf("-DISCOUNT @%.1f%s :\t                       \xBA -%-.2f\n", discount, "%", dis);
    printf("                                               -----------------\n");
    printf("-NET TOTAL :                                   \xBA  %.2f\n", netTotal);
    printf("                                               -----------------\n");
    printf("-SD (Included) @10.0%s :                        \xBA  %.2f\n", "%", SD);
    printf("-VAT. (Included) @5.0%s :                       \xBA  %.2f\n", "%", VAT);
    printf("----------------------------------------------------------------\n");
    printf("-GRAND TOTAL :                                 \xBA  %.2f\n", grandTotal);
    printf("----------------------------------------------------------------\n");
}

int main() //Arman
{
    int ID, flag = 0, flag2;
    int init = 1;
    char Password[50];
    struct Account account;
    FILE *fp;

    SetConsoleTitle("ASP.C - Restaurant Management System");

    while(1)
    {
        flag2 = 0;
        if(init)
        {
            init = 0;
            prt_StartupScreen();
            system("color 03");
        }
        system("cls");
        prt_Title();
        printf("Enter ID: ");
        scanf("%d", &ID);

        if(ID == 1229)
        {
            createAccount(1);
            continue;
        }

        printf("Enter Password: ");
        scanf("%s", Password);

        fp = fopen("Res-Accounts.dat", "r");

        while(fread(&account, sizeof(struct Account), 1, fp))
        {
            if(account.ID == ID)
            {
                if(strcmp(account.Password, Password) == 0)
                {
                    flag = 1;
                    break;
                }
                else
                {
                    flag2 = 1;
                    printf("Incorrect Password\n");
                    Sleep(1000);
                    break;
                }
            }
        }

        fclose(fp);

        if(flag == 0 && flag2 == 0)
        {
            printf("Account Not Found!");
            Sleep(1500);
        }
        else if(flag == 1)
        {
            flag = 0;
            if(strcmp(account.Category, "Admin") == 0)
            {
                adminMenu(account.Name, account.ID, account.Category);
            }
            else if(strcmp(account.Category, "Super-Admin") == 0)
            {
                superAdmin(account.Name, account.ID, account.Category);
            }
            else if(strcmp(account.Category, "Order") == 0)
            {
                orderMenu(account.Name, account.ID, account.Category);
            }
        }
    }

    return 0;
}

void orderMenu(char Name[], int ID, char Category[])
{
    int cho = -1;
    while(cho != 0)
    {
        system("cls");
        prt_Title();
        printf("Welcome %s - %s(%d)\n\n", Name, Category, ID);

        printf("---Please select your preferred option from below---\n\n");
        printf("1. Generate Invoice\n");
        printf("2. Show all Invoices\n");
        printf("3. Search Invoice\n");
        printf("0. Logout\n\n");
        printf(">> ");
        scanf("%d", &cho);

        if(cho == 1)
        {
            generateBill(Name);
        }
        else if(cho == 2)
        {
            viewBills();
            system("pause");
        }
        else if(cho == 3)
        {
            searchBill();
            system("pause");
        }
    }
}

void adminMenu(char Name[], int ID, char Category[])
{
    int cho = -1;
    while(cho != 0)
    {
        system("cls");
        prt_Title();
        printf("Welcome %s - %s(%d)\n\n", Name, Category, ID);

        printf("---Please select your preferred option from below---\n\n");
        printf("1. Add/Remove Account\n");
        printf("2. Add/Remove Employee\n");
        printf("3. Check Finances\n");
        printf("4. Update/Add Menu Items\n");
        printf("0. Logout\n\n");
        printf(">> ");
        scanf("%d", &cho);

        if(cho == 1)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Account\n");
                printf("2. Remove Account\n");
                printf("3. View Accounts\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);
                if(cho2 == 1)
                {
                    createAccount(0);
                }
                else if(cho2 == 2)
                {
                    deleteAccount(0);
                }
                else if(cho2 == 3)
                {
                    viewAccounts();
                    system("pause");
                }
            }
        }
        else if(cho == 2)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Employee\n");
                printf("2. Remove Employee\n");
                printf("3. Update Employee\n");
                printf("4. View Employee\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);
                if(cho2 == 1)
                {
                    addEmployee(0);
                }
                else if(cho2 == 2)
                {
                    removeEmployee();
                }
                else if(cho2 == 3)
                {
                    updateEmployee();
                }
                else if(cho2 == 4)
                {
                    viewEmployees();
                    system("pause");
                }
            }
        }
        else if(cho == 3)
        {
            checkFinances();
        }
        else if(cho == 4)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Item\n");
                printf("2. Remove Item\n");
                printf("3. Update Item\n");
                printf("4. View Items\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);

                if(cho2 == 1)
                {
                    addMenuItem();
                }
                else if(cho2 == 2)
                {
                    removeMenuItem();
                }
                else if(cho2 == 3)
                {
                    updateItemMenu();
                }
                else if(cho2 == 4)
                {
                    viewItemMenu(0);
                    system("pause");
                }
            }
        }
    }
}

void superAdmin(char Name[], int ID, char Category[])
{
    int cho = -1;
    while(cho != 0)
    {
        system("cls");
        prt_Title();
        printf("Welcome %s - %s(%d)\n\n", Name, Category, ID);

        printf("---Please select your preferred option from below---\n\n");
        printf("1. Add/Remove Account\n");
        printf("2. Add/Remove Employee\n");
        printf("3. Take Order\n");
        printf("4. Check Finances\n");
        printf("5. Update/Add Menu Items\n");
        printf("0. Logout\n\n");
        printf(">> ");
        scanf("%d", &cho);

        if(cho == 1)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Account\n");
                printf("2. Remove Account\n");
                printf("3. View Accounts\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);
                if(cho2 == 1)
                {
                    createAccount(1);
                }
                else if(cho2 == 2)
                {
                    deleteAccount(1);
                }
                else if(cho2 == 3)
                {
                    viewAccounts();
                    system("pause");
                }
            }
        }
        else if(cho == 2)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Employee\n");
                printf("2. Remove Employee\n");
                printf("3. Update Employee\n");
                printf("4. View Employee\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);
                if(cho2 == 1)
                {
                    addEmployee(1);
                }
                else if(cho2 == 2)
                {
                    removeEmployee();
                }
                else if(cho2 == 3)
                {
                    updateEmployee();
                }
                else if(cho2 == 4)
                {
                    viewEmployees();
                    system("pause");
                }
            }
        }
        else if(cho == 3)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();

                printf("---Please select your preferred option from below---\n\n");
                printf("1. Generate Invoice\n");
                printf("2. Show all Invoices\n");
                printf("3. Search Invoice\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);

                if(cho2 == 1)
                {
                    generateBill(Name);
                }
                else if(cho2 == 2)
                {
                    viewBills();
                    system("pause");
                }
                else if(cho2 == 3)
                {
                    searchBill();
                    system("pause");
                }
            }
        }
        else if(cho == 4)
        {
            checkFinances();
        }
        else if(cho == 5)
        {
            int cho2 = -1;
            while(cho2 != 0)
            {
                system("cls");
                prt_Title();
                printf("---Please select your preferred option from below---\n\n");
                printf("1. Add Item\n");
                printf("2. Remove Item\n");
                printf("3. Update Item\n");
                printf("4. View Items\n");
                printf("0. Go back\n\n");
                printf(">> ");
                scanf("%d", &cho2);

                if(cho2 == 1)
                {
                    addMenuItem();
                }
                else if(cho2 == 2)
                {
                    removeMenuItem();
                }
                else if(cho2 == 3)
                {
                    updateItemMenu();
                }
                else if(cho2 == 4)
                {
                    viewItemMenu(0);
                    system("pause");
                }
            }
        }
    }
}

int viewAccounts()
{
    FILE *fp;
    fp = fopen("Res-Accounts.dat", "r");
    int i = 0;

    system("cls");
    prt_Title();

    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\xBA  Account ID  \xBA  Account Name          \xBA  Account Category  \xBA\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

    while(fread(&act[i], sizeof(struct Account), 1, fp))
    {
        printf("\xBA  %-10d  \xBA  %-20s  \xBA      %-12s  \xBA\n", act[i].ID, act[i].Name, act[i].Category);
        printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
        i++;
    }

    printf("\n");

    fclose(fp);

    return i;
}

void deleteAccount(int superAdmin)
{
    int id;
    FILE *fp;

    while(1)
    {
        int i = 0, Found = 0;

        i = viewAccounts();

        printf("Enter the ID of the account you want to delete or enter 0 to go back: ");
        scanf("%d", &id);

        if(id == 0)
        {
            break;
        }

        int k;
        for(k = 0; k < i; k++)
        {
            if(act[k].ID == id)
            {
                Found = 1;
                break;
            }
        }

        if(!Found)
        {
           printf("Incorrect account ID!");
           Sleep(1000);
           continue;
        }

        if(!superAdmin && (strcmp(act[k].Category, "Super-Admin") == 0))
        {
            printf("Cannot delete Super-Admin accounts!");
            Sleep(1500);
            continue;
        }

        fp = fopen("Res-Accounts.dat", "w");

        for(int j = 0; j < i; j++)
        {
            if(act[j].ID != id)
            {
                fwrite(&act[j], sizeof(struct Account), 1, fp);
            }
        }

        printf("Account %d deleted successfully!", id);
        Sleep(1000);
        fclose(fp);
    }
}

int createAccount(int superAdmin)
{
    int flag = 0;
    FILE *fp;
    struct Account account;

    while(flag == 0)
    {
        int accountType;
        system("cls");
        prt_Title();
        printf("Enter account type:\n");
        printf("1. [Order]\n");
        printf("2. [Admin]\n");
        if(superAdmin)
        {
            printf("3. [Super-Admin]\n");
        }
        printf("\n>> ");
        scanf("%d", &accountType);

        switch(accountType)
        {
        case 1:
            strcpy(account.Category, "Order");
            flag = 1;
            break;
        case 2:
            strcpy(account.Category, "Admin");
            flag = 1;
            break;
        case 3:
            if(superAdmin)
            {
                strcpy(account.Category, "Super-Admin");
                flag = 1;
            }
            break;
        }
    }

    printf("Set account ID: ");
    scanf("%d", &account.ID);
    printf("Set account Password: ");
    scanf("%s", account.Password);
    printf("Set account Name: ");
    scanf(" %[^\n]s", account.Name);

    fp = fopen("Res-Accounts.dat", "a+");
    fwrite(&account, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("Account saved successfully!!\n");
    Sleep(1000);
    return account.ID;
}

int viewEmployees()
{
    FILE *fp;
    fp = fopen("Res-Employees.dat", "r");
    int i = 0;

    system("cls");
    prt_Title();

    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\xBA  Employee ID  \xBA\tEmployee Name\t        \xBA  Employee Designation  \xBA  Account ID  \xBA\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

    while(fread(&employee[i], sizeof(struct Employee), 1, fp))
    {
        printf("\xBA    %-10d \xBA   %-20s\t\xBA  %-16s\t \xBA  %-10d  \xBA\n", employee[i].ID, employee[i].Name, employee[i].Designation, employee[i].AccountID);
        printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
        i++;
    }

    printf("\n");

    fclose(fp);
    return i;
}

void addEmployee(int superAdmin)
{
    struct Employee empl;
    char cho;
    FILE *fp;

    while(1)
    {
        viewEmployees();

        printf("Enter Employee Name or Enter 0 to go back: ");
        scanf(" %[^\n]s", empl.Name);
        if(strcmp(empl.Name,"0") == 0)
        {
            break;
        }
        printf("Enter Designation of Employee: ");
        scanf(" %[^\n]s", empl.Designation);
        printf("Enter Employee ID: ");
        scanf(" %d", &empl.ID);
        empl.AccountID = -1;
        printf("Does the employee have an account [y/n]? : ");
        scanf(" %c", &cho);
        if(cho == 'y')
        {
            printf("Enter account ID: ");
            scanf(" %d", &empl.AccountID);
        }
        else if(cho == 'n')
        {
            printf("Do you want to create a new account for this employee [y/n]? : ");
            scanf(" %c", &cho);

            if(cho == 'y')
            {
                int id = createAccount(superAdmin);
                empl.AccountID = id;
            }
        }

        fp = fopen("Res-Employees.dat", "a");

        fwrite(&empl, sizeof(struct Employee), 1, fp);

        fclose(fp);
    }
}

void removeEmployee()
{
    FILE *fp;
    int id;

    while(1)
    {
        int i = 0, Found = 0;

        i = viewEmployees();

        printf("Enter the ID of the employee you want to delete or Enter 0 to go back: ");
        scanf("%d", &id);

        if(id == 0)
        {
            break;
        }

        for(int j = 0; j < i; j++)
        {
            if(employee[j].ID == id)
            {
                Found = 1;
                break;
            }
        }

        if(!Found)
        {
           printf("Incorrect employee ID!");
           Sleep(1000);
           continue;
        }

        fp = fopen("Res-Employees.dat", "w");

        for(int j = 0; j < i; j++)
        {
            if(employee[j].ID != id)
            {
                fwrite(&employee[j], sizeof(struct Employee), 1, fp);
            }
        }

        printf("Employee %d deleted successfully!", id);

        fclose(fp);
    }
}

void updateEmployee()
{
    FILE *fp;
    int id, cho = -1;

    while(1)
    {
        int i = 0, Found = 0;

        i = viewEmployees();

        printf("Enter the ID of the employee you want to update or Enter 0 to go back: ");
        scanf("%d", &id);

        if(id == 0)
        {
            break;
        }

        for(int j = 0; j < i; j++)
        {
            if(employee[j].ID == id)
            {
                Found = 1;
                break;
            }
        }

        if(!Found)
        {
           printf("Incorrect employee ID!");
           Sleep(1000);
           continue;
        }

        while(cho != 0)
        {
            printf("---Please select your preferred option from below---\n\n");
            printf("1. Change Employee Name\n");
            printf("2. Change Employee Designation\n");
            printf("3. Change Employee Account ID\n");
            printf("0. To go back\n");
            printf("\n>> ");
            scanf("%d", &cho);

            if(cho == 1)
            {
                char n_name[100];
                printf("Enter new name: ");
                scanf(" %[^\n]s", n_name);

                fp = fopen("Res-Employees.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(employee[j].ID == id)
                    {
                        strcpy(employee[j].Name, n_name);
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                    else
                    {
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                }

                fclose(fp);

                printf("Employee %d updated successfully!", id);
                Sleep(1500);
                break;
            }
            else if(cho == 2)
            {
                char n_designation[20];
                printf("Enter new designation: ");
                scanf(" %[^\n]s", n_designation);

                fp = fopen("Res-Employees.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(employee[j].ID == id)
                    {
                        strcpy(employee[j].Designation, n_designation);
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                    else
                    {
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                }

                fclose(fp);

                printf("Employee %d updated successfully!", id);
                Sleep(1500);
                break;
            }
            else if(cho == 3)
            {
                int n_id;
                char cho;

                printf("Does the employee have a new account [y/n]? : ");
                scanf(" %c", &cho);
                if(cho == 'y')
                {
                    printf("Enter account ID: ");
                    scanf(" %d", &n_id);
                }
                else if(cho == 'n')
                {
                    printf("Do you want to create a new account for this employee [y/n]? : ");
                    scanf(" %c", &cho);

                    if(cho == 'y')
                    {
                        n_id = createAccount(1);
                    }
                    else
                    {
                        n_id = -1;
                    }
                }

                fp = fopen("Res-Employees.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(employee[j].ID == id)
                    {
                        employee[j].AccountID = n_id;
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                    else
                    {
                        fwrite(&employee[j], sizeof(struct Employee), 1, fp);
                    }
                }

                fclose(fp);

                printf("Employee %d updated successfully!", id);
                Sleep(1500);
                break;
            }
        }
    }
}

int viewItemMenu(int TOrder)
{
    FILE *fp;
    fp = fopen("Res-Menu.dat", "r");

    int i = 0;

    system("cls");
    prt_Title();

    if(TOrder)
    {
        printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
        printf("\xBA  Item ID  \xBA\tItem Name\t        \xBA   Price      \xBA\n");
        printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

        while(fread(&mnItm[i], sizeof(struct menuItem), 1, fp))
        {
            printf("\xBA    %-5d  \xBA\t%-17s\t\xBA   %-8.2f   \xBA\n", mnItm[i].ID, mnItm[i].Item, mnItm[i].Price);
            printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
            i++;
        }
    }
    else
    {
        printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
        printf("\xBA  Item ID  \xBA\tItem Name\t        \xBA   Price      \xBA   Cost Price  \xBA\n");
        printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

        while(fread(&mnItm[i], sizeof(struct menuItem), 1, fp))
        {
            printf("\xBA    %-5d  \xBA\t%-17s\t\xBA   %-8.2f   \xBA   %-8.2f    \xBA\n", mnItm[i].ID, mnItm[i].Item, mnItm[i].Price, mnItm[i].Cost);
            printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
            i++;
        }
    }

    printf("\n");

    fclose(fp);

    return i;
}

void addMenuItem()
{
    FILE *fp;
    struct menuItem mItem;

    while(1)
    {
        system("cls");
        prt_Title();

        viewItemMenu(0);

        printf("Enter Item Name or Enter 0 to go back: ");
        scanf(" %[^\n]s", mItem.Item);
        if(strcmp(mItem.Item, "0") == 0)
        {
            break;
        }
        printf("Enter Item Price: ");
        scanf(" %f", &mItem.Price);
        printf("Enter Item Making Cost: ");
        scanf(" %f", &mItem.Cost);
        printf("Enter Item ID: ");
        scanf(" %d", &mItem.ID);

        fp = fopen("Res-Menu.dat", "a");

        fwrite(&mItem, sizeof(struct menuItem), 1, fp);

        fclose(fp);
        printf("Item added successfully!");
        Sleep(1500);
    }
}

void removeMenuItem()
{
    int id;
    FILE *fp;

    while(1)
    {
        int i = 0, Found = 0;

        i = viewItemMenu(0);

        printf("Enter the ID of the item you want to delete or enter 0 to go back: ");
        scanf("%d", &id);

        if(id == 0)
        {
            break;
        }

        for(int j = 0; j < i; j++)
        {
            if(mnItm[j].ID == id)
            {
                Found = 1;
                break;
            }
        }

        if(!Found)
        {
           printf("Incorrect item ID!");
           Sleep(1000);
           continue;
        }

        fp = fopen("Res-Menu.dat", "w");

        for(int j = 0; j < i; j++)
        {
            if(mnItm[j].ID != id)
            {
                fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
            }
        }

        printf("Item %d deleted successfully!", id);

        fclose(fp);
    }
}

void updateItemMenu()
{
    int id, cho = -1;
    FILE *fp;

    while(1)
    {
        int i = 0, Found = 0;

        i = viewItemMenu(0);

        printf("Enter the ID of the item you want to update or enter 0 to go back: ");
        scanf("%d", &id);
        if(id == 0)
        {
            break;
        }

        for(int j = 0; j < i; j++)
        {
            if(mnItm[j].ID == id)
            {
                Found = 1;
                break;
            }
        }

        if(!Found)
        {
           printf("Incorrect item ID!");
           Sleep(1000);
           continue;
        }

        while(cho != 0)
        {
            printf("---Please select your preferred option from below---\n\n");
            printf("1. Change Item Name\n");
            printf("2. Change Item Price\n");
            printf("3. Change Item Cost Price\n");
            printf("0. To go back\n");
            printf("\n>> ");
            scanf("%d", &cho);

            if(cho == 1)
            {
                char n_name[20];
                printf("Enter new name: ");
                scanf(" %[^\n]s", n_name);

                fp = fopen("Res-Menu.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(mnItm[j].ID == id)
                    {
                        strcpy(mnItm[j].Item, n_name);
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                    else
                    {
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                }

                fclose(fp);
                printf("Item %d updated successfully!", id);
                Sleep(1500);
                break;
            }
            else if(cho == 2)
            {
                float n_price;
                printf("Enter new price: ");
                scanf(" %f", &n_price);

                fp = fopen("Res-Menu.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(mnItm[j].ID == id)
                    {
                        mnItm[j].Price = n_price;
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                    else
                    {
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                }

                fclose(fp);
                printf("Item %d updated successfully!", id);
                Sleep(1500);
                break;
            }
            else if(cho == 3)
            {
                float n_price;
                printf("Enter new cost price: ");
                scanf(" %f", &n_price);

                fp = fopen("Res-Menu.dat", "w");

                for(int j = 0; j < i; j++)
                {
                    if(mnItm[j].ID == id)
                    {
                        mnItm[j].Cost = n_price;
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                    else
                    {
                        fwrite(&mnItm[j], sizeof(struct menuItem), 1, fp);
                    }
                }

                fclose(fp);
                printf("Item %d updated successfully!", id);
                Sleep(1500);
                break;
            }
        }
    }
}

void viewBills()
{
    struct orders pOrd;
    FILE *fp;
    system("cls");
    prt_Title2();
    fp = fopen("Res-Invoices.dat", "r");
    printf("\n\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE Your Previous Invoices \xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n\n");

    while(fread(&pOrd, sizeof(struct orders), 1, fp))
    {
        float total = 0;
        generateBillHeader(pOrd.Customer, pOrd.Date, pOrd.ServedBy);
        for (int i = 0; i < pOrd.numOfItems; i++)
        {
            generateBillBody(pOrd.Itm[i].Item, pOrd.Itm[i].Qty, pOrd.Itm[i].UPrice);
            total += pOrd.Itm[i].UPrice * pOrd.Itm[i].Qty;
        }
        generateBillFooter(total, pOrd.Discount);
        printf("\n\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n\n");
    }
    fclose(fp);
}

void generateBill(char servedBy[])
{
    struct orders ord;
    int id, x, total = 0;
    char saveBill = 'n';
    FILE *fp;

    system("cls");
    printf("\nPlease enter name of the customer: ");
    scanf(" %[^\n]s", ord.Customer);
    strcpy(ord.Date, __DATE__);
    printf("Please enter the number of items: ");
    scanf(" %d", &ord.numOfItems);

    x = viewItemMenu(1);

    for (int i = 0; i < ord.numOfItems; i++)
    {
        printf("Please enter the ID for Item-%d: ", i + 1);
        scanf("%d", &id);

        for(int j = 0; j < x; j++)
        {
            if(mnItm[j].ID == id)
            {
                strcpy(ord.ServedBy, servedBy);
                strcpy(ord.Itm[i].Item, mnItm[j].Item);

                printf("Please enter the quantity for the item: ");
                scanf(" %d", &ord.Itm[i].Qty);

                ord.Itm[i].UPrice = mnItm[j].Price;
                ord.Itm[i].CPrice = mnItm[j].Cost * ord.Itm[i].Qty;
                total += ord.Itm[i].UPrice * ord.Itm[i].Qty;
            }
        }
    }
    printf("Please enter Discount %s: ", "%");
    scanf(" %f", &ord.Discount);

    system("cls");
    prt_Title2();
    generateBillHeader(ord.Customer, ord.Date, servedBy);
    for (int i = 0; i < ord.numOfItems; i++)
    {
        generateBillBody(ord.Itm[i].Item, ord.Itm[i].Qty, ord.Itm[i].UPrice);
    }
    generateBillFooter(total, ord.Discount);

    printf("\nDo you want to save the invoice [y/n]? : ");
    scanf(" %c",&saveBill);

    if(saveBill == 'y')
    {
        fp = fopen("Res-Invoices.dat", "a");
        fwrite(&ord, sizeof(struct orders), 1, fp);

        fclose(fp);
    }
    Sleep(3000);
}

void searchBill()
{
    struct orders pOrd;
    int invoiceFound = 0;
    FILE *fp;
    char name[50];

    printf("Enter the name of the customer: ");
    scanf(" %[^\n]s", name);
    system("cls");
    prt_Title2();
    printf("\n\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE Invoices of %-20s \xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n", name);
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n\n");

    fp = fopen("Res-Invoices.dat", "r");
    while(fread(&pOrd, sizeof(struct orders), 1, fp))
    {
        float total = 0;
        if(strcmp(pOrd.Customer, name) == 0)
        {
            generateBillHeader(pOrd.Customer, pOrd.Date, pOrd.ServedBy);
            for (int i = 0; i < pOrd.numOfItems; i++)
            {
                generateBillBody(pOrd.Itm[i].Item, pOrd.Itm[i].Qty, pOrd.Itm[i].UPrice);
                total += pOrd.Itm[i].UPrice * pOrd.Itm[i].Qty;
            }
            generateBillFooter(total, pOrd.Discount);
            invoiceFound = 1;
        }
    }
    if(!invoiceFound)
    {
        printf("\nSorry the invoice for %s does not exist!\n\n", name);
    }
    fclose(fp);
}

void checkFinances()
{
    FILE *fp;
    struct orders pOrd;
    char Itms[30][21];
    float Prc[30], Cst[30];
    int Qty[30];
    int n_orders = 0;
    float GP = 0, TDiscount = 0, SD = 0, VAT = 0;

    int i = 0;

    fp = fopen("Res-Invoices.dat", "r");

    while(fread(&pOrd, sizeof(struct orders), 1, fp))
    {
        float Total = 0;
        n_orders++;
        for(int j = 0; j < pOrd.numOfItems; j++)
        {
            int flg = 0, k = 0;

            Total += pOrd.Itm[j].UPrice * pOrd.Itm[j].Qty;

            for(; k <= i; k++)
            {
                if(strcmp(Itms[k], pOrd.Itm[j].Item) == 0)
                {
                    flg = 1;
                    break;
                }
            }

            if(flg == 1)
            {
                Qty[k] += pOrd.Itm[j].Qty;
                Cst[k] += pOrd.Itm[j].CPrice;
                Prc[k] += pOrd.Itm[j].UPrice * pOrd.Itm[j].Qty;
                if(j == pOrd.numOfItems - 1)
                {
                    TDiscount += (pOrd.Discount/100) * Total;
                    SD += (Total - ((pOrd.Discount/100) * Total)) * 0.1;
                    VAT += (Total - ((pOrd.Discount/100) * Total)) * 0.05;
                }
            }
            else
            {
                strcpy(Itms[i], pOrd.Itm[j].Item);
                Cst[i] = pOrd.Itm[j].CPrice;
                Prc[i] = pOrd.Itm[j].UPrice * pOrd.Itm[j].Qty;
                Qty[i] = pOrd.Itm[j].Qty;
                if(j == pOrd.numOfItems - 1)
                {
                    TDiscount += (pOrd.Discount/100) * Total;
                    SD += (Total - ((pOrd.Discount/100) * Total)) * 0.1;
                    VAT += (Total - ((pOrd.Discount/100) * Total)) * 0.05;
                }
                i++;
            }
        }
    }
    fclose(fp);

    system("cls");
    prt_Title();

    printf("No. of orders: %d\n\n", n_orders);

    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\xBA\tItem Name\t        \xBA  QTY  \xBA  Cost Price  \xBA    Price      \xBA    Profit     \xBA\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

    for(int a = 0; a < i; a++)
    {
        GP += Prc[a] - Cst[a];
        printf("\xBA\t%-17s\t\xBA  %-3d  \xBA   %-8.2f   \xBA   %-8.2f    \xBA   %-8.2f    \xBA\n", Itms[a], Qty[a], Cst[a], Prc[a], Prc[a] - Cst[a]);
        printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    }

    printf("\t\t\t\t\t\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\t\t\t\t\t\xBA  Gross Profit:               \xBA   %-8.2f    \xBA\n", GP);
    printf("\t\t\t\t\t\xBA  Total Discounts Given:      \xBA  -%-8.2f    \xBA\n", TDiscount);
    printf("\t\t\t\t\t\xBA                              \xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    printf("\t\t\t\t\t\xBA  Net Profit:                 \xBA   %-8.2f    \xBA\n", GP - TDiscount);
    printf("\t\t\t\t\t\xBA                              \xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    printf("\t\t\t\t\t\xBA  SD:                         \xBA   %-8.2f    \xBA\n", SD);
    printf("\t\t\t\t\t\xBA  VAT:                        \xBA   %-8.2f    \xBA\n", VAT);
    printf("\t\t\t\t\t\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");

    printf("\n\nTop 5 most selling items :\t\t\t\t Top 5 item with max profit :\n\n");

    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\t\t\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");
    printf("\xBA\tItem Name\t        \xBA  QTY  \xBA\t\t\xBA\tItem Name\t        \xBA  Profit    \xBA\n");
    printf("\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\t\t\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\n");


    for(int a = 1; a <= 5; a++)
    {
        int max1 = Qty[0], index = 0, index2 = 0;
        float max2 = Prc[0] - Cst[0];
        for(int b = 1; b < i; b++)
        {
            if(max1 < Qty[b])
            {
                max1 = Qty[b];
                index = b;
            }

            if(max2 < Prc[b] - Cst[b])
            {
                max2 = Prc[b] - Cst[b];
                index2 = b;
            }
        }
        Qty[index] = 0;
        Prc[index2] = 0;
        Cst[index2] = 0;

        printf("\xBA\t%-17s\t\xBA  %-3d  \xBA\t\t\xBA\t%-17s\t\xBA  %-8.2f  \xBA\n", Itms[index], max1, Itms[index2], max2);
        printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\t\t\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    }
    printf("\n");

    system("pause");
}

void prt_Title()
{
    printf("\n");
    printf("   \xDB\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    printf("  \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB   \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\n");
    printf("  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC   \xDB\xDB\xBA     \n");
    printf("  \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBA \xC8\xCD\xCD\xCD\xCD\xDB\xDB\xBA \xDB\xDB\xC9\xCD\xCD\xCD\xBC    \xDB\xDB\xBA     \n");
    printf("  \xDB\xDB\xBA  \xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xBA     \xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    printf("  \xC8\xCD\xBC  \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC\n\n\n");
}

void prt_Title2()
{
    printf("\n");
    printf("              \xDB\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    printf("             \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB   \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\n");
    printf("             \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC   \xDB\xDB\xBA     \n");
    printf("             \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBA \xC8\xCD\xCD\xCD\xCD\xDB\xDB\xBA \xDB\xDB\xC9\xCD\xCD\xCD\xBC    \xDB\xDB\xBA     \n");
    printf("             \xDB\xDB\xBA  \xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xBA     \xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    printf("             \xC8\xCD\xBC  \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC\n\n");
    printf("              Plot-21, Gulshan Avenue, Gulshan-1,\n");
    printf("                    Dhaka-1213, Bangladesh\n");
    printf("                      Phone# 01711275323\n");
}

void prt_StartupScreen()
{
    system("color 04");
    Sleep(200);
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("                                      \xDB\xDB\xDB\xDB\xDB\xBB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xBB     \xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    Sleep(500);
    printf("                                     \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBB   \xDB\xDB\xC9\xCD\xCD\xCD\xCD\xBC\n");
    Sleep(500);
    printf("                                     \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBB \xDB\xDB\xDB\xDB\xDB\xDB\xC9\xBC   \xDB\xDB\xBA     \n");
    Sleep(500);
    printf("                                     \xDB\xDB\xC9\xCD\xCD\xDB\xDB\xBA \xC8\xCD\xCD\xCD\xCD\xDB\xDB\xBA \xDB\xDB\xC9\xCD\xCD\xCD\xBC    \xDB\xDB\xBA     \n");
    Sleep(500);
    printf("                                     \xDB\xDB\xBA  \xDB\xDB\xBA \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xBA \xDB\xDB\xBA     \xDB\xDB\xBB\xC8\xDB\xDB\xDB\xDB\xDB\xDB\xBB\n");
    Sleep(500);
    printf("                                     \xC8\xCD\xBC  \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xBC     \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC\n");
    Sleep(3500);
}
