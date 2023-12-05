#include <stdio.h>
#include <pthread.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_variable = 0;

void *thread_function(void *arg)
{
    // 加锁
    pthread_mutex_lock(&my_mutex);

    // 访问共享资源
    for (int i = 0; i < 5; i++)
    {
        shared_variable++;
        printf("Thread %d: shared_variable = %d\n", *(int *)arg, shared_variable);
    }

    // 解锁
    pthread_mutex_unlock(&my_mutex);

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    int thread_id1 = 1, thread_id2 = 2;

    // 创建线程
    pthread_create(&thread1, NULL, thread_function, &thread_id1);
    pthread_create(&thread2, NULL, thread_function, &thread_id2);

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // 销毁互斥锁
    pthread_mutex_destroy(&my_mutex);

    return 0;
}