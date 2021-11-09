#include <gtest/gtest.h>

extern "C" {
#include "structs.h"
#include "find.h"
#include "create_database.h"
}
TEST(INPUT_PERSON_TEST, right_input_test) {
    Person first = {"Bob","Green","eng",false,30,10,1};
    TitleArr *db = (TitleArr*) malloc(sizeof(TitleArr));
    db->arr = (Title*) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
    PushBackTitle(&db, first.title, &first);
}

TEST(FIND_TEST, right_input_test) {
    Person first = { "Bob", "Green", "eng", false, 30, 10, 1, };
    Person second = { "Met", "Rose", "eng", false, 30, 10, 1, };
    Person third = { "A", "Alex", "teacher", false, 30, 10, 1, };
    TitleArr *db = (TitleArr*) malloc(sizeof(TitleArr));
    db->arr = (Title*) malloc(sizeof(Title));
    db->max_size = 1;
    db->curr_idx = 0;
    PushBackTitle(&db, first.title, &first);
    PushBackTitle(&db, second.title, &second);
    PushBackTitle(&db, third.title, &third);
    FindYoungest(&(db->arr[db->curr_idx - 1]));
    FindYoungestByProfession(db);
}

TEST(INPUT_BD_TEST, right_output_test) {
    CreateDb();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}