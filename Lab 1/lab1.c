#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
srand ((int) time (NULL));

//declare variables

int input = 0;
int divisor;
int dividend;
int quotient;
int count = 0;

//loop for 10 times

for(int i=0; i<10; i++){

        //setting random values

        divisor = rand () % 12+1;
        quotient = rand () % 13;
        dividend = quotient*divisor;

        //receiving user input

        printf("%d / %d = ", dividend, divisor);
        scanf("%d", &input);

        //checking if the user is correct

        if(input == quotient){
                printf("Correct!\n");
                count++;
        }
        else{
                printf("Wrong. The correct answer is %d\n", quotient);
        }
}

//final output of score

printf("Epic! You got %d/10!\n", count);
}
