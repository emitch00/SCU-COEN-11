#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20
#define ENTRY struct entry

void insert (void);                                     //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
char name[LENGTH];
int size;


struct entry{                                   //structure template
        char name[LENGTH];
        int size;
        ENTRY *next;                                    //declaring pointer in structure
};

ENTRY *head = NULL;
ENTRY *tail = NULL;                                     //declaring head and tail


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
        ENTRY *p;
        tail = head;                                                            //declaring pointer and setting tail to head

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

        strcpy(p->name, name);                                  //copy name into structure
        printf("Enter Size of Reservation:\n");
        scanf("%d", &size);
        p->size = size;                                         //inserting values into node
        p->next = NULL;

        if(head == NULL){                                       //checking if only one node exists
                head = p;
                return;
        }


        while(tail->next != NULL)                               //setting tail to end of list
                tail = tail->next;

        tail->next = p;                                         //making tail end node

        return;
}

void bye(void){                                                 //delete function
        int tablesize;
        int flag = 1;
        printf("Enter Size of Table:\n");
        scanf("%d", &tablesize);                                                                //scaning for tablesize

        ENTRY *p, *q;
        p = q = head;                                                           //initialize p and q

        if(p == (ENTRY *)NULL){                                                                 //if at the end of the list
                printf("No Table Available for %d people.\n", tablesize);
                return;
        }


        while (p != (ENTRY *)NULL) {
                if(p->size <= tablesize){
                        tablesize -= p->size;
                        flag = 0;
                        printf("Removed %s party of %d from waiting list.\n", p->name, p->size);
                        free(p);                                                                        //print removal

                        if(p == head){                                                                          //if head needs to be deleted
                                head = p->next;
                        }




                        else                                                                                    //unlink node
                                q->next = p->next;
                }

                q = p;                                                                                  //advance to next node
                p = p->next;


        }

        if(flag == 1){                                                                  //if at the end of the list
                printf("No Table Available for %d people.\n", tablesize);
                return;
        }


        return;
}

void list(void){
        ENTRY *p;

        if(head == (ENTRY *)NULL){                                                                      //if the head and the rest of the list are NULL
                printf("No Reservations Logged.\n");
                return;
        }

        p = head;                                                                                       //if not, start at the head

        while(p != (ENTRY *)NULL){                                                                              //lists out reservation until the end of the list
                printf("Reservation for %d under %s\n", p->size, p->name);
                p = p->next;                                                                            //advance to the next node
        }

        return;
}

int duplicate (char *name){
        ENTRY *p;
        p = head;

        while(p != (ENTRY *)NULL){
                if(strcmp(name, p->name) == 0){                         //checks if the name is the same as another stored name
                        return 0;
                }
                p = p->next;                                            //advance to the next node
        }
        return 1;
}

void fit_in(void){
        ENTRY *p;

        int flag=0;
        int psize;

        if(head == (ENTRY *)NULL){                                                                      //if the head is NULL
                printf("No Reservations Logged.\n");
                return;
        }

        printf("Enter a Party Size:\n");
        scanf("%d", &psize);


        p = head;

        while(p != (ENTRY *)NULL){                                                                                      //checks if at the end of the list
                        if(p->size <= psize){
                                printf("%d, %s\n", p->size, p->name);                                                   //printing out size and name
                                flag = 1;
                }
        p = p->next;
        }

        if(flag==0){                                                            //check if flag activated
                printf("No Reservations Available.\n");
                return;
        }
}
