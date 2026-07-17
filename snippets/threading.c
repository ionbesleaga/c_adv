#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_work(void *arg)
{
    int a = *(int *)arg;
    free(arg);
    printf("THREAD WORK ARG: %d\n", a);

    return (void *)(intptr_t)a;
}

void *thread_work_static(void *arg)
{
    int a = *(int *)arg;
    free(arg);

    static int foo = 10;
    int x = foo;
    printf("THREAD WORK ARG: %d; FOO: %d; X: %d\n", a, foo, x);

    foo++;

    return (void *)(intptr_t)a;
}

void *thread_work_static_local_thrd(void *arg)
{
    int a = *(int *)arg;
    free(arg);

    static thread_local int foo = 10;
    int x = foo;
    printf("THREAD WORK ARG: %d; FOO: %d; X: %d\n", a, foo, x);

    foo++;

    return (void *)(intptr_t)a;
}

pthread_mutex_t mtx;
void *thread_work_static_mutex(void *arg)
{
    (void)arg;
    static int num = 0;

    pthread_mutex_lock(&mtx);
    printf("THREAD WORKING : %d\n", num);
    num++;
    pthread_mutex_unlock(&mtx);

    return (void *)(intptr_t)num;
}

void run_single_thrd()
{
    pthread_t thrd;
    int arg = 123;

    pthread_create(&thrd, NULL, thread_work, &arg);

    void *thrd_ret = NULL;
    pthread_join(thrd, &thrd_ret);

    printf("MAIN RETURN: %d", (int)(intptr_t)thrd_ret);
}

void run_multiple_thrds()
{
    int thrd_ctn = 5;
    pthread_t thrds[thrd_ctn];

    int i;
    for (i = 0; i < thrd_ctn; i++)
    {
        int *arg = malloc(sizeof *arg);
        *arg = i;
        pthread_create(thrds + i, NULL, thread_work, arg);
    }

    for (int i = 0; i < thrd_ctn; i++)
    {
        void *thrd_ret = NULL;
        pthread_join(thrds[i], &thrd_ret);

        printf("MAIN RETURN: %d\n", (int)(intptr_t)thrd_ret);
    }
}

void run_multiple_thrds_with_static()
{
    int thrd_ctn = 5;
    pthread_t thrds[thrd_ctn];

    int i;
    for (i = 0; i < thrd_ctn; i++)
    {
        int *arg = malloc(sizeof *arg);
        *arg = i;
        pthread_create(thrds + i, NULL, thread_work_static_local_thrd, arg);
    }

    for (int i = 0; i < thrd_ctn; i++)
    {
        void *thrd_ret = NULL;
        pthread_join(thrds[i], &thrd_ret);

        printf("MAIN RETURN: %d\n", (int)(intptr_t)thrd_ret);
    }
}

void run_detached_thrds()
{
    int thrd_ctn = 5;
    pthread_t thrd;
    for (int i = 0; i < thrd_ctn; i++)
    {
        int *arg = malloc(sizeof *arg);
        *arg = i;

        // create THEN detach
        // pthread_create(&thrd, NULL, thread_work, arg);
        // pthread_detach(thrd);

        // create detached
        pthread_attr_t tattr;
        pthread_attr_init(&tattr);
        pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
        pthread_create(&thrd, &tattr, thread_work, arg);
        pthread_attr_destroy(&tattr);
    }

    nanosleep(&(struct timespec){.tv_sec = 1}, NULL);
}

void run_multiple_thrds_mutex()
{
    int thrd_ctn = 5;
    pthread_t thrds[thrd_ctn];

    pthread_mutex_init(&mtx, NULL);

    int i;
    for (i = 0; i < thrd_ctn; i++)
    {
        int *arg = malloc(sizeof *arg);
        *arg = i;
        pthread_create(thrds + i, NULL, thread_work_static_mutex, arg);
    }

    for (int i = 0; i < thrd_ctn; i++)
    {
        void *thrd_ret = NULL;
        pthread_join(thrds[i], &thrd_ret);
    }

    pthread_mutex_destroy(&mtx);
}
