#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20

void insert (char *name, int size);                                     //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
void readf(char *name);
void savef(char *name);
void freenode();
char name[LENGTH];
int size;


typedef struct ENTRY{                                   //structure template
        char name[LENGTH];
        int size;
        struct ENTRY *next;                                     //declaring pointer in structure
}ENTRY;

ENTRY* head = NULL;                                             //declaring head and tail
ENTRY* tail = NULL;

int main(int argc, char *argv[]){                                                       //start of main function with arguments
        int i;
        int input;

        if(argc == 1){                                                                  //if no file inputed
                printf("The name of the file is missing!\n");
                return 1;
        }

        readf(argv[1]);                                                                 //read in lines

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
                                printf("Enter Name of Reservation:\n");
                                scanf("%s", name);                                                      //scan for name

                                if (duplicate(name)==0){                                                //check for duplicates
                                        printf("Duplicate Name Entered\n");
                                        break;
                                }

                                printf("Enter Size of Reservation:\n");                                 //scan for size
                                scanf("%d", &size);


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
                        case 0:
                                savef(argv[1]);                                                         //save function
                                freenode();                                                             //freeing memory function
                                return 5;
                        default:
                                printf("Bad Input.\n");
                                break;
                }
        }
}

void insert(char *name, int size){
        ENTRY *p;
        FILE *fp;                                                               //declaring struct and file pointers

        if((p = (ENTRY *) malloc (sizeof (ENTRY))) == (ENTRY *)NULL){           //check for malloc error
                printf("malloc error\n");
                return;
        }


        strcpy(p->name, name);                                                  //copy name into structure
        p->size = size;                                                         //copy size into structure

        if(head == NULL){                                                       //if list is empty
                head = tail = p;                                                        //head and tail to pointer
                tail->next = NULL;                                                      //tail next to NULL
        }

        else{                                                                   //if list is not empty
                tail->next = p;                                                         //tail next to pointer
                tail = p;                                                               //tail to pointer
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

        if((p = (ENTRY *)malloc(sizeof(ENTRY))) == NULL){                       //if at the end of the list
                printf("No memory to delete.\n");
                return;
        }


        p = q = head;                                                           //p and q to head
        while(p != NULL){
                if(tablesize >= p->size){                                       //if tablesize is greater than size
                        printf("Removed %s party of %d from waiting list.\n", p->name, p->size);                //print removal
                        flag++;
                        if (p == head){                                         //if deleted node is head
                                head = p->next;                                         //set head to next node
                        }
                        else{                                                   //if deleted node is not head
                                q->next = p->next;                                      //set q next to p next
                        }

                        free(p);
                        return;
                }

                q = p;                                                          //set q to p
                p = p->next;                                                    //advance to next node
        }

        if(flag==0){                                                            //if node is not deleted
                printf("Nothing to remove.\n");                                 //print no removal
                return;
        }
}

void list(void){
        ENTRY *p;

        p = head;                                                               //set pointer to head

        while(p != NULL){                                                       //lists out reservation until the end of the list
                printf("Name: %s, Group Size: %d\n", p->name, p->size);
                p = p->next;                                                    //advance to the next node
        }
        return;
}




int duplicate (char *name){
        ENTRY *p;

        p = head;                                                               //set pointer to head

        while(p != NULL){
                if(strcmp(name, p->name) == 0){                                 //checks if the name is the same as another stored name
                        return 0;
                }
                p = p->next;                                                    //advance to the next node
        }

        return 1;
}




void fit_in(void){
        ENTRY *p;

        int flag=0;
        int psize;


        printf("Enter a Party Size:\n");
        scanf("%d", &psize);                                                    //scan for party size

        p = head;                                                               //set pointer to head

        while(p != NULL){                                                       //checks if at the end of the list
                if(p->size <= psize){
                        printf("%d, %s\n", p->size, p->name);                   //printing out size and name
                        flag = 1;
                }

                p = p->next;                                                    //advance to next node
        }
}

void readf(char *filename){

        char readchar[20];
        int readint;
        FILE *fp;                                                               //declare file pointer

        if((fp = fopen(filename, "r")) == NULL)                                 //if file is NULL
                printf("Cant open file %s\n", filename);                                //print unable to open file

        else{                                                                   //if file is not NULL
                fseek(fp, 37, SEEK_SET);                                                //skip 37 bytes
                while(fscanf(fp, "%s\t%d\n", readchar, &readint) == 2){                 //look through file

                        insert(readchar, readint);                                      //insert character and integer into list
                }

        fclose(fp);                                                             //close file
        }

}


void savef(char *filename){

        FILE *fp;                                                               //declare struct and file pointer
        ENTRY *p;

        fp = fopen(filename, "w");                                              //set pointer to file write
        fprintf(fp, "Name\tGroup Size\n---------------------\n");               //print header

        p = head;                                                               //set pointer to head
        while(p!=NULL){                                                         //look through list
                fprintf(fp, "%s\t%d\n", p->name, p->size);                              //print name and size into file
                p = p->next;                                                            //advance to next node
        }

        fclose(fp);                                                             //close file
}

void freenode(){
        ENTRY *p, *q;                                                           //declare two struct pointers

        if(head != NULL){                                                                               //if list is not empty
                if(head->next == NULL){                                                                         //if list has one node
                        printf("User %s with Group Size %d Deleted\n", head->name, head->size);
                        free(head);                                                                             //delete the head
                }

                else{                                                                                           //if list has more than one node
                        q = head;                                                                                       //keep traversing list
                        p = head->next;

                        while(q != NULL){
                                printf("User %s with Group Size %d Deleted\n", q->name, q->size);
                                free(q);                                                                                //keep deleting nodes while traversing
                                q = p;
                                if(p != NULL)
                                        p = p->next;
                        }                                                                                               //delete until end of list
                }
        }
}
