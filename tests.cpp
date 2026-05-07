#include <cstdio>
#include <iostream>

#include <gtest/gtest.h>

#include "includes/Exception.h"

#include "includes/DynamicArray.h"
#include "includes/LinkedList.h"
#include "includes/ArraySequence.h"
#include "includes/ListSequence.h"
#include "includes/Sequence.h"
#include "includes/DiagonalMatrix.h"

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
    EXPECT_EQ(list[2], 10);
    EXPECT_THROW(list[3], index_out_of_range);
    EXPECT_THROW(list[-1], index_out_of_range);

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

TEST(TestArraySequence, create_empty_array){

    ArraySequence<int> arr;

    EXPECT_EQ(arr.get_length(), 0);
    EXPECT_THROW(arr.get(0), index_out_of_range);
    EXPECT_THROW(arr.get_first(), empty_container);
    EXPECT_THROW(arr.get_last(), empty_container);

}

TEST(TestArraySequence, create_from_array){

    int items[] = {67, 52, 42, 228, 141};
    ArraySequence<int> arr(items, 3);

    EXPECT_EQ(arr.get_length(), 3);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);
    EXPECT_THROW(arr.get(-1), index_out_of_range);
    EXPECT_THROW(arr.get(3), index_out_of_range);

    ArraySequence<int> arr2(items, 0);

    EXPECT_EQ(arr2.get_length(), 0);
    EXPECT_THROW(arr2.get(0), index_out_of_range);

}

TEST(TestArraySequence, size_create){

    ArraySequence<int> arr(3);

    EXPECT_EQ(arr.get_length(), 3);
    EXPECT_EQ(arr.get(0), 0);
    EXPECT_EQ(arr.get(1), 0);
    EXPECT_EQ(arr.get(2), 0);

    ArraySequence<int> arr3(0);

    EXPECT_EQ(arr3.get_length(), 0);
    EXPECT_THROW(arr3.get(0), index_out_of_range);

}

TEST(TestArraySequence, create_from_dynamic_array){

    int items[] = {67, 52, 42, 228, 141};
    DynamicArray<int> arr(items, 3);

    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);

    ArraySequence<int> res(arr);
    arr.set(1, 11);

    EXPECT_EQ(arr.get(1), 11);
    EXPECT_EQ(res.get_length(), 3);
    EXPECT_EQ(res.get(0), 67);
    EXPECT_EQ(res.get(1), 52);
    EXPECT_EQ(res.get(2), 42);
    EXPECT_THROW(res.get(3), index_out_of_range);

}

TEST(TestArraySequence, create_from_another){

    int items[] = {67, 52, 42, 228, 141};
    DynamicArray<int> arr(items, 3);

    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);

    ArraySequence<int> res(arr);

    EXPECT_EQ(res.get_length(), 3);
    EXPECT_EQ(res.get(0), 67);
    EXPECT_EQ(res.get(1), 52);
    EXPECT_EQ(res.get(2), 42);

    ArraySequence<int> ans(res);

    arr.set(1, 2121);
    res.set(0, 3232);

    EXPECT_EQ(arr.get(1), 2121);
    EXPECT_EQ(res.get(0), 3232);
    EXPECT_EQ(ans.get_length(), 3);
    EXPECT_EQ(ans.get(0), 67);
    EXPECT_EQ(ans.get(1), 52);
    EXPECT_EQ(ans.get(2), 42);
    EXPECT_THROW(ans.get(3), index_out_of_range);

    ArraySequence<int> empty_arr;

    EXPECT_EQ(empty_arr.get_length(), 0);
    EXPECT_THROW(empty_arr.get(0), index_out_of_range);

    ArraySequence<int> ress(empty_arr);

    empty_arr.append(10);

    EXPECT_EQ(empty_arr.get_length(), 1);
    EXPECT_EQ(empty_arr.get(0), 10);
    EXPECT_EQ(ress.get_length(), 0);
    EXPECT_THROW(ress.get(0), index_out_of_range);

}

