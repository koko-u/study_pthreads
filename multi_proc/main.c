#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int varA = 0;

void process_func(int n) {

    int varB = 4 * n;
    printf("process_func-%d-1: varA=%d, varB=%d\n", n, varA, varB);

    varA = 5 * n;
    printf("process_func-%d-2: varA=%d, varB=%d\n", n, varA, varB);

    sleep(2);
    printf("process_func-%d-3: varA=%d, varB=%d\n", n, varA, varB);

    varB = 6 * n;
    printf("process_func-%d-4: varA=%d, varB=%d\n", n, varA, varB);

    exit(EXIT_SUCCESS);
}

int main() {

    varA = 1;
    int varB = 2;
    printf("main-1: varA=%d, varB=%d\n", varA, varB);

    pid_t process1 = fork();
    if (process1 == 0) {
        process_func(1);
    }

    sleep(1);

    varB = 3;
    printf("main-2: varA=%d, varB=%d\n", varA, varB);

    pid_t process2 = fork();
    if (process2 == 0) {
        process_func(2);
    }

    waitpid(process1, NULL, 0);
    waitpid(process2, NULL, 0);

    printf("main-3: varA=%d, varB=%d\n", varA, varB);

    return 0;
}