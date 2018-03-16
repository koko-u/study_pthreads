#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void another_func(int n) {
    if (n == 1) {
        printf("See you...\n");
        pthread_exit(NULL);
    }
}

void* thread_func(void* arg) {
    for (int i = 0; i < 3; ++i) {
        printf("I'm thread func: %d\n", i);
        another_func(i);
        sleep(1);
    }
    return NULL;
}

int main(void) {
    pthread_t thread = 0;
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create new thread.\n");
        exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        printf("I'm main: %d\n", i);
        sleep(1);
    }

    return 0;
}