#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#pragma once

//#pragma pack(4)
typedef struct {
    char name[16];
    char last_name[16];
    char title[19];
    _Bool sex; // False - men, True - women
    int age;
    int salary;
    int experience;
} Person;

typedef struct {
   Person* arr;
   size_t max_size;
   size_t curr_idx;  // next available element
} PersonArr;

typedef struct {
    int min_age;
    int max_age;
    char title[19];
    PersonArr *persons;
} Title;

typedef struct {
    Title* arr;
    size_t max_size;
    size_t curr_idx;  // next available element
    pthread_mutex_t mutex;
} TitleArr;

void copy_worker(Person *p1, Person *p2);

int Grow(PersonArr *v);

int PushBackPerson(PersonArr *persons, Person* new_person);

int PersonArrInit(PersonArr **persons);

int PersonArrInitInTitle(TitleArr **v);

int GrowTitle(TitleArr *v);

//int PushBackTitle(TitleArr *v, char* new_title, Person* new_person);
int PushBackTitle(TitleArr **titles, char* new_title, Person* new_person);

void printPersonArr(PersonArr *v);