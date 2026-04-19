#include <gtest/gtest.h>

#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "NormalBitSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"

TEST(TestDynamicArray, size_create){

    DynamicArray<int> arr(4);

    EXPECT_EQ(arr.get_size(), 4);
    EXPECT_EQ(arr.get(0), 0);
    EXPECT_EQ(arr.get(1), 0);
    EXPECT_EQ(arr.get(2), 0);
    EXPECT_EQ(arr.get(3), 0);
    
}

TEST(TestDynamicArray, create_from_arr){

    int items[] = {67, 52, 42, 228, 141};
    DynamicArray<int> arr(items, 4);

    EXPECT_EQ(arr.get_size(), 4);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);
    EXPECT_EQ(arr.get(3), 228);
    
    DynamicArray<int> arr2(items, 0);

    EXPECT_EQ(arr2.get_size(), 0);
    EXPECT_THROW(arr2.get(0), index_out_of_range);

}

TEST(TestDynamicArray, create_from_another){

    int items[] = {67, 52, 42, 228, 141};
    DynamicArray<int> arr(items, 4);

    arr.append(37);

    EXPECT_EQ(arr.get(4), 37);

    DynamicArray<int> res(arr);

    EXPECT_EQ(res.get_size(), 5);
    EXPECT_EQ(res.get(0), 67);
    EXPECT_EQ(res.get(1), 52);
    EXPECT_EQ(res.get(2), 42);
    EXPECT_EQ(res.get(3), 228);
    EXPECT_EQ(res.get(4), 37);
    
}

TEST(TestDynamicArray, check_methods){

    DynamicArray<int> arr(0);

    arr.append(52);
    arr.append(42);

    EXPECT_EQ(arr.get(0), 52);
    EXPECT_EQ(arr.get(1), 42);
    EXPECT_EQ(arr.get_size(), 2);

    EXPECT_THROW(arr.get(-100), index_out_of_range);
    EXPECT_THROW(arr.get(100), index_out_of_range);
    EXPECT_THROW(arr.set(-10, 10), index_out_of_range);
    EXPECT_THROW(arr.set(100, 10), index_out_of_range);

    arr.set(0, 10);
    EXPECT_EQ(arr.get(0), 10);

    arr.resize(2);
    EXPECT_EQ(arr.get_size(), 2);

    arr.resize(4);
    EXPECT_EQ(arr.get_size(), 4);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 42);
    EXPECT_EQ(arr.get(2), 0);
    EXPECT_EQ(arr.get(3), 0);

    arr.resize(1);
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_THROW(arr.get(1), index_out_of_range);

}

TEST(TestDynamicArray, check_operator){

    int items[] = {67, 52, 42, 228, 141};
    DynamicArray<int> arr(items, 4);
    DynamicArray<int> another(0);

    arr = arr;

    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);
    EXPECT_EQ(arr.get(3), 228);

    another = arr;

    EXPECT_EQ(another.get_size(), 4);
    EXPECT_EQ(another.get(0), 67);
    EXPECT_EQ(another.get(1), 52);
    EXPECT_EQ(another.get(2), 42);
    EXPECT_EQ(another.get(3), 228);
    
    another.append(10);
    another.set(2, 2);
    arr.set(2, 3);
    arr.resize(3);

    EXPECT_EQ(another.get_size(), 5);
    EXPECT_EQ(another.get(0), 67);
    EXPECT_EQ(another.get(1), 52);
    EXPECT_EQ(another.get(2), 2);
    EXPECT_EQ(another.get(3), 228);
    EXPECT_EQ(another.get(4), 10);
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 3);

    EXPECT_EQ(arr[0], 67);
    EXPECT_EQ(arr[1], 52);
    EXPECT_EQ(arr[2], 3);
    EXPECT_THROW(arr[-10], index_out_of_range);
    EXPECT_THROW(arr[200], index_out_of_range);

    arr = arr + arr;

    EXPECT_EQ(arr.get_size(), 6);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 3);
    EXPECT_EQ(arr.get(3), 67);
    EXPECT_EQ(arr.get(4), 52);
    EXPECT_EQ(arr.get(5), 3);

    arr.append(10);
    arr.set(0, 2);

    EXPECT_EQ(arr.get_size(), 7);
    EXPECT_EQ(arr.get(0), 2);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 3);
    EXPECT_EQ(arr.get(3), 67);
    EXPECT_EQ(arr.get(4), 52);
    EXPECT_EQ(arr.get(5), 3);
    EXPECT_EQ(arr.get(6), 10);
    
}

