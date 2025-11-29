#include <stdio.h>
#include <math.h>
void calculateRepayment(float loan,float interestRate, int years,float installment);
int year=1;
int main() {
    float loan,interestRate,installment;
    int years;
    printf("Loan: ");
    scanf("%f",&loan);
    printf("Interest Rate: ");
    scanf("%f",&interestRate);
    printf("Years: ");
    scanf("%d",&years);
    printf("Installment: ");
    scanf("%f",&installment);

    calculateRepayment(loan,interestRate,years,installment);
    return 0;
}

void calculateRepayment(float loan,float interestRate, int years,float installment){
    if(year>years || loan <=0){
        return;
    }else{
        loan = loan * (1 + (interestRate / 100)) - installment;
        printf("Year %d: Remaining loan = %.2f\n",year,loan);
        year++;
        calculateRepayment(loan,interestRate,years,installment);
    }
}