TEST(TestArraySequence, check_methods){

    int items[] = {67, 52, 42, 228, 141};
    ArraySequence<int> arr(items, 3);

    EXPECT_EQ(arr.get_length(), 3);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);

    arr.append(10);

    EXPECT_EQ(arr.get_length(), 4);
    EXPECT_EQ(arr.get(0), 67);
    EXPECT_EQ(arr.get(1), 52);
    EXPECT_EQ(arr.get(2), 42);
    EXPECT_EQ(arr.get(3), 10);

    arr.prepend(-10);

    EXPECT_EQ(arr.get_length(), 5);
    EXPECT_EQ(arr.get(0), -10);
    EXPECT_EQ(arr.get(1), 67);
    EXPECT_EQ(arr.get(2), 52);
    EXPECT_EQ(arr.get(3), 42);
    EXPECT_EQ(arr.get(4), 10);

    arr.insert_at(12, 1);

    EXPECT_EQ(arr.get_length(), 6);
    EXPECT_EQ(arr.get(0), -10);
    EXPECT_EQ(arr.get(1), 12);
    EXPECT_EQ(arr.get(2), 67);
    EXPECT_EQ(arr.get(3), 52);
    EXPECT_EQ(arr.get(4), 42);
    EXPECT_EQ(arr.get(5), 10);

    arr.set(2, 13);

    EXPECT_EQ(arr.get_length(), 6);
    EXPECT_EQ(arr.get(0), -10);
    EXPECT_EQ(arr.get(1), 12);
    EXPECT_EQ(arr.get(2), 13);
    EXPECT_EQ(arr.get(3), 52);
    EXPECT_EQ(arr.get(4), 42);
    EXPECT_EQ(arr.get(5), 10);

    EXPECT_EQ(arr.get_first(), -10);
    EXPECT_EQ(arr.get_last(), 10);
    
    ArraySequence<int> arr1;
    Sequence<int> *res = arr.concat(&arr1);

    EXPECT_EQ(res->get_length(), 6);
    EXPECT_EQ(res->get(0), -10);
    EXPECT_EQ(res->get(1), 12);
    EXPECT_EQ(res->get(2), 13);
    EXPECT_EQ(res->get(3), 52);
    EXPECT_EQ(res->get(4), 42);
    EXPECT_EQ(res->get(5), 10);

    delete res;

    ArraySequence<int> arr2;
    ArraySequence<int> arr3;
    Sequence<int> *ress = arr2.concat(&arr3);

    EXPECT_EQ(ress->get_length(), 0);
    EXPECT_THROW(ress->get(0), index_out_of_range);

    delete ress;

    ArraySequence<int> arr4;
    Sequence<int> *resss = arr4.concat(&arr);

    EXPECT_EQ(resss->get_length(), 6);
    EXPECT_EQ(resss->get(0), -10);
    EXPECT_EQ(resss->get(1), 12);
    EXPECT_EQ(resss->get(2), 13);
    EXPECT_EQ(resss->get(3), 52);
    EXPECT_EQ(resss->get(4), 42);
    EXPECT_EQ(resss->get(5), 10);

    delete resss;

    Sequence<int> *qwerty = arr.concat(nullptr);

    EXPECT_EQ(qwerty->get_length(), 6);
    EXPECT_EQ(qwerty->get(0), -10);
    EXPECT_EQ(qwerty->get(1), 12);
    EXPECT_EQ(qwerty->get(2), 13);
    EXPECT_EQ(qwerty->get(3), 52);
    EXPECT_EQ(qwerty->get(4), 42);
    EXPECT_EQ(qwerty->get(5), 10);

    delete qwerty;

    Sequence<int> *ans = arr.get_sub_sequence(1, 4);

    EXPECT_EQ(ans->get_length(), 4);
    EXPECT_EQ(ans->get(0), 12);
    EXPECT_EQ(ans->get(1), 13);
    EXPECT_EQ(ans->get(2), 52);
    EXPECT_EQ(ans->get(3), 42);

    delete ans;

    Sequence<int> *ans2 = arr.get_sub_sequence(4, 1);

    EXPECT_EQ(ans2->get_length(), 4);
    EXPECT_EQ(ans2->get(0), 42);
    EXPECT_EQ(ans2->get(1), 52);
    EXPECT_EQ(ans2->get(2), 13);
    EXPECT_EQ(ans2->get(3), 12);

    delete ans2;

    Sequence<int> *ans3 = arr.get_sub_sequence(1, 1);

    EXPECT_EQ(ans3->get_length(), 1);
    EXPECT_EQ(ans3->get(0), 12);

    delete ans3;

    EXPECT_THROW(arr.get_sub_sequence(-1, 4), index_out_of_range);
    EXPECT_THROW(arr.get_sub_sequence(-1, 10), index_out_of_range);
    EXPECT_THROW(arr.get_sub_sequence(0, 10), index_out_of_range);

}

