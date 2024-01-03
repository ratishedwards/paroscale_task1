#include <sys/stat.h>

struct lru_node{
        char file_name[32];
        time_t  time_open;
        struct stat file_stat;
        struct lru_node  *next;
};

struct lru_node *LRU_HEAD = NULL;

struct lru_node *createNode(){
        struct lru_node *temp; // declare a node
        temp = (struct lru_node *)malloc(sizeof(struct lru_node));
        temp->next = NULL;// make next point to NULL
        return temp;//return the new node
}

struct lru_node * addNode(const char *file_name){
        struct lru_node *temp, *p;
        temp = createNode();

        //  Filling the stats info in the node
        if(stat(file_name, &temp->file_stat) == -1){
                // memory leak is possible more work is needed #TODO
                perror("stats call failed()\n");
                free(temp);
                exit (EXIT_FAILURE);
        }
        strcpy(temp->file_name, file_name);
        temp->time_open = time(NULL);

        if(LRU_HEAD == NULL){
                LRU_HEAD = temp;     //when linked list is empty
        }
        else{
                p  = LRU_HEAD;//assign head to p
                while(p->next != NULL){
                        p = p->next;
                }
                p->next = temp;
        }
        return LRU_HEAD;
}

// fuction to search node and return pointer to it
// return NULL if not found
struct lru_node *lru_search(const char file_name[]){
        struct lru_node *p;
        p = LRU_HEAD;
        while(p != NULL){
                if (strcmp(file_name, p->file_name) == 0 )
                        return p;
                p = p->next;
        }
        return NULL;
}


// fuction to search node and delete it
void lru_delete(const char file_name[]){
        struct lru_node *prev;
        struct lru_node *temp;
        temp = LRU_HEAD;
        prev = LRU_HEAD;
}

FILE * lru_open_file(const char file_name[]){

        FILE *file_ptr = fopen(file_name, "r");
        if (file_ptr == NULL){
                return NULL;
        }

        // update in record
        addNode(file_name);

        return file_ptr;
}

void lru_close_file(FILE * file_ptr, const char file_name[]){

        fclose(file_ptr);
        // update in record
        lru_delete(file_name);
}

void print_lru_stats(){

        struct lru_node *p;
        p = LRU_HEAD;
        while(p != NULL){
                printf("==============================\n");
                printf("File Name     :  %s\n", p->file_name);
                printf("File Size     :  %ld bytes\n", p->file_stat.st_size);
                printf("File inode    : %ld\n",  p->file_stat.st_ino);
                printf("File Open time: %ld\n",  p->time_open);
                printf("==============================\n");
                p = p->next;
        }
}