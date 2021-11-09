#include <dlfcn.h>
#include <stdio.h>
#include "structs.h"

void *library;
void (*FindYoung)(TitleArr *v);
void (*FindOld)(TitleArr *v);

Person* GetPerson(FILE *f) {
    Person *new_person;
    new_person = (Person*) malloc(sizeof(Person));
    int sex, age, salary, experience;
    fscanf(f, "%s %s %s %d %d %d %d",
           new_person->name, new_person->last_name, new_person->title,
           &sex,
           &(new_person->age),
           &(new_person->salary),
           &(new_person->experience));
    new_person->sex = (sex == 1) ? true : false;
    return new_person;
}

int CreateDb() {

    TitleArr *db = (TitleArr *) malloc(sizeof(TitleArr));
    pthread_mutex_init (&(db->mutex), NULL);
    db->arr = (Title *) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
    db->arr->persons = (PersonArr*) malloc(sizeof(PersonArr));
    FILE *f = fopen("../data.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }
    while (!feof(f)) {
        Person *person = GetPerson(f);
        PushBackTitle(&db, person->title, person);
    }
    if (fclose(f)) {
        fprintf(stderr, "Failed to close file\n");
        return 1;
    }

    printf("The youngest workers:\n");

    library = dlopen("./db_lib_dynamic.so", RTLD_LAZY);
    FindYoung = dlsym(library, "FindYoungestByProfession");
    FindYoung(db);

    FindOld = dlsym(library, "FindOldestByProfession");
    FindOld(db);
    dlclose(library);

    free(db);
    return 0;
}

