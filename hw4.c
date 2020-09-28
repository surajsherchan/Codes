#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void* runner(void* arg) {
    FILE *fp1; //Declare a file pointer. int n, sum = 0;
    int n, sum=0;
    //Open the file as readable.
    fp1 = fopen(arg, "r");
        //If open is unsucessful, print error msg and exit
    if(fp1 == NULL) {
        fprintf(stderr, "unable to open file.\n");
        exit(EXIT_FAILURE);
    }
    // If read is successful, get the number  add them.
    while (fscanf(fp1, "%d", &n) == 1) {
        sum += n;
        
    }
    //Declare a pointer of dynamic size.
    int* total = malloc(sizeof(*total));
    *total = sum;
    printf("The sum of file %s is %d.\n", arg,sum);
    //Close the file.
    if(fclose(fp1) != 0) {
        printf("Error closing file.\n"); exit(EXIT_FAILURE);
        exit(EXIT_FAILURE);
        
    }
    //Exit the thread with total as return value.
    pthread_exit(total);
    
}

int main(int ac, char* argv[]) {
    int argc = ac-1; //Declare 3 pthreads.
    pthread_t tid[argc];
    int i;
    if(ac < 2) {
        fprintf(stderr, "Please give a filename.\n");
        exit(EXIT_FAILURE);
        }
    
    for(i =0; i<argc; i++) {
        int ret;
        pthread_attr_t attr;
        pthread_attr_init(&attr); //get the default attributes.
        //Print error msg and exit if thread creation failed.
        if (( ret = pthread_create(&tid[i], &attr, runner,argv[i+1])) != 0){
            printf("Error creating threads.\n");
            exit(EXIT_FAILURE);
            }
        
    }
    //Join the results after threads finish executing.
    int* result;
    int total = 0;
    for(i=0; i<argc; i++) {
        int res = pthread_join(tid[i],(void**) &result);
        //If join failed print error msg and exit
        if (res != 0) {
            printf("Join unsucessful.\n");
            exit(EXIT_FAILURE);
            
        } else {
            printf("finishing child %d.\n", i);
            
        }
        //Add the results.
        total += *result; }
    //Free the memory.
    free(result);
    printf("sum of all threads %d\n",total);
    return 0;
    
}

