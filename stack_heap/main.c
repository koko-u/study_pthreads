#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//    main                     thread1                               thread2
//     |                         |                                     |
//    varA(global) <- 1          |                                     |
//    varB(local)  <- 2          |                                     |
//    print varA, varB           |                                     |
//     |             arg = 1     |                                     |
//    pthread_create  ------->   n <- 1                                |
//     |                        varB(local) <- 4 * 1                   |
//     |                        print varA, varB                       |
//     |                         |                                     |
//    <<sleep 1 second>>        varA(global) <- 5 * 1                  |
//     |                        print varA, varB                       |
//     |                         |                                     |
//    varB(local) <- 3           |                                     |
//    print varA, varB           |                       arg = 2       |
//    pthread_create  --------  <<sleep 2 seconds>>  --------------->  n <- 2
//                               |                                    varB(local) <- 4 * 2
//                               |                                    print varA, varB
//                               |                                     |
//                               |                                    varA(global) <- 5 * 2
//                               |                                    print varA, varB
//                               |                                     |
//                              print varA, varB                       |
//                               |                                     |
//                              varB(local) <- 6 * 1                  <<sleep 2 seconds>>
//                              print varA, varB                       |
//                               |                                     |
//    pthread_join <-------------/                                     |
//                                                                     |
//                                                                     |
//                                                                    print varA, varB
//                                                                     |
//                                                                    varB(local) <- 6 * 2
//                                                                    print varA, varB
//                                                                     |
//    pthread_join <---------------------------------------------------/
//     |
//    print varA, varB
//


int varA = 0;

void* thread_func(void* arg) {

    int n = *((int*)arg);

    int varB = 4 * n;
    printf("thread_func-%d-1: varA=%d, varB=%d\n", n, varA, varB);

    varA = 5 * n;
    printf("thread_func-%d-2: varA=%d, varB=%d\n", n, varA, varB);

    sleep(2);
    printf("thread_func-%d-3: varA=%d, varB=%d\n", n, varA, varB);

    varB = 6 * n;
    printf("thread_func-%d-4: varA=%d, varB=%d\n", n, varA, varB);

    return NULL;
}

int main() {

    varA = 1;
    int varB = 2;
    printf("main-1: varA=%d, varB=%d\n", varA, varB);

    pthread_t thread1 = 0;
    int arg1 = 1;
    pthread_create(&thread1, NULL, thread_func, &arg1);

    sleep(1);

    varB = 3;
    printf("main-2: varA=%d, varB=%d\n", varA, varB);

    pthread_t thread2 = 0;
    int arg2 = 2;
    pthread_create(&thread2, NULL, thread_func, &arg2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("main-3: varA=%d, varB=%d\n", varA, varB);

    return 0;
}