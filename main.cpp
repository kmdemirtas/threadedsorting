#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <iomanip>
#include <chrono>
#include "sort.h"

struct package
{
    int *arr;
    int sortType;
};

sem_t out;

void *threadFunc(void *arg)
{
    auto start = std::chrono::high_resolution_clock::now();
    package *p = (package *)arg;
    switch (p->sortType)
    {
    case 0:
        sem_wait(&out);
        std::cout << "SELECTION SORT STARTED" << std::endl;
        sem_post(&out);
        selectionSort(p->arr);
        break;
    case 1:
        sem_wait(&out);
        std::cout << "INSERTION SORT STARTED" << std::endl;
        sem_post(&out);
        insertionSort(p->arr);
        break;
    case 2:
        sem_wait(&out);
        std::cout << "BUBBLE SORT STARTED" << std::endl;
        sem_post(&out);
        bubbleSort(p->arr);
        break;
    case 3:
        sem_wait(&out);
        std::cout << "MERGE SORT STARTED" << std::endl;
        sem_post(&out);
        mergeSort(p->arr, 0, ARR_SIZE - 1);
        break;
    case 4:
        sem_wait(&out);
        std::cout << "QUICK SORT STARTED" << std::endl;
        sem_post(&out);
        quickSort(p->arr, 0, ARR_SIZE - 1);
        break;
    default:
        break;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    if (isSorted(p->arr))
    {
        sem_wait(&out);
        std::cout << std::setw(22);
        switch (p->sortType)
        {
        case 0:
            std::cout << "SELECTION SORT SUCCESS";
            break;
        case 1:
            std::cout << "INSERTION SORT SUCCESS";
            break;
        case 2:
            std::cout << "BUBBLE SORT SUCCESS";
            break;
        case 3:
            std::cout << "MERGE SORT SUCCESS";
            break;
        case 4:
            std::cout << "QUICK SORT SUCCESS";
            break;
        default:
            break;
        }
        std::cout << " in: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms\n";
        sem_post(&out);
    }
    else
    {
        sem_wait(&out);
        std::cout << "ERROR" << std::endl;
        sem_post(&out);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    bool isRandom = true;
    if (argc > 1 && argv[1] == "sorted")
    {
        isRandom = false;
    }
    if (argc > 2)
    {
        ARR_SIZE = atoi(argv[2]);
    }
    sem_init(&out, 0, 1);
    pthread_t threads[TOTAL_ALG];
    std::srand(time(nullptr));
    int **arrHolder = (int **)malloc(sizeof(int *) * TOTAL_ALG);
    for (int i = 0; i < TOTAL_ALG; i++)
    {
        arrHolder[i] = (int *)malloc(sizeof(int) * ARR_SIZE);
    }
    for (int i = 0; i < ARR_SIZE; i++)
    {
        int val = isRandom ? rand() % ARR_SIZE : i;
        for (int j = 0; j < TOTAL_ALG; j++)
        {
            arrHolder[j][i] = val;
        }
    }
    package packages[TOTAL_ALG];
    for (int i = 0; i < TOTAL_ALG; i++)
    {
        packages[i].arr = arrHolder[i];
        packages[i].sortType = i;
        pthread_create(&(threads[i]), NULL, threadFunc, &packages[i]);
    }

    for (int i = 0; i < TOTAL_ALG; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < TOTAL_ALG; i++)
    {
        free(arrHolder[i]);
    }
    sem_destroy(&out);
    free(arrHolder);
}