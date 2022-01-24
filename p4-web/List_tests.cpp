// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_size_push_back_push_front) {
    List<int> my_list;
    my_list.push_back(42);
    my_list.push_back(42);

    my_list.push_front(42);
    my_list.push_front(42);

    ASSERT_TRUE(my_list.size() == 4);
}

TEST(test_list_front_back) {
    List<int> my_list;
    my_list.push_back(42);
    my_list.push_back(42);

    my_list.push_front(42);
    my_list.push_front(42);

    my_list.front() = 10;
    my_list.back() = 11;

    ASSERT_TRUE(my_list.front() == 10);
    ASSERT_TRUE(my_list.back() == 11);

    my_list.push_back(20);    
    my_list.push_front(21);

    ASSERT_TRUE(my_list.front() == 21);
    ASSERT_TRUE(my_list.back() == 20);
}

TEST(test_list_pop_front_pop_back_clear) {
    List<int> my_list;
    my_list.push_back(5);
    my_list.push_back(6);

    my_list.push_front(7);
    my_list.push_front(8);
    // 8756

    ASSERT_TRUE(my_list.size() == 4);
    ASSERT_TRUE(my_list.back() == 6);

    my_list.pop_back();
    ASSERT_TRUE(my_list.size() == 3);
    ASSERT_TRUE(my_list.back() == 5);

    ASSERT_TRUE(my_list.front() == 8);

    my_list.pop_front();
    ASSERT_TRUE(my_list.size() == 2);
    ASSERT_TRUE(my_list.back() == 5);  
    ASSERT_TRUE(my_list.front() == 7);

    my_list.clear();
    ASSERT_TRUE(my_list.size() == 0);
}

TEST_MAIN()
