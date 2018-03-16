#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* thread_func(void* arg) {
    for (int i = 0; i < 3; ++i) {
        printf("I'm thread_func: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t thread = 0;
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create new thread\n");
        exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        printf("I'm main: %d\n", i);
        sleep(1);
    }

    return 0;
}