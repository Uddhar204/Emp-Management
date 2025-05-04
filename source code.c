#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void menu();  //functions used
void add();
void view();
void search();
void edit();
void del();

struct emp {        //structure
    int id, age, salary;
    char name[40];
};

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {            //main Function//
    gotoxy(15, 8);
    printf("| Employee management system |");
    gotoxy(19, 15);
    printf("Press any key to continue");
    getch();
    menu();
    return 0;
}

void menu() {           //Menu function//
    int choice;
    system("cls");
    gotoxy(20, 3);
    printf("| MENU |");
    gotoxy(10, 4);
    printf("1. Press 1 to create new record.");
    gotoxy(10, 5);
    printf("2. Press 2 to view all records.");
    gotoxy(10, 6);
    printf("3. Press 3 to edit a record.");
    gotoxy(10, 7);
    printf("4. Press 4 to search for a record.");
    gotoxy(10,8);
    printf("5. Press 5 to delete a record.");
    gotoxy(10, 9);
    printf("6. Press 6 to exit.");
    gotoxy(10, 11);
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            view();
            break;
        case 3:
            edit();
            break;
        case 4 :
            search();
            break;
        case 5:
            del();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
            getch();
            menu();
    }
}

void add() {            //Add function
    FILE *fp;
    struct emp std;
    char another = 'y';
    system("cls");

    fp = fopen("record.dat", "ab+");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    fflush(stdin);
    while (another == 'y' || another == 'Y') {
            system("cls");
        gotoxy(10, 3);
        printf("| ADD RECORD |");
        gotoxy(10, 5);
        printf("Enter the details of employee.");
        gotoxy(10, 6);
        printf("Enter Employee Id: ");
        scanf("%d", &std.id);
        fflush(stdin);
        gotoxy(10, 7);
        printf("Enter the name of the employee: ");
        gets(std.name);
        gotoxy(10, 8);
        printf("Enter the age of employee: ");
        scanf("%d", &std.age);
        gotoxy(10, 9);
        printf("Enter salary of the employee: ");
        scanf("%d", &std.salary);
        fwrite(&std, sizeof(std), 1, fp);
        gotoxy(10, 12);
        printf("To add another record press 'Y', else press 'N': ");
        fflush(stdin);
        another = getchar();
    }
    fclose(fp);
    gotoxy(10, 18);
    printf("Press any key to continue.");
    getch();
    menu();
}

void view() {       //view function
    FILE *fp;
    int i = 1, j;
    struct emp std;
    system("cls");
    gotoxy(10, 3);
    printf("| VIEW RECORD |");
    gotoxy(10, 5);
    printf("Id   Name of employee        Age         Salary");
    gotoxy(10, 6);
    printf("---------------------------------------------------");
    fp = fopen("record.dat", "rb+");
    if (fp == NULL) {
        gotoxy(10, 8);
        printf("Error Opening File");
        exit(1);
    }
    j = 7;
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        gotoxy(10, j);
        printf("%-7d%-22s%-12d%-9d", i, std.name, std.age, std.salary);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to continue.");
    getch();
    menu();
}

void edit() {       //Edit function
    int id;
    FILE *fp;
    struct emp std;
    system("cls")b  ;
    gotoxy(10, 3);
    printf("| MODIFY RECORD |");
    gotoxy(10, 5);
    printf("Enter Id of employee to modify: ");
    fflush(stdin);
    scanf("%d", &id);
    fp = fopen("record.dat", "rb+");
    if (fp == NULL) {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id == id) {
            gotoxy(10, 7);
            printf("Enter new Id: ");
            scanf("%d", &std.id);
            fflush(stdin);
            gotoxy(10, 8);
            printf("Enter new name: ");
            gets(std.name);
            gotoxy(10, 9);
            printf("Enter new age: ");
            scanf("%d", &std.age);
            gotoxy(10, 10);
            printf("Enter new salary: ");
            scanf("%d", &std.salary);
            fseek(fp, -sizeof(std), SEEK_CUR);
            fwrite(&std, sizeof(std), 1, fp);
            break;
        }
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Edit made sucessfully");
    gotoxy(10,18);
    printf("Press any key to continue.");
    getch();
    menu();
}

void search() {         //Search function
    FILE *fp;
    struct emp std;
    int id;
    system("cls");
    gotoxy(10, 3);
    printf("| SEARCH RECORD |");
    gotoxy(10, 5);
    printf("Enter Id of employee: ");
    fflush(stdin);
    scanf("%d", &id);
    fp = fopen("record.dat", "rb+");
    if (fp == NULL) {
        gotoxy(10, 6);
        printf("Error opening File");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id == id) {
            gotoxy(10, 8);
            printf("Id: %d", std.id);
            gotoxy(10, 9);
            printf("Name: %s", std.name);
            gotoxy(10, 10);
            printf("Age: %d", std.age);
            gotoxy(10, 11);
            printf("Salary: %d", std.salary);
        }
        else{
            gotoxy(10,14);
            printf("Record not found");
        }
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue.");
    getch();
    menu();
}

void del() {            //Delete function
    int id;
    FILE *fp, *ft;
    struct emp std;
    system("cls");
    gotoxy(10, 3);
    printf("| DELETE RECORD |");
    gotoxy(10, 5);
    printf("Enter the Employee Id to delete: ");
    fflush(stdin);
    scanf("%d", &id);
    fp = fopen("record.dat", "rb+");
    if (fp == NULL) {
        gotoxy(10, 6);
        printf("Error opening File");
        exit(1);
    }
    ft = fopen("temp.dat", "wb+");
    if (ft == NULL) {
        gotoxy(10, 6);
        printf("Error opening File");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id != id) {
            fwrite(&std, sizeof(std), 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.dat");
    rename("temp.dat", "record.dat");
    gotoxy(10,18);
    printf("Record deleted sucessfully");
    menu();
}