#include <stdio.h>
#include <string.h>


void insert (void);
void bye (void);
void list (void);
int counter = 0;
char name[10][20];
int size[10];

int main(){                                                     //start of main function
        int i;
        int input;
        for(i=0; i<10; i++){                                    //loop that resets values when program starts
                name[i][0] = '\0';
                size[i] = '\0';
        }




        while(1){                                               //Print out menu
                printf("Menu\n");
                printf("1 - Add Reservation\n");
                printf("2 - Remove Reservation\n");
                printf("3 - List\n");
                printf("0 - Quit\n");
                scanf("%d", &input);

                switch(input){                                  //switch with case functions
                        case 1:
                                insert();
                                break;
                        case 2:
                                bye();
                                break;
                        case 3:
                                list();
                                break;
                        case 0:
                                return 5;
                        default:
                                printf("Bad Input.\n");
                                break;
                }
        }
}

void insert(void){                                              //insert function
        if(counter >= 10){
                printf("Waiting List Full, Return Later");
                return;
        }
        printf("Enter Name of Reservation:\n");                 //print for inputs
        scanf("%s", name[counter]);
        printf("Enter Size of Reservation:\n");
        scanf("%d", &size[counter]);
        counter++;                                              //add to counter
}

void bye(void){                                                 //delete function
        if(counter==0){
                printf("No Reservations Logged.\n");
                return;
        }

        int i;
        int tablesize;
        int flag = 0;
        printf("Enter Size of Table:\n");
        scanf("%d", &tablesize);

        for(i=0;i<counter;i++){
                int j=0;                                        //loop that removes party if the size is less than or equal to the input
                if(tablesize - size[i] >= 0 && tablesize-size[i] < tablesize){
                        tablesize -= size[i];
                        printf("Removed %s party of %d from waiting list.\n", name[i], size[i]);
                        name[i][0] = '\0';
                        size[i] = '\0';

                        while(j<counter){
                                if(name[j][0] == '\0'){
                                        strcpy(name[j],name[j+1]);
                                        size[j] = size[j+1];
                                        name[j+1][0] = '\0';
                                        size[j+1] = '\0';
                                }
                        j++;
                        }
                        i--;
                        counter--;
                        flag++;
        }
        }

        if(flag==0){                                            //checks if anyone was removed
                printf("Can Not Fit Anyone at the Table.\n");
                return;
        }
}

void list(void){
int i;
        if(counter == 0){                                       //checks if any reservations exist
                printf("No Reservations Logged.\n");
                return;
        }
        for (i=0; i<10; i++){                                   //lists out reservation
                if(name[i][0] != '\0'){
                        printf("Reservation for %d under %s\n", size[i], name[i]);
                }
}
}