TEST(TestArraySequence, check_operators){

    int items[] = {67, 52, 42, 228, 141};
    ArraySequence<int> arr(items, 3);

    EXPECT_EQ(arr.get_length(), 3);
    EXPECT_EQ(arr[0], 67);
    EXPECT_EQ(arr[1], 52);
    EXPECT_EQ(arr[2], 42);
    EXPECT_THROW(arr[-10], index_out_of_range);
    EXPECT_THROW(arr[20], index_out_of_range);

    arr = arr;

    EXPECT_EQ(arr.get_length(), 3);
    EXPECT_EQ(arr[0], 67);
    EXPECT_EQ(arr[1], 52);
    EXPECT_EQ(arr[2], 42);

    ArraySequence<int> res;

    res = arr;
    arr.set(0, 19);
    res.set(1, 1);

    EXPECT_EQ(res.get_length(), 3);
    EXPECT_EQ(res[0], 67);
    EXPECT_EQ(res[1], 1);
    EXPECT_EQ(res[2], 42);
    EXPECT_EQ(arr[0], 19);
    EXPECT_EQ(arr[1], 52);
    EXPECT_EQ(arr[2], 42);

    ArraySequence<int> ress;

    ress = res + arr;
    arr.set(1, 19);
    res.set(2, 1);

    EXPECT_EQ(arr[1], 19);
    EXPECT_EQ(res[2], 1);
    EXPECT_EQ(ress.get_length(), 6);
    EXPECT_EQ(ress[0], 67);
    EXPECT_EQ(ress[1], 1);
    EXPECT_EQ(ress[2], 42);
    EXPECT_EQ(ress[3], 19);
    EXPECT_EQ(ress[4], 52);
    EXPECT_EQ(ress[5], 42);

    ArraySequence<int> a, b, c;

    a = b + c;

    EXPECT_EQ(a.get_length(), 0);
    EXPECT_THROW(a[0], index_out_of_range);

}

TEST(TestListSequence, create_empty_list){

    ListSequence<int> list;

    EXPECT_EQ(list.get_length(), 0);
    EXPECT_THROW(list.get(0), index_out_of_range);
    EXPECT_THROW(list.get_first(), empty_container);
    EXPECT_THROW(list.get_last(), empty_container);

}

TEST(TestListSequence, create_from_array){

    int items[] = {67, 52, 42, 228, 141};
    ListSequence<int> list(items, 3);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get(0), 67);
    EXPECT_EQ(list.get(1), 52);
    EXPECT_EQ(list.get(2), 42);
    EXPECT_THROW(list.get(-1), index_out_of_range);
    EXPECT_THROW(list.get(10), index_out_of_range);

}

TEST(TestListSequence, create_from_linked_list){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);
    ListSequence<int> res(list);

    list.set(0, 11);
    res.set(1, 32);

    EXPECT_EQ(res.get_length(), 3);
    EXPECT_EQ(res.get(0), 67);
    EXPECT_EQ(res.get(1), 32);
    EXPECT_EQ(res.get(2), 42);
    EXPECT_THROW(res.get(3), index_out_of_range);
    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get(0), 11);
    EXPECT_EQ(list.get(1), 52);

}

TEST(TestListSequence, create_from_another){

    int items[] = {67, 52, 42, 228, 141};
    LinkedList<int> list(items, 3);
    ListSequence<int> bob(list);
    ListSequence<int> res(bob);

    list.set(0, 12);
    bob.set(1, 13);
    res.set(2, 14);

    EXPECT_EQ(list.get(0), 12);
    EXPECT_EQ(list.get(2), 42);
    EXPECT_EQ(bob.get(1), 13);
    EXPECT_EQ(bob.get(2), 42);
    EXPECT_EQ(res.get_length(), 3); 
    EXPECT_EQ(res.get(0), 67);
    EXPECT_EQ(res.get(1), 52);
    EXPECT_EQ(res.get(2), 14);
    EXPECT_THROW(res.get(3), index_out_of_range);

    LinkedList<int> listik;
    ListSequence<int> bobik(listik);
    ListSequence<int> resik(bobik);

    bobik.append(10);

    EXPECT_EQ(resik.get_length(), 0);
    EXPECT_THROW(resik.get(0), index_out_of_range);
    
    resik.append(21);
    
    EXPECT_EQ(resik.get_length(), 1);
    EXPECT_EQ(resik.get(0), 21);
    EXPECT_EQ(bobik.get(0), 10);
    EXPECT_THROW(listik.get(0), index_out_of_range);

}

