/*
*	Jessica Valenzuela
*	I pledge my honor that I have abided by the Stevens Honors System
*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>


#define gettid() syscall(SYS_gettid)

int item1_counter = 0, item2_counter = 0, item3_counter = 0;
pthread_t t1, t2, t3;
pthread_mutex_t l1, l2, l3;


void *cs392_thread_run(void* arg){
    FILE *x = fopen((char*)arg, "r");
    if(x == NULL){
        printf("ERROR: Cannot open file %d\n", errno);
        exit(EXIT_FAILURE);
    }
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), x) != NULL){
        if(buffer[5] == '1'){
            pthread_mutex_lock(&l1);
            if(buffer[0] == '+'){
                item1_counter += 1;
            }
            if(buffer[0] == '-'){
                item1_counter -= 1;
            }

            pthread_mutex_unlock(&l1);
        }
        	if(buffer[5] == '2'){
            pthread_mutex_lock(&l2);
            if(buffer[0] == '+'){
                item2_counter += 1;
            }
            if(buffer[0] == '-'){
                item2_counter -= 1;
            }

            pthread_mutex_unlock(&l2);

        }
        	if(buffer[5] == '3'){
            pthread_mutex_lock(&l3);

            if(buffer[0] == '+'){
                item3_counter += 1;
            }
            if(buffer[0] == '-'){
                item3_counter -= 1;
            }

            pthread_mutex_unlock(&l3);
        }
    }
    fclose(x);

    return NULL;

}


int main(int argc, char** argv){
	//checks the number of arguments
    if(argc != 4){
        perror("Incorrect number of arguments: Expected 3.\nUsage: ./cs392_thread ./item_file1.txt ./item_file2.txt ./item_file3.txt\n");
        exit(EXIT_FAILURE);
    }

    //creates three child threads
    if( pthread_create(&t1, NULL, cs392_thread_run, argv[1]) != 0){
        perror("Thread 1 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_create(&t2, NULL, cs392_thread_run, argv[2]) != 0){
        perror("Thread 2 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_create(&t3, NULL, cs392_thread_run, argv[3]) != 0){
        perror("Thread 3 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }


    if( pthread_mutex_init(&l1, NULL) != 0){
        perror("Mutex 1 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_mutex_init(&l2, NULL) != 0){
        perror("Mutex 2 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }
    if( pthread_mutex_init(&l3, NULL) != 0){
        perror("Mutex 3 cannot be created, exiting...\n");
        exit(EXIT_FAILURE);
    }

    
    // wait for the three child threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&l1);
    pthread_mutex_destroy(&l2);
    pthread_mutex_destroy(&l3);


    //prints final values
    printf("The final value of item1_ counter, item2_counter and item3_counter are %d, %d, %d\n", item1_counter, item2_counter, item3_counter);

    pthread_exit(NULL);
    return 0;
}