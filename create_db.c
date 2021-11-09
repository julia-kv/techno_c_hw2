#include "find.h"
#include "stdio.h"

Person *GetPerson(FILE *f) {
    Person *new_person;
    new_person = (Person *) malloc(sizeof(Person));
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
    db->arr = (Title *) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
    FILE *f = fopen("/home/julia/CLionProjects/C++_HW2/data.txt", "r");
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
    FindYoungestByProfession(db);

}