TEST(TestListSequence, check_methods){

    int items[] = {67, 52, 42, 228, 141};
    ListSequence<int> list(items, 2);

    EXPECT_EQ(list.get_length(), 2);
    EXPECT_EQ(list.get(0), 67);
    EXPECT_EQ(list.get(1), 52);
    EXPECT_THROW(list.get(2), index_out_of_range);

    list.append(10);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list.get(2), 10);

    list.prepend(-10);

    EXPECT_EQ(list.get_length(), 4);
    EXPECT_EQ(list.get(0), -10);

    list.set(1, 33);

    EXPECT_EQ(list.get_length(), 4);
    EXPECT_EQ(list.get(0), -10);
    EXPECT_EQ(list.get(1), 33);
    EXPECT_EQ(list.get(2), 52);
    EXPECT_EQ(list.get(3), 10);
    EXPECT_THROW(list.get(4), index_out_of_range);

    list.insert_at(37, 1);
    
    EXPECT_EQ(list.get_length(), 5);
    EXPECT_EQ(list.get(0), -10);
    EXPECT_EQ(list.get(1), 37);
    EXPECT_EQ(list.get(2), 33);
    EXPECT_EQ(list.get(3), 52);
    EXPECT_EQ(list.get(4), 10);
    EXPECT_THROW(list.get(5), index_out_of_range);

    EXPECT_EQ(list.get_first(), -10);
    EXPECT_EQ(list.get_last(), 10);

    ListSequence<int> list2(items, 2);

    EXPECT_EQ(list2.get(0), 67);
    EXPECT_EQ(list2.get(1), 52);

    Sequence<int> *res3 = list2.concat(&list2);
    list2.set(0, 10);

    EXPECT_EQ(list2.get(0), 10);
    EXPECT_EQ(res3->get_length(), 4);
    EXPECT_EQ(res3->get(0), 67);
    EXPECT_EQ(res3->get(1), 52);
    EXPECT_EQ(res3->get(2), 67);
    EXPECT_EQ(res3->get(3), 52);
    EXPECT_THROW(res3->get(4), index_out_of_range); 

    Sequence<int> *res4 = res3->concat(&list2);

    EXPECT_EQ(res4->get_length(), 6);
    EXPECT_EQ(res4->get(0), 67);
    EXPECT_EQ(res4->get(1), 52);
    EXPECT_EQ(res4->get(2), 67);
    EXPECT_EQ(res4->get(3), 52);
    EXPECT_EQ(res4->get(4), 10);
    EXPECT_EQ(res4->get(5), 52);
    EXPECT_THROW(res4->get(6), index_out_of_range); 

    delete res3;
    delete res4;

    Sequence<int> *res5 = list2.concat(nullptr);

    EXPECT_EQ(res5->get_length(), 2);
    EXPECT_EQ(res5->get(0), 10);
    EXPECT_EQ(res5->get(1), 52);
    EXPECT_THROW(res5->get(2), index_out_of_range);

    delete res5;

    Sequence<int> *res = list.get_sub_sequence(1, 3);
    list.set(1, 10);

    EXPECT_EQ(list.get(1), 10);
    EXPECT_EQ(res->get_length(), 3);
    EXPECT_EQ(res->get(0), 37);
    EXPECT_EQ(res->get(1), 33);
    EXPECT_EQ(res->get(2), 52);

    Sequence<int> *ans = res->get_sub_sequence(0, 2);
    delete res;

    EXPECT_EQ(ans->get_length(), 3);
    EXPECT_EQ(ans->get(0), 37);
    EXPECT_EQ(ans->get(1), 33);
    EXPECT_EQ(ans->get(2), 52);

    Sequence<int> *res2 = ans->get_sub_sequence(2, 0);
    delete ans;

    EXPECT_EQ(res2->get_length(), 3);
    EXPECT_EQ(res2->get(0), 52);
    EXPECT_EQ(res2->get(1), 33);
    EXPECT_EQ(res2->get(2), 37);

    EXPECT_THROW(res2->get_sub_sequence(-1, 10), index_out_of_range);
    EXPECT_THROW(res2->get_sub_sequence(-1, 2), index_out_of_range);
    EXPECT_THROW(res2->get_sub_sequence(0, 10), index_out_of_range);

    delete res2;

}

