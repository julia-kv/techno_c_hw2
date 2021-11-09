#pragma once
#include "structs.h"

int CmpFunc(const void *p1, const void *p2);

void* FindYoungest(void *arg);

void FindYoungestByProfession(TitleArr *v);

void* FindOldest(void *arg);

void FindOldestByProfession(TitleArr *v);
