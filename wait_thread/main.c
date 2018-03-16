#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

int parse_repeat_count(int argc, char **argv);

void* thread_func(void* arg) {

    int* n = (int*)arg;

    for (int i = 0; i < *n; ++i) {
        printf("I'm thread_func: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int n = parse_repeat_count(argc, argv);

    pthread_t thread = 0;
    if (pthread_create(&thread, NULL, thread_func, &n) != 0) {
        fprintf(stderr, "Error: Failed to create new thread\n");
        exit(1);
    }

    for (int i = 0; i < 5; ++i) {
        printf("I'm main: %d\n", i);
        sleep(1);
    }

    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error: Failed to wait for the thread termination.\n");
        exit(1);
    }

    printf("Bye.\n");

    return 0;
}

int parse_repeat_count(int argc, char* argv[]) {

    if (argc > 1) {
        char* end = NULL;
        long n = strtol(argv[1], &end, 10);
        if (end != NULL && *end == '\0' && n <= INT_MAX) {
            return (int)n;
        }
    }
    return 1;
}