TEST(TestListSequence, check_operators){

    int items[] = {67, 52, 42, 228, 141};
    ListSequence<int> list(items, 3);

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list[0], 67);
    EXPECT_EQ(list[1], 52);
    EXPECT_EQ(list[2], 42);
    EXPECT_THROW(list[-10], index_out_of_range);
    EXPECT_THROW(list[20], index_out_of_range);

    list = list;

    EXPECT_EQ(list.get_length(), 3);
    EXPECT_EQ(list[0], 67);
    EXPECT_EQ(list[1], 52);
    EXPECT_EQ(list[2], 42);

    ListSequence<int> res;

    res = list;
    list.set(0, 19);
    res.set(1, 1);

    EXPECT_EQ(res.get_length(), 3);
    EXPECT_EQ(res[0], 67);
    EXPECT_EQ(res[1], 1);
    EXPECT_EQ(res[2], 42);
    EXPECT_EQ(list[0], 19);
    EXPECT_EQ(list[1], 52);
    EXPECT_EQ(list[2], 42);

    ListSequence<int> ress;

    ress = res + list;
    list.set(1, 19);
    res.set(2, 1);

    EXPECT_EQ(list[1], 19);
    EXPECT_EQ(res[2], 1);
    EXPECT_EQ(ress.get_length(), 6);
    EXPECT_EQ(ress[0], 67);
    EXPECT_EQ(ress[1], 1);
    EXPECT_EQ(ress[2], 42);
    EXPECT_EQ(ress[3], 19);
    EXPECT_EQ(ress[4], 52);
    EXPECT_EQ(ress[5], 42);

    ListSequence<int> a, b, c;

    a = b + c;

    EXPECT_EQ(a.get_length(), 0);
    EXPECT_THROW(a[0], index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_array_sequence){

    int items[] = {1, 2, 3};

    ArraySequence<int> seq(items, 3);
    DiagonalMatrix<ArraySequence, int> matrix(seq, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    EXPECT_EQ(matrix.get(0), 1);
    EXPECT_EQ(matrix.get(1), 2);
    EXPECT_EQ(matrix.get(2), 3);

    EXPECT_THROW(matrix.get(3), index_out_of_range);
    EXPECT_THROW(matrix.get(-1), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_list_sequence){

    int items[] = {1, 2, 3};

    ListSequence<int> list(items, 3);
    DiagonalMatrix<ListSequence, int> matrix(list, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    EXPECT_EQ(matrix.get(0), 1);
    EXPECT_EQ(matrix.get(1), 2);
    EXPECT_EQ(matrix.get(2), 3);

    EXPECT_THROW(matrix.get(3), index_out_of_range);
    EXPECT_THROW(matrix.get(-1), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_linked_list){

    int items[] = {1, 2, 3, 4};
    LinkedList<int> list(items, 3);

    DiagonalMatrix<LinkedList, int> matrix(list, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    
    EXPECT_EQ(matrix.get(0), 1);
    EXPECT_EQ(matrix.get(1), 2);
    EXPECT_EQ(matrix.get(2), 3);
    EXPECT_THROW(matrix.get(-1), index_out_of_range);
    EXPECT_THROW(matrix.get(3), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_dynamic_array){

    int items[] = {1, 2, 3, 4};
    DynamicArray<int> array(items, 3);

    DiagonalMatrix<DynamicArray, int> matrix(array, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    
    EXPECT_EQ(matrix.get(0), 1);
    EXPECT_EQ(matrix.get(1), 2);
    EXPECT_EQ(matrix.get(2), 3);
    EXPECT_THROW(matrix.get(-1), index_out_of_range);
    EXPECT_THROW(matrix.get(3), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_another){

    int items[] = {1, 2, 3, 4};
    ArraySequence<int> array(items, 3);
    DiagonalMatrix<ArraySequence, int> matrix(array, 3, 1);
    DiagonalMatrix<ArraySequence, int> mamatrix(matrix);

    EXPECT_EQ(mamatrix.get_diag_count(), 1);
    EXPECT_EQ(mamatrix.get_matrix_size(), 3);
    
    EXPECT_EQ(mamatrix.get(0), 1);
    EXPECT_EQ(mamatrix.get(1), 2);
    EXPECT_EQ(mamatrix.get(2), 3);
    EXPECT_THROW(mamatrix.get(-1), index_out_of_range);
    EXPECT_THROW(mamatrix.get(3), index_out_of_range);

}

TEST(TestDiagonalMatrix, check_methods){

    int items[] = {1, 2, 3};

    ArraySequence<int> seq(items, 3);
    DiagonalMatrix<ArraySequence, int> matrix(seq, 3, 1);

    matrix.set(0, 7);
    matrix.multiply_by_scalar(2);
    matrix.summary_with_scalar(1);

    EXPECT_EQ(matrix.get(0), 15);
    EXPECT_EQ(matrix.get(1), 5);
    EXPECT_EQ(matrix.get(2), 7);

    EXPECT_THROW(matrix.get(3), index_out_of_range);
    EXPECT_THROW(matrix.get(-1), index_out_of_range);

}