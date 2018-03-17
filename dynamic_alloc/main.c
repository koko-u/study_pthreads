#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

//     main                       thread1                       thread2
//      |                           |                             |
//     malloc varA                  |                             |
//     varA <- "Good morning"       |                             |
//     print varA                   |                             |
//      |                           |                             |
//     pthread_create ---arg:1---> n <- 1                         |
//      |                          varA <- "Hello I'm No.1"       |
//      |                          print vaA                      |
//     <<sleep 1 second>>           |                             |
//      |                          <<slep 2 seconds>>             |
//      |                           |                             |
//     print varA                   |                             |
//     pthread_create --------------------------arg:2----------> n <- 2
//      |                           |                            varA <- "Hello I'm No.2"
//      |                           |                            print varA
//      |                           |                             |
//      |                           |                            <sleep 2 seconds>>
//      |                          print varA                     |
//      |                           |                             |
//     pthread_join <---------------/                             |
//      |                                                         |
//      |                                                        print varA
//      |                                                         |
//     pthread_join <---------------------------------------------/
//      |
//     print varA

#define STRING_SIZE 32

char* varA = NULL;

void* thread_func(void* arg) {
    int n = *((int*)arg);

    if (varA != NULL) {
        snprintf(varA, STRING_SIZE, "Hello, I'm No.%d", n);
        varA[STRING_SIZE-1] = '\0';
        printf("thread_func-%d: Sets varA as '%s'\n", n, varA);

        sleep(2);

        printf("thread_func-%d: After 2 secs. varA is '%s'\n", n, varA);
    }

    return NULL;
}

int main() {

    varA = malloc(sizeof(char) * STRING_SIZE);
    strncpy(varA, "Good morning.", STRING_SIZE);
    varA[STRING_SIZE-1] = '\0';

    printf("main-1: varA is '%s'\n", varA);

    pthread_t thread1 = 0;
    int arg1 = 1;
    pthread_create(&thread1, NULL, thread_func, &arg1);

    sleep(1);

    printf("main-2: varA is '%s'\n", varA);

    pthread_t thread2 = 0;
    int arg2 = 2;
    pthread_create(&thread2, NULL, thread_func, &arg2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("main-3: varA is '%s'\n", varA);

    free(varA);

    return 0;
}

