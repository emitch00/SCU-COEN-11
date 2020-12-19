#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20

void insert (char *name, int size);                             //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
void readf(char *name);
void savef(char *name);
char name[LENGTH];
int size;


typedef struct ENTRY{                                           //structure template
        char name[LENGTH];
        int size;
        struct ENTRY *next;                                     //declaring pointer in structure
}ENTRY;

ENTRY* head = NULL;                                             //declaring head and tail
ENTRY* tail = NULL;

void freenode(ENTRY *p);                                        //prototype for free node function
void revlist(ENTRY *p);                                         //prototype for reverse list
void revname(ENTRY *p);                                         //prototype for reverse name

int main(int argc, char *argv[]){                               //start of main function with arguments
        int i;
        int input;

        if(argc == 1){                                                  //if file is not given
                printf("The name of the file is missing!\n");           //print to user
                return 1;
        }

        readf(argv[1]);                                                 //read in lines

        while(1){                                                       //Print out menu
                printf("Menu\n");
                printf("1 - Add Reservation\n");
                printf("2 - Remove Reservation\n");
                printf("3 - List\n");
                printf("4 - Search\n");
                printf("5 - Reverse List\n");
                printf("0 - Quit\n");
                scanf("%d", &input);

                switch(input){                                          //switch with case functions
                        case 1:
                                printf("Enter Name of Reservation:\n");
                                scanf("%s", name);                                      //scan for name

                                if (duplicate(name)==0){                                //check for duplicates
                                        printf("Duplicate Name Entered\n");
                                        break;
                                }

                                printf("Enter Size of Reservation:\n");
                                scanf("%d", &size);                                     //scan for size


                                insert(name, size);
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
                        case 5:
                                revlist(head);
                                break;
                        case 6:
                                revname(head);
                                break;
                        case 0:
                                savef(argv[1]);
                                freenode(head);
                                return 5;
                        default:
                                printf("Bad Input.\n");
                                break;
                }
        }
}

void insert(char *name, int size){
        ENTRY *p;                                                               //declaring struct and file pointers
        FILE *fp;

        if((p = (ENTRY *) malloc (sizeof (ENTRY))) == (ENTRY *)NULL){           //check for malloc error
                printf("malloc error\n");
                return;
        }


        strcpy(p->name, name);                                  //copy name into structure
        p->size = size;                                         //copy size into structure

        if(head == NULL){                                       //if list is empty
                head = tail = p;                                        //set head and tail to pointer
                tail->next = NULL;                                      //set end of list to NULL
        }

        else{                                                   //if list is not empty
                tail->next = p;                                         //set p to the end of list
                tail = p;
        }

        return;
}

void bye(void){                                                 //delete function
        int tablesize;
        int i;
        int flag = 0;
        printf("Enter Size of Table:\n");
        scanf("%d", &tablesize);                                //scaning for tablesize

        ENTRY *p, *q;                                           //initialize p and q

        if((p = (ENTRY *)malloc(sizeof(ENTRY))) == NULL){               //malloc function
                printf("No memory to delete.\n");
                return;
        }


        p = q = head;                                                   //set p and q to beginning of list
        while(p != NULL){
                if(tablesize >= p->size){                                                               //if tablesize is greater than size
                        printf("Removed %s party of %d from waiting list.\n", p->name, p->size);        //indicate to user removal
                        flag++;
                        if (p == head){                                 //if deleted node is head
                                head = p->next;                                 //set head to next node
                        }
                        else{                                           //if deleted node is not head
                                q->next = p->next;                              //traverse list
                        }

                        free(p);                                        //free memory
                        return;
                }

                q = p;                                                  //set q to p
                p = p->next;                                            //traverse to next node
        }

        if(flag==0){                                                                    //if no node is deleted
                printf("Nothing to remove.\n");                                                 //indicate to user
                return;
        }
}

void list(void){
        ENTRY *p;                                                       //declare struct pointer

        p = head;                                                       //set pointer to beginning of list

        while(p != NULL){                                                                       //lists out reservation until the end of the list
                printf("Name: %s, Group Size: %d\n", p->name, p->size);
                p = p->next;                                                                            //advance to the next node
        }
        return;
}




int duplicate (char *name){
        ENTRY *p;                                                       //declare struct pointer

        p = head;                                                       //set pointer to beginning of list

        while(p != NULL){
                if(strcmp(name, p->name) == 0){                         //checks if the name is the same as another stored name
                        return 0;
                }
                p = p->next;                                            //advance to the next node
        }

        return 1;
}

void fit_in(void){
        ENTRY *p;                                                       //struct pointer

        int psize;


        printf("Enter a Party Size:\n");
        scanf("%d", &psize);                                            //scan party size

        p = head;                                                       //set pointer to beginning of list

        while(p != NULL){                                                       //checks if at the end of the list
                if(p->size <= psize){
                        printf("%d, %s\n", p->size, p->name);                   //printing out size and name                                            
                }

                p = p->next;                                            //advance to next node
        }

}


void readf(char *filename){

        char readchar[20];
        int readint;
        FILE *fp;                                                               //declare file pointer

        if((fp = fopen(filename, "r")) == NULL)                                 //if file pointer comes back NULL
                printf("Cant open file %s\n", filename);                                //tell user

        else{                                                                   //if file is not empty
                fseek(fp, 37, SEEK_SET);                                                //skip 37 bytes
                while(fscanf(fp, "%s\t%d\n", readchar, &readint) == 2){                 //look for character and integer

                        insert(readchar, readint);                                      //insert character and integer into list
                }

        fclose(fp);                                                             //close file
        }

}

void savef(char *filename){

        FILE *fp;                                                               //declare struct and file pointer
        ENTRY *p;

        fp = fopen(filename, "w");                                              //set file pointer to write
        fprintf(fp, "Name\tGroup Size\n---------------------\n");               //print header

        p = head;                                                               //set pointer to beginning of list
        while(p!=NULL){                                                         //traverse list
                fprintf(fp, "%s\t%d\n", p->name, p->size);                      //print name and size into file
                p = p->next;                                                    //advance to next node  
        }

        fclose(fp);                                                             //close file
}

void freenode(ENTRY *p){                                                                        //free node function

        if(p == NULL)                                                                           //if node is empty, return
                return;
        printf("Name %s and Number of Customers %d Deleted.\n", p->name, p->size);
        free(p);                                                                                //free memory
        freenode(p->next);                                                                      //recursive for next node
}

void revlist(ENTRY *p){
        if(p == NULL)                                                                           //if list is empty, return
                return;

        revlist(p->next);                                                                       //recursive for next node
        printf("Name: %s, Number of Customers: %d\n", p->name, p->size);                        //print name and number of customers
}

void revname(ENTRY *p){
        int i = 0;
        if(p == NULL)                                                           //if node is empty, return
                return;

        for(i = (strlen(p->name)-1); i>=0; i--){                                //start at end of name and move backwards
                printf("%c", p->name[i]);                                       //print characters backwards
                printf("\n");                                                   //new line between names
        }

        revname(p->next);                                                       //recursive for next node
}
