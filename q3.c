#include <stdio.h>
#include <string.h>

struct employee {
    char id[10];
    char name[50];
    char designation[50];
    int salary;
};
void displayEmployees(struct employee emp[],int n);
void findHighestSalary(struct employee emp[],int n);
void searchEmployee(struct employee emp[],int n);
void giveBonus(struct employee emp[],int n);

int main() {
    int n,chose,c;
    printf("Enter number of employees :> ");
    scanf("%d",&n);
    struct employee emp[n];

    
    for(int i=0;i<n;i++){
        while((c=getchar()), c != '\n' && c != EOF);
        printf("Employee %d :) \n",i+1);
        printf("\tId :> ");
        fgets(emp[i].id,sizeof(emp[i].id),stdin);
        emp[i].id[strlen(emp[i].id)-1]='\0';
        printf("\tName :> ");
        fgets(emp[i].name,sizeof(emp[i].name),stdin);
        emp[i].name[strlen(emp[i].name)-1]='\0';
        printf("\tDesignation :> ");
        fgets(emp[i].designation,sizeof(emp[i].designation),stdin);
        emp[i].designation[strlen(emp[i].designation)-1]='\0';
        printf("\tSalary :> ");
        scanf("%d",&emp[i].salary);
    }
    while (1)
    {
        printf("\nMain menu\n");
        printf("1. Display All Employees\n2. Get Employee Details With Highest Salary In staff\n3.Search Employee \n4. Give Bonus\n5. Exit\nChose :- ");
        scanf("%d",&chose);
        switch (chose)
        {
        case 1:
            displayEmployees(emp,n);
            break;
        case 2:
            findHighestSalary(emp,n);
            break;
        case 3:
            searchEmployee(emp,n);
            break;
        case 4:
            giveBonus(emp,n);
            break;
        case 5:
            return 0;
            break;
        default:
            printf("Invalid Input :(\n");

            break;
        }   
    }
    return 0;
}
void displayEmployees(struct employee emp[],int n){
    printf("\nEmployee ID\tEmployee Name\tDesignation\tSalary\n");
    for (int i = 0; i < n; i++)
    {
        if(strlen(emp[i].designation)<=6){
            printf("%s\t\t%s\t\t%s\t\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
        }else{
            printf("%s\t\t%s\t\t%s\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
        }
    }
    
}
void findHighestSalary(struct employee emp[],int n){
    int highest=0;
    printf("\nEmployee With Highest Salary In Staff");
    for(int i=0;i<n;i++){
        if(emp[highest].salary<emp[i].salary) highest=i;
    }
    printf("\nEmployee ID\tEmployee Name\tDesignation\tSalary\n");
    if(strlen(emp[highest].designation)<=6){
            printf("%s\t\t%s\t\t%s\t\t%d\n",emp[highest].id,emp[highest].name,emp[highest].designation,emp[highest].salary);
        }else{
            printf("%s\t\t%s\t\t%s\t%d\n",emp[highest].id,emp[highest].name,emp[highest].designation,emp[highest].salary);
        }
}
void searchEmployee(struct employee emp[],int n){
    int chose,c;
    printf("\nSearch by?\n1. ID\n2. Name\nChose :- ");
    scanf("%d",&chose);
    switch (chose)
    {
    case 1:
        char id[50];
        while((c=getchar()), c != '\n' && c != EOF);
        printf("ID :> ");
        fgets(id,sizeof(id),stdin);
        id[strlen(id)-1]='\0';

        for(int i=0;i<n;i++){
            if(strcmp(emp[i].id,id)==0) {
                printf("\nEmployee ID\tEmployee Name\tDesignation\tSalary\n");
                if(strlen(emp[i].designation)<=6){
                     printf("%s\t\t%s\t\t%s\t\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
                }else{
                    printf("%s\t\t%s\t\t%s\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
                }
            }
        }

        break;
    case 2:

        char name[50];
        while((c=getchar()), c != '\n' && c != EOF);
        printf("Name :> ");
        fgets(name,sizeof(name),stdin);
        name[strlen(name)-1]='\0';

        for(int i=0;i<n;i++){
            if(strcmp(emp[i].name,name)==0) {
                printf("\nEmployee ID\tEmployee Name\tDesignation\tSalary\n");
                if(strlen(emp[i].designation)<=6){
                    printf("%s\t\t%s\t\t%s\t\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
                }else{
                    printf("%s\t\t%s\t\t%s\t%d\n",emp[i].id,emp[i].name,emp[i].designation,emp[i].salary);
                }
            }
        }
        break;
    
    default:
        printf("\nInvalid Input :( \n");
        break;
    }
}
void giveBonus(struct employee emp[],int n){
    float bonus=50.0;
    float bon=bonus/100;

    for (int i = 0; i < n; i++)
    {
        if(emp[i].salary<50000){
            emp[i].salary *= ((1+bon));
        }
    }
    printf("Successfully gave bonus %.2f to all employees that have salary below 50,000",bonus);
}