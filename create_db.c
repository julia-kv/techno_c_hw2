#include <stdio.h>
#include "find.h"

Person *GetPerson(FILE *f) {
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
    db->arr = (Title *) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
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
    FindYoungestByProfession(db);

    printf("\n");
    printf("The oldest workers:\n");
    FindOldestByProfession(db);

    free(db->arr->persons);
    free(db->arr);
    free(db);
    return 0;
}

