//25k-3105
#include<stdio.h>
#include<string.h>
typedef struct EmployeeInformation{
        int EmployeeID;
        char Employeename[20];
        char Designation[20];
        float salary;
    } Information;
void displayEmployees(Information arr[],int n){
    printf("\n===========================================\n");
    printf("ID\tName\tDesignation\tSalary");
    printf("\n===========================================\n");
    int i;
    for(i=0;i<n;i++){
        printf("%d\t%s\t%s\t%f\n",arr[i].EmployeeID,arr[i].Employeename,arr[i].Designation,arr[i].salary);
    }
    printf("\n===========================================\n");
}
void findhighestsalary(Information arr[],int n){
    int maxindex = 0;
    int i;
    for(i=1;i<n;i++){
        if(arr[i].salary > arr[maxindex].salary){
        maxindex = i;
    }
}
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\n",arr[maxindex].EmployeeID);
    printf("Name: %s\n",arr[maxindex].Employeename);
    printf("Designation: %s\n",arr[maxindex].Designation);
    printf("Salary: %f\n",arr[maxindex].salary);
}
void searchEmployee(Information arr[], int n){
    int option;
    printf("\nSearch By:\n1. ID\n2. Name\nEnter Choice: ");
    scanf("%d",&option);
    if(option==1){
        int searchID;
        printf("Enter Employee ID: ");
        scanf("%d",&searchID);
        int i;
        for(i=0;i<n;i++){
        if(arr[i].EmployeeID == searchID){
            printf("\nEmployee Found!\n");
            printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %f",arr[i].EmployeeID,arr[i].Employeename,arr[i].Designation,arr[i].salary);
            return;
        }
        }
        printf("Employee with %d ID not Found.\n",searchID);
    }
    else if(option == 2){
        char searchname[20];
        printf("Enter Employee Name: ");
        scanf("%s",searchname);
        int i;
        for(i=0;i<n;i++){
        if(strcmp(arr[i].Employeename , searchname)==0){
            printf("\nEmployee Found!\n");
            printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %f",arr[i].EmployeeID,arr[i].Employeename,arr[i].Designation,arr[i].salary);
            return;
        }
        }
        printf("Employee with name %s not found.\n",searchname);
    }
    else{
        printf("Invalid option!\n");
    }
}
void updateSalarybonus(Information arr[], int n, float threshold){
    int i;
    for(i=0;i<n;i++){
        if(arr[i].salary < threshold){
            arr[i].salary += arr[i].salary * 0.10;
        }
    }
    printf("\nSalary updated for employees earning below %f\n",threshold);
}
int main(void){
    int n;
    printf("Enter number of Employees: ");
    scanf("%d",&n);
    Information arr[n];
    int i;
    for(i=0;i<n;i++){
     printf("\nEnter details for employee %d:\n",i+1);
     printf("ID: ");
     scanf("%d",&arr[i].EmployeeID);
     printf("Name: ");
     scanf("%s",arr[i].Employeename);
     printf("Designation: ");
     scanf("%s",arr[i].Designation);
     printf("Salary: ");
     scanf("%f",&arr[i].salary);
    }
    displayEmployees(arr,n);
    findhighestsalary(arr,n);
    searchEmployee(arr,n);
    updateSalarybonus(arr,n,50000);
    displayEmployees(arr,n);
    return 0;
}

