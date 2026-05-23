#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&mutex);
    readcount++;

    if(readcount == 1)
        sem_wait(&wrt);

    sem_post(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);

    sem_wait(&mutex);
    readcount--;

    if(readcount == 0)
        sem_post(&wrt);

    sem_post(&mutex);

    printf("Reader %d finished reading\n", id);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wrt);

    printf("Writer %d is writing\n", id);
    sleep(1);
    printf("Writer %d finished writing\n", id);

    sem_post(&wrt);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int rid[5], wid[2];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for(int i = 0; i < 5; i++) {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }

    for(int i = 0; i < 2; i++) {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }

    for(int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    for(int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

//gcc reader-writer_problem.c -lpthread

/*
Aim

To synchronize access to shared data so that multiple readers can read simultaneously while writers get exclusive access.

Theory

The Reader–Writer problem is a classic process synchronization problem.

There are two types of processes:

Reader
Reads shared data
Does not modify it
Multiple readers can access simultaneously
Writer
Modifies shared data
Requires exclusive access
No reader or writer can access while writing
Working Principle
Many readers → allowed together
One writer → exclusive access
Writer and readers together → not allowed

Algorithm (Reader–Writer)
Reader Process
Start
Request read access
If no writer active → allow reading
Increase reader count
Read shared data
Decrease reader count
If last reader leaves → release resource
Stop
Writer Process
Start
Request write access
Wait until no readers/writers active
Lock resource
Write data
Release resource
Stop
*/