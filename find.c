#include "structs.h"

#define NTHREADS 2

int CmpFunc(const void *p1, const void *p2) {
    Person a = *(const Person*)p1;
    Person b = *(const Person*)p2;
    return strcmp(a.last_name, b.last_name);
}

void* FindYoungest(void *arg){
    Title* profession = (Title*) arg;
    PersonArr* youngest = NULL;
    PersonArrInit(&youngest);
    size_t n = profession->persons->curr_idx;
    int count;
    count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (profession->persons->arr[i].age <= profession->min_age) {
            PushBackPerson(youngest, &(profession->persons->arr[i]));
            ++count;
        }
    }
    qsort((void *) youngest->arr, count, sizeof(Person), CmpFunc);
    return (void*)(youngest);
}

void FindYoungestByProfession(TitleArr *v) {
    pthread_t tid[NTHREADS];
    int err;
    size_t N = v->curr_idx;
    PersonArr** res = malloc(N*sizeof(PersonArr*));
    int k = N / NTHREADS;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < NTHREADS && i * NTHREADS + j < N; ++j) {
            err = pthread_create(&(tid[j]), NULL, &FindYoungest, (void *) (&(v->arr[i * NTHREADS + j])));
        }
        for (int j = 0; j < NTHREADS && i * NTHREADS + j < N; ++j) {
            void *ret_from_thread;
            pthread_join(tid[j], &ret_from_thread);
            res[i * NTHREADS + j] = (PersonArr *) ret_from_thread;
        }
    }
    for (int i = 0; i < N; ++i) {
        printPersonArr(res[i]);
    }
    for (int i = 0; i < N; ++i) {
        free(res[i]->arr);
    }
    free(res);
}

void* FindOldest(void *arg) {
    Title* profession = (Title*) arg;
    PersonArr* youngest = NULL;
    PersonArrInit(&youngest);
    size_t n = profession->persons->curr_idx;
    int count;
    count = 0;
    for (size_t i = 0; i < n; ++i) {
        if (profession->persons->arr[i].age >= profession->max_age) {
            PushBackPerson(youngest, &(profession->persons->arr[i]));
            ++count;
        }
    }
    qsort((void *) youngest->arr, count, sizeof(Person), CmpFunc);
    return (void*)(youngest);
}

void FindOldestByProfession(TitleArr *v) {
    pthread_t tid[NTHREADS];
    int err;
    size_t N = v->curr_idx;
    PersonArr** res = malloc(N*sizeof(PersonArr*));
    int k = N / NTHREADS;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < NTHREADS && i * NTHREADS + j < N; ++j) {
            err = pthread_create(&(tid[j]), NULL, &FindOldest, (void *) (&(v->arr[i * NTHREADS + j])));
        }
        for (int j = 0; j < NTHREADS && i * NTHREADS + j < N; ++j) {
            void *ret_from_thread;
            pthread_join(tid[j], &ret_from_thread);
            res[i * NTHREADS + j] = (PersonArr *) ret_from_thread;
        }
    }
    for (int i = 0; i < N; ++i) {
        printPersonArr(res[i]);
    }
    for (int i = 0; i < N; ++i) {
        free(res[i]->arr);
    }
    free(res);
}

