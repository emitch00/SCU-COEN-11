#include <stdio.h>
#include <string.h>
#define SIZE 10
#define LENGTH 20

void insert (void);                                     //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
int counter = 0;
char name[SIZE][LENGTH];
int size[SIZE];


typedef union extra{                                    //union
        char birthday_name[20];
        int years;
        float average_age;
}EXTRA;

typedef struct entry{                                   //structure template
        char name[LENGTH];
        int size;
        int occasion;
        EXTRA extra_info;
}ENTRY;

ENTRY line[SIZE];
ENTRY *p = line;                                        //declaring pointer in structure


int main(){                                                     //start of main function
        int i;
        int input;


        while(1){                                               //Print out menu
                printf("Menu\n");
                printf("1 - Add Reservation\n");
                printf("2 - Remove Reservation\n");
                printf("3 - List\n");
                printf("4 - Search\n");
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
                        case 4:
                                fit_in();
                                break;
                        case 0:
                                return 5;
                        default:
                                printf("Bad Input.\n");
                                break;
                }
        }
}

void insert(void){
int occasion;
char temp[LENGTH];
        if(counter >= SIZE){
                printf("Waiting List Full, Return Later");
                return;
        }
        printf("Enter Name of Reservation:\n");
        scanf("%s", temp);
        if (duplicate(temp)==0){
                printf("Duplicate Name Entered\n");             //Checks if duplicate function returns 0
                return;
        }
        strcpy(line[counter].name, temp);

        printf("Enter Size of Reservation:\n");
        scanf("%d", &line[counter].size);                       //inputs size

        printf("Occasion?\n");
        scanf("%d", &line[counter].occasion);

        occasion = line[counter].occasion;

        switch(occasion){                                       //switch for occasion
                case 1:
                        printf("Enter Name of Birthday Person:\n");             //birthday option
                        scanf("%s", line[counter].extra_info.birthday_name);
                        break;
                case 2:
                        printf("Enter Number of Years:\n");                     //anniversary option
                        scanf("%d", &line[counter].extra_info.years);
                        break;
                default:                                                        //other option
                        printf("Enter the Average Age of Party:\n");
                        scanf("%f", &line[counter].extra_info.average_age);
                        break;
        }

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
        scanf("%d", &tablesize);                                                                //scaning for tablesize


        for(i=0;i<counter;i++){
                int j=0;                                                                        //loop that removes party if the size is less than or equal to the input
                if(tablesize - line[i].size >= 0 && tablesize-line[i].size < tablesize){
                        tablesize -= line[i].size;
                        printf("Removed %s party of %d from waiting list.\n", line[i].name, line[i].size);
                        line[i].name[0] = '\0';
                        line[i].size = '\0';
                        line[i].extra_info.birthday_name[0] = '\0';
                        line[i].extra_info.years = '\0';
                        line[i].extra_info.average_age = '\0';

                        while(j<counter-1){                                             //shifting
                                if(line[j].name[0] == '\0'){
                                        strcpy(line[j].name,line[j+1].name);                                                    //shifting data up one slot
                                        line[j].size = line[j+1].size;
                                        strcpy(line[j].extra_info.birthday_name, line[j+1].extra_info.birthday_name);
                                        line[j].extra_info.years = line[j+1].extra_info.years;
                                        line[j].extra_info.average_age = line[j+1].extra_info.average_age;
                                        line[j].occasion = line[j+1].occasion;

                                        line[j+1].name[0] = '\0';                                                               //deleting repeated data from the previous slot
                                        line[j+1].size = '\0';
                                        line[j+1].extra_info.birthday_name[0] = '\0';
                                        line[j+1].extra_info.years = '\0';
                                        line[j+1].extra_info.average_age = '\0';
                                        line[j+1].occasion = '\0';
                                }
                        j++;
                        }
                        i--;
                        counter--;
                        flag++;
        }
        }


        if(flag==0){                                                            //checks if anyone was removed
                printf("Can Not Fit Anyone at the Table.\n");
                return;
        }
}

void list(void){
int i;
ENTRY *p = line;
        if(counter == 0){                                                       //checks if any reservations exist
                printf("No Reservations Logged.\n");
                return;
        }
        for(i=0; i<counter; i++, p++)
                if(p->occasion == 1)                                            //lists out reservation
                        printf("Reservation for %d under %s. The occasion is %d and the birthday name is: %s.\n", p->size, p->name, p->occasion, p->extra_info.birthday_name);
                else if(p->occasion == 2)
                        printf("Reservation for %d under %s. The occasion is %d and this is the %dth anniversary.\n", p->size, p->name, p->occasion, p->extra_info.years);
                else
                        printf("Reservation for %d under %s. The occasion is %d and the average age of the party is: %.2f.\n", p->size, p->name, p->occasion, p->extra_info.average_age);               //prints list depending on occasion
}

int duplicate (char *temp){;
int i;
ENTRY *p = line;
        for(i=0;i<counter;i++,p++){
                if(strcmp(temp, p->name) == 0){                         //checks if the name is the same as another stored name
                        return 0;
                }
        }
        return 1;
}




void fit_in(void){
if(counter==0){                                                         //check if any reservations are logged
        printf("No Reservations Logged.\n");
        return;
}
ENTRY *p = line;
int flag=0;
int psize;
int i;
int j;
printf("Enter a Party Size:\n");
scanf("%d", &psize);
for(i=0;i<counter;i++, p++){                                            //checks for a size that is less than the user input
        if(p->size <= psize){
                printf("%d, %s\n", p->size, p->name);                   //printing out size and name
                flag = 1;
}
}
if(flag==0){                                                            //check if flag activated
        printf("No Reservations Available.\n");
        return;
}
}
