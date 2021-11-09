#include <dlfcn.h>
#include <stdio.h>
#include "structs.h"

void *library;
void (*Find)(TitleArr *v);

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

void CreateDb() {

    TitleArr *db = (TitleArr *) malloc(sizeof(TitleArr));
    pthread_mutex_init (&(db->mutex), NULL);
    db->arr = (Title *) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
    db->arr->persons = (PersonArr*) malloc(sizeof(PersonArr));
    FILE *f = fopen("../data.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return;
    }
    while (!feof(f)) {
        Person *person = GetPerson(f);
        PushBackTitle(&db, person->title, person);
    }
    if (fclose(f)) {
        fprintf(stderr, "Failed to close file\n");
        return;
    }

    printf("The youngest workers:\n");

    library = dlopen("./db_lib_dynamic.so", RTLD_LAZY);
    Find = dlsym(library, "FindYoungestByProfession");
    Find(db);
    dlclose(library);
}

