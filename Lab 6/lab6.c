#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20

void insert (void);                                     //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
char name[LENGTH];
int size;


typedef struct ENTRY{                                   //structure template
        char name[LENGTH];
        int size;
        struct ENTRY *next;                                     //declaring pointer in structure
}ENTRY;

typedef struct LIST{                                    //declaring heads and tails
        ENTRY *head;
        ENTRY *tail;
}LIST;

LIST array[4];                                          //declaring array of linked lists


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
        ENTRY *p;                                                               //declaring pointer

        printf("Enter Name of Reservation:\n");
        scanf("%s", name);                                                      //scan for name

        if((p = (ENTRY *) malloc (sizeof (ENTRY))) == (ENTRY *)NULL){           //check for malloc error
                printf("malloc error\n");
                return;
        }


        if (duplicate(name)==0){
                printf("Duplicate Name Entered\n");             //Checks if duplicate function returns 0
                return;
        }
        
        strcpy(p->name, name);                                  //copying name into struct
        printf("Enter Size of Reservation:\n");
        scanf("%d", &size);
        p->size = size;                                         //copy party size into struct

        if(size == 1 || size == 2){                                     //if size is 1 or 2
                if(array[0].head == NULL){                                      //if list is empty
                        array[0].head = array[0].tail = p;                              //set pointer to head and tail
                        array[0].tail->next = NULL;                                     //set next to NULL
                }

                else{                                                           //if list is not empty 
                        array[0].tail->next = p;                                        //set next to pointer
                        array[0].tail=p;                                                //set tail to pointer
                }
        }

        if(size == 3 || size == 4){                                     //if size is 3 or 4
                if(array[1].head == NULL){                                      //if list is empty
                        array[1].head = array[1].tail = p;                              //set pointer to head and tail
                        array[1].tail->next = NULL;                                     //set next to NULL
                }

                else{                                                           //if list is not empty
                        array[1].tail->next = p;                                        //set next to pointer
                        array[1].tail=p;                                                //set tail to pointer
                }
        }

        if(size == 5 || size == 6){                                     //if size is 5 or 6
                if(array[2].head == NULL){                                      //if list is empty 
                        array[2].head = array[2].tail = p;                              //set pointer to head and tail
                        array[2].tail->next = NULL;                                     //set next to NULL
                }

                else{                                                           //if list is not empty
                        array[2].tail->next = p;                                        //set pointer to head and tail
                        array[2].tail=p;                                                //set next to NULL
                }
        }

        if(size > 6){                                                   //if size is greater than 6
                if(array[3].head == NULL){                                      //if list is empty
                        array[3].head = array[3].tail = p;                              //set pointer to head and tail
                        array[3].tail->next = NULL;                                     //set next to NULL
                }

                else{                                                           //if list is not empty
                        array[3].tail->next = p;                                        //set pointer to head and tail
                        array[3].tail=p;                                                //set next to NULL
                }
        }

        return;
}

void bye(void){                                                                 //delete function
        int tablesize;
        int i;
        int flag = 0;
        printf("Enter Size of Table:\n");
        scanf("%d", &tablesize);                                                //scaning for tablesize

        ENTRY *p, *q;                                                           //initialize p and q

        if((p = (ENTRY *)malloc(sizeof(ENTRY))) == NULL){                       //malloc
                printf("No memory to delete.\n");
                return;
        }


        for(i=0;i<4;i++){                                                       //for loop for array of 4
                p = q = array[i].head;                                          //set p and q to head of array
                while(p != NULL){                                               //while p is not NULL
                        if(tablesize >= p->size){                                                               //if tablesize is greater than size
                                printf("Removed %s party of %d from waiting list.\n", p->name, p->size);        //print removal
                                flag++;                                                                         //signal flag
                                break;
                        }

                        q = p;                                                  //set q equal to p
                        p = p->next;                                            //set p to next node
                }

                if(flag>0)                                                      //if a node is found, break
                        break;

        }

        if(flag==0){                                                            //if a node is not found, print
                printf("No Table Available for %d people.\n", tablesize);
                return;
        }

        if(p == array[i].head){                                                 //if p is equal to head
                array[i].head = p->next;                                        //set head equal to next
        }

        else{                                                                   //else set q next to p next
                q->next = p->next;

        }

        free(p);                                                                //free memory

        return;
}

void list(void){
        ENTRY *p;

        for(int i=0;i<4;i++){                                                   //for loop

                p = array[i].head;                                              //set pointer to head

                while(p != NULL){                                                                       //lists out reservation until the end of the list
                        printf("Reservation for %d under %s\n", p->size, p->name);
                        p = p->next;                                                                            //advance to the next node
                }
        }
        return;
}

int duplicate (char *name){
        ENTRY *p;

        for(int i=0;i<4;i++){                                                   //for loop for array of 4

                p = array[i].head;                                              //set pointer to head

                while(p != NULL){
                        if(strcmp(name, p->name) == 0){                         //checks if the name is the same as another stored name
                                return 0;
                        }
                        p = p->next;                                            //advance to the next node
                }
        }

        return 1;
}




void fit_in(void){
        ENTRY *p;                                                               //declare pointer

        int flag=0;
        int psize;


        printf("Enter a Party Size:\n");                                        //scan for party size
        scanf("%d", &psize);

        for(int i=0;i<4;i++){                                                   //for loop for array of 4

                p = array[i].head;                                              //set pointer to head

                while(p != NULL){                                               //checks if at the end of the list
                        if(p->size <= psize){
                                printf("%d, %s\n", p->size, p->name);           //printing out size and name
                                flag = 1;
                        }

                        p = p->next;                                            //advance to the next node
                }

        }
        if(flag==0){                                                            //check if flag activated
                printf("No Reservations Available.\n");                         //if not, print no reservations
                return;
        }
}