TEST(TestLinkedList, create_empty_list_and_check_throw){

    LinkedList<int> list;

    EXPECT_EQ(list.get_length(), 0);
    EXPECT_THROW(list.get_first(), empty_container);
    EXPECT_THROW(list.get_last(), empty_container);
    EXPECT_THROW(list.get(-10), index_out_of_range);
    EXPECT_THROW(list.get(0), index_out_of_range);
    EXPECT_THROW(list.get(10), index_out_of_range);
    EXPECT_THROW(list.set(-10, 10), index_out_of_range);
    EXPECT_THROW(list.set(10, 10), index_out_of_range);
    EXPECT_THROW(list.set(0, 10), index_out_of_range);
    EXPECT_THROW(list.get_sub_list(-10, 0), index_out_of_range);

}

TEST(TestLinkedList, create_from_arr){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get_first(), 67);
    EXPECT_EQ(list.get_last(), 42);
    EXPECT_EQ(list.get(0), 67);
    EXPECT_EQ(list.get(1), 52);
    EXPECT_EQ(list.get(2), 42);
    
    LinkedList<int> list2(items, 0);

    EXPECT_EQ(list2.get_length(), 0);
    EXPECT_THROW(list2.get(0), index_out_of_range);

}

TEST(TestLinkedList, create_from_list){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);
    LinkedList<int> list2(list);

    EXPECT_EQ(list2.get_length(), 3);
    EXPECT_EQ(list2.get(0), 67);
    EXPECT_EQ(list2.get(1), 52);
    EXPECT_EQ(list2.get(2), 42);

    list.append(10);
    list.prepend(1);
    
    EXPECT_EQ(list.get_length(), 5);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 67);
    EXPECT_EQ(list.get(2), 52);
    EXPECT_EQ(list.get(3), 42);
    EXPECT_EQ(list.get(4), 10);
    EXPECT_EQ(list2.get_length(), 3);
    EXPECT_EQ(list2.get(0), 67);
    EXPECT_EQ(list2.get(1), 52);
    EXPECT_EQ(list2.get(2), 42);

    list2.append(2);
    list2.prepend(3);
    
    EXPECT_EQ(list.get_length(), 5);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 67);
    EXPECT_EQ(list.get(2), 52);
    EXPECT_EQ(list.get(3), 42);
    EXPECT_EQ(list.get(4), 10);
    EXPECT_EQ(list2.get_length(), 5);
    EXPECT_EQ(list2.get(0), 3);
    EXPECT_EQ(list2.get(1), 67);
    EXPECT_EQ(list2.get(2), 52);
    EXPECT_EQ(list2.get(3), 42);
    EXPECT_EQ(list2.get(4), 2);

    LinkedList<int> list3;
    LinkedList<int> list4(list3);

    EXPECT_EQ(list4.get_length(), 0);
    EXPECT_THROW(list4.get(0), index_out_of_range);

}

