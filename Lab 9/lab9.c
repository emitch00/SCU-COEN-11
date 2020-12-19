#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define LENGTH 20

void insert (char *name, int size);                                     //global variables
void bye (void);
void list (void);
void fit_in(void);
int duplicate (char *);
void readf(char *name);
void savef(char *name);
void *autosave();
void readbin(char *name);
char name[LENGTH];
int size;


typedef struct ENTRY{                                   //structure template
        char name[LENGTH];
        int size;
        struct ENTRY *next;                                     //declaring pointer in structure
}ENTRY;

ENTRY* head = NULL;
ENTRY* tail = NULL;

void freenode(ENTRY *p);
void revlist(ENTRY *p);
void revname(ENTRY *p);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]){                                                       //start of main function
        int i;
        int input;
        pthread_t thread;
        pthread_mutex_init(&mutex, NULL);
        pthread_create(&thread, NULL, autosave, (void *)argv[2]);

        if(argc != 3){
                printf("Some files are missing!\n");
                return 1;
        }

        readf(argv[1]);
        
        while(1){                                               //Print out menu
                printf("Menu\n");
                printf("1 - Add Reservation\n");
                printf("2 - Remove Reservation\n");
                printf("3 - List\n");
                printf("4 - Search\n");
                printf("5 - Reverse List\n");
                printf("0 - Quit\n");
                scanf("%d", &input);

                switch(input){                                  //switch with case functions
                        case 1:
                                printf("Enter Name of Reservation:\n");
                                scanf("%s", name);                                                      //scan for name

                                if (duplicate(name)==0){
                                        printf("Duplicate Name Entered\n");
                                        break;
                                }

                                printf("Enter Size of Reservation:\n");
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
                        case 5:
                                revlist(head);
                                break;
                        case 6:
                                revname(head);
                                break;
                        case 7:
                                readbin(argv[2]);
                                break;
                        case 0:
                                pthread_mutex_lock(&mutex);
                                pthread_cancel(thread);
                                pthread_mutex_unlock(&mutex);
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
        pthread_mutex_lock(&mutex);
        ENTRY *p;
        FILE *fp;                                                               //declaring pointer and setting tail to head

        if((p = (ENTRY *) malloc (sizeof (ENTRY))) == (ENTRY *)NULL){           //check for malloc error
                printf("malloc error\n");
                return;
        }


        strcpy(p->name, name);                                  //copy name into structure
        p->size = size;

        if(head == NULL){
                head = tail = p;
                tail->next = NULL;
        }

        else{
                tail->next = p;
                tail = p;
        }

        pthread_mutex_unlock(&mutex);

        return;
}

void bye(void){                                                 //delete function
        int tablesize;
        int i;
        int flag = 0;
        printf("Enter Size of Table:\n");
        scanf("%d", &tablesize);                                                                //scaning for tablesize

        ENTRY *p, *q;                                                           //initialize p and q

        p = q = head;
        while(p != NULL){
                if(tablesize >= p->size){
                        printf("Removed %s party of %d from waiting list.\n", p->name, p->size);
                        flag++;
                        if (p == head){
                                head = p->next;
                        }
                        else{
                                q->next = p->next;
                        }

                        free(p);
                        return;
                }

                q = p;
                p = p->next;
        }

        if(flag==0){                                                                    //if at the end of the list
                printf("Nothing to remove.\n");
                return;
        }
}

void list(void){
        ENTRY *p;

        p = head;                                                                                       //if not, start at the head

        while(p != NULL){                                                                               //lists out reservation until the end of the list
                printf("Name: %s, Group Size: %d\n", p->name, p->size);
                fflush(stdout);
                p = p->next;                                                                            //advance to the next node
        }
        return;
}




int duplicate (char *name){
        ENTRY *p;

        p = head;

        while(p != NULL){
                if(strcmp(name, p->name) == 0){                         //checks if the name is the same as another stored name
                        return 0;
                }
                p = p->next;                                            //adcance to the next node
        }

        return 1;
}




void fit_in(void){
        ENTRY *p;

        int psize;

        printf("Enter a Party Size:\n");
        scanf("%d", &psize);

        p = head;

        while(p != NULL){                                                                                       //checks if at the end of the list
                if(p->size <= psize){
                        printf("%d, %s\n", p->size, p->name);                                                   //printing out size and name                                            
                }

                p = p->next;
        }

}

void readf(char *filename){

        char readchar[20];
        int readint;
        FILE *fp;

        if((fp = fopen(filename, "r")) == NULL)
                printf("Cant open file %s\n", filename);

        else{
                fseek(fp, 37, SEEK_SET)                                                 //skip 47 bytes;
                while(fscanf(fp, "%s\t%d\n", readchar, &readint) == 2){

                        insert(readchar, readint);                                      //insert character and int into structure
                }

        fclose(fp);
        }

}


void savef(char *filename){

        FILE *fp;
        ENTRY *p;

        fp = fopen(filename, "w");
        fprintf(fp, "Name\tGroup Size\n---------------------\n");                       //make heading

        p = head;
        while(p!=NULL){
                fprintf(fp, "%s\t%d\n", p->name, p->size);
                p = p->next;                                                            //print name and size into file
        }

        fclose(fp);
}

void freenode(ENTRY *p){

        if(p == NULL)
                return;
        printf("Name %s and Number of Customers %d Deleted.\n", p->name, p->size);
        free(p);
        freenode(p->next);                                                              //free nodes and traverse
}

void revlist(ENTRY *p){
        if(p == NULL)
                return;

        revlist(p->next);                                                               //reverse list and traverse
        printf("Name: %s, Number of Customers: %d\n", p->name, p->size);
}

void revname(ENTRY *p){
        int i = 0;
        if(p == NULL)
                return;

        for(i = (strlen(p->name)-1); i>=0; i--){
                printf("%c", p->name[i]);                                               //start at end of name and print backwards
                printf("\n");
        }

        revname(p->next);
}

void *autosave(void *arg){
        FILE *fp;
        char *filename = (char *)arg;
        ENTRY *p;

        while(1){
                sleep(15);
                printf("Saving to File.\n");
                pthread_mutex_lock(&mutex);                                             //lock
                fp = fopen(filename, "wb");
                p = head;

                while(p != NULL){
                        fwrite(p, sizeof(ENTRY), 1, fp);                                //write entire list into binary file
                        p = p->next;
                }

                fclose(fp);
                printf("Finished Saving.\n");
                pthread_mutex_unlock(&mutex);                                           //unlock
        }
}

void readbin(char filename[]){
        FILE *fp;
        ENTRY p;

        pthread_mutex_lock(&mutex);
        fp = fopen(filename, "rb");

        if(fp == NULL){
                pthread_mutex_unlock(&mutex);                                           //if file empty unlock and quit
                return;
        }

        while((fread(&p, sizeof(ENTRY), 1, fp)) > 0){
                printf("Name: %s and Number of Customers: %d\n", p.name, p.size);       //print contents in binary file
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        return;
}
