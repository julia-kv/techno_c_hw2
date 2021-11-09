#include "structs.h"

void copy_worker(Person *p1, Person *p2) {
    p1->age = p2->age;
    p1->experience = p2->experience;
    p1->salary = p2->salary;
    p1->sex = p2->sex;
    strcpy(p1->last_name, p2->last_name);
    strcpy(p1->name, p2->name);
    strcpy(p1->title, p2->title);
}

int Grow(PersonArr *v) {
    v->arr = (Person *) realloc(v->arr, (sizeof(Person) * (v->max_size) * 2));
    v->max_size *= 2;
    return 1;
}

int PushBackPerson(PersonArr *persons, Person *new_person) {
    if (persons->curr_idx >= persons->max_size) {
        Grow(persons);
    }
    copy_worker(&(persons->arr[persons->curr_idx]), new_person);
    persons->curr_idx += 1;
    return 1;
}

int GrowTitle(TitleArr *v) {
    v->arr = (Title *) realloc(v->arr, (sizeof(Title) * (v->max_size) * 2));
    v->max_size *= 2;
    return 1;
}

int PersonArrInit(PersonArr **persons) {
    *persons = malloc(sizeof(PersonArr));
    (*persons)->arr = malloc(sizeof(Person));
    (*persons)->curr_idx = 0;
    (*persons)->max_size = 1;
    return 1;
}

int PersonArrInitInTitle(TitleArr **v) {
    (*v)->arr[(*v)->curr_idx].persons = malloc(sizeof(PersonArr));
    (*v)->arr[(*v)->curr_idx].persons->arr = malloc(sizeof(Person));
    (*v)->arr[(*v)->curr_idx].persons->curr_idx = 0;
    (*v)->arr[(*v)->curr_idx].persons->max_size = 1;
    (*v)->curr_idx += 1;
    return 1;
}

int PushBackTitle(TitleArr **titles, char *new_title, Person *new_person) {
    TitleArr *v = *titles;
    for (int i = 0; i < v->curr_idx; ++i) {
        if (strcmp(v->arr[i].title, new_title) == 0) {
            PushBackPerson((PersonArr *) &(v->arr[i].persons->arr), new_person);
            if (new_person->age < v->arr[i].min_age) {
                v->arr[i].min_age = new_person->age;
            }
            if (new_person->age > v->arr[i].max_age) {
                v->arr[i].max_age = new_person->age;
            }
            return 1;
        }
    }
    if (v->curr_idx >= v->max_size) {
        GrowTitle(v);
    }
    PersonArrInitInTitle(&v);
    size_t last_el = v->curr_idx - 1;  // curr_idx points to an empty place
    strcpy((char *) v->arr[last_el].title, new_title);
    v->arr[last_el].min_age = new_person->age;
    v->arr[last_el].max_age = new_person->age;
    PushBackPerson(v->arr[last_el].persons, new_person);
    return 1;
}

void printPersonArr(PersonArr *v) {
    int n;
    n = v->curr_idx;
    for (int i = 0; i < n; ++i) {
        printf("%s %s (%d) - %s (exp. %d, sal. %d)\n",
               v->arr[i].last_name,
               v->arr[i].name,
               v->arr[i].age,
               v->arr[i].title,
               v->arr[i].experience,
               v->arr[i].salary
        );
    }
}