TEST(TestLinkedList, check_methods){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);
    
    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get(0), 67);
    EXPECT_EQ(list.get(1), 52);
    EXPECT_EQ(list.get(2), 42);
    EXPECT_THROW(list.get(-10), index_out_of_range);
    EXPECT_THROW(list.get(100), index_out_of_range);
    EXPECT_THROW(list.set(-10, 10), index_out_of_range);
    EXPECT_THROW(list.set(100, 10), index_out_of_range);
    EXPECT_EQ(list.get_first(), 67);
    EXPECT_EQ(list.get_last(), 42);
    
    list.append(10);
    list.prepend(-10);
    list.insert_at(111, 2);

    EXPECT_EQ(list.get_length(), 6);
    EXPECT_EQ(list.get(0), -10);
    EXPECT_EQ(list.get(1), 67);
    EXPECT_EQ(list.get(2), 111);
    EXPECT_EQ(list.get(3), 52);
    EXPECT_EQ(list.get(4), 42);
    EXPECT_EQ(list.get(5), 10);

    LinkedList<int> *new_list = list.concat(&list);
    new_list->append(3);
    new_list->prepend(1);

    EXPECT_EQ(new_list->get_length(), 14);
    EXPECT_EQ(new_list->get(0), 1);
    EXPECT_EQ(new_list->get(1), -10);
    EXPECT_EQ(new_list->get(2), 67);
    EXPECT_EQ(new_list->get(3), 111);
    EXPECT_EQ(new_list->get(4), 52);
    EXPECT_EQ(new_list->get(5), 42);
    EXPECT_EQ(new_list->get(6), 10);
    EXPECT_EQ(new_list->get(7), -10);
    EXPECT_EQ(new_list->get(8), 67);
    EXPECT_EQ(new_list->get(9), 111);
    EXPECT_EQ(new_list->get(10), 52);
    EXPECT_EQ(new_list->get(11), 42);
    EXPECT_EQ(new_list->get(12), 10);
    EXPECT_EQ(new_list->get(13), 3);

    delete new_list;

    LinkedList<int> list2;
    LinkedList<int> *new_list2 = list.concat(&list2);

    EXPECT_EQ(new_list2->get(0), -10);
    EXPECT_EQ(new_list2->get(1), 67);
    EXPECT_EQ(new_list2->get(2), 111);
    EXPECT_EQ(new_list2->get(3), 52);
    EXPECT_EQ(new_list2->get(4), 42);
    EXPECT_EQ(new_list2->get(5), 10);

    delete new_list2;

    LinkedList<int> *new_list3 = list.get_sub_list(0, 5);

    EXPECT_EQ(new_list3->get(0), -10);
    EXPECT_EQ(new_list3->get(1), 67);
    EXPECT_EQ(new_list3->get(2), 111);
    EXPECT_EQ(new_list3->get(3), 52);
    EXPECT_EQ(new_list3->get(4), 42);
    EXPECT_EQ(new_list3->get(5), 10);

    delete new_list3;

    LinkedList<int> *new_list4 = list.get_sub_list(5, 0);

    EXPECT_EQ(new_list4->get(0), 10);
    EXPECT_EQ(new_list4->get(1), 42);
    EXPECT_EQ(new_list4->get(2), 52);
    EXPECT_EQ(new_list4->get(3), 111);
    EXPECT_EQ(new_list4->get(4), 67);
    EXPECT_EQ(new_list4->get(5), -10);

    EXPECT_THROW(new_list4->get_sub_list(-1, 4), index_out_of_range);
    EXPECT_THROW(new_list4->get_sub_list(0, 7), index_out_of_range);
    EXPECT_THROW(new_list4->get_sub_list(7, 2), index_out_of_range);
    EXPECT_THROW(new_list4->get_sub_list(7, 7), index_out_of_range);

    delete new_list4;

}

TEST(TestLinkedList, check_operators){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);

    EXPECT_EQ(list[0], 67);
    EXPECT_EQ(list[1], 52);
    EXPECT_EQ(list[2], 42);
    EXPECT_THROW(list[-10], index_out_of_range);
    EXPECT_THROW(list[10], index_out_of_range);

    LinkedList<int> res;
    res = list;

    list.set(2, 10);
    res.set(0, 12);

    EXPECT_EQ(list[0], 67);
    EXPECT_EQ(list[2], 10);
    EXPECT_EQ(res[0], 12);
    EXPECT_EQ(res[1], 52);
    EXPECT_EQ(res[2], 42);
    EXPECT_THROW(res[-10], index_out_of_range);
    EXPECT_THROW(res[10], index_out_of_range);

    list = list;

    EXPECT_EQ(list[0], 67);
    EXPECT_EQ(list[1], 52);
    EXPECT_EQ(res[2], 10);
    EXPECT_EQ(res[3], 67);
    EXPECT_EQ(res[4], 62);
    EXPECT_EQ(list[5], 10);

    LinkedList<int> ress;
    ress = list + res;
    list.set(0, 12111);
    res.set(2, 121);

    EXPECT_EQ(list[0], 12111);
    EXPECT_EQ(res[2], 121);
    EXPECT_EQ(ress.get_length(), 6);
    EXPECT_EQ(ress[0], 67);
    EXPECT_EQ(ress[1], 52);
    EXPECT_EQ(ress[2], 10);
    EXPECT_EQ(ress[3], 12);
    EXPECT_EQ(ress[4], 52);
    EXPECT_EQ(ress[5], 42);    

}