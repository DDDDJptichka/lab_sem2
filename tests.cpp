#include <cstdio>
#include <iostream>

#include <complex>
#include <cmath>

#include <gtest/gtest.h>

#include "includes/Exception.h"
#include "includes/DynamicArray.h"
#include "includes/LinkedList.h"
#include "includes/ArraySequence.h"
#include "includes/ListSequence.h"
#include "includes/Sequence.h"
#include "includes/DiagonalMatrix.h"

#include "includes/LazyOperations.h"
#include "includes/Shaker.h"

#include "includes/Option.h"
#include "includes/Generator.h"

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
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);

    EXPECT_THROW(matrix.get(3, 3), index_out_of_range);
    EXPECT_THROW(matrix.get(-1, 3), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_list_sequence){

    int items[] = {1, 2, 3};

    ListSequence<int> list(items, 3);
    DiagonalMatrix<ListSequence, int> matrix(list, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);

    EXPECT_THROW(matrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(matrix.get(-1, 1), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_linked_list){

    int items[] = {1, 2, 3, 4};
    LinkedList<int> list(items, 3);

    DiagonalMatrix<LinkedList, int> matrix(list, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);
    EXPECT_THROW(matrix.get(-1, 1), index_out_of_range);
    EXPECT_THROW(matrix.get(3, 0), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_dynamic_array){

    int items[] = {1, 2, 3, 4};
    DynamicArray<int> array(items, 3);

    DiagonalMatrix<DynamicArray, int> matrix(array, 3, 1);

    EXPECT_EQ(matrix.get_diag_count(), 1);
    EXPECT_EQ(matrix.get_matrix_size(), 3);
    
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(1, 1), 2);
    EXPECT_EQ(matrix.get(2, 2), 3);
    EXPECT_THROW(matrix.get(-1, 0), index_out_of_range);
    EXPECT_THROW(matrix.get(3, 0), index_out_of_range);

}

TEST(TestDiagonalMatrix, create_from_another){

    int items[] = {1, 2, 3, 4};
    ArraySequence<int> array(items, 3);
    DiagonalMatrix<ArraySequence, int> matrix(array, 3, 1);
    DiagonalMatrix<ArraySequence, int> mamatrix(matrix);

    EXPECT_EQ(mamatrix.get_diag_count(), 1);
    EXPECT_EQ(mamatrix.get_matrix_size(), 3);
    
    EXPECT_EQ(mamatrix.get(0, 0), 1);
    EXPECT_EQ(mamatrix.get(1, 1), 2);
    EXPECT_EQ(mamatrix.get(2, 2), 3);
    EXPECT_THROW(mamatrix.get(-1, 0), index_out_of_range);
    EXPECT_THROW(mamatrix.get(3, 0), index_out_of_range);

}

TEST(TestDiagonalMatrix, check_methods){

    int items[] = {1, 2, 3, 4, 5, 6, 7};

    ArraySequence<int> seq(items, 7);
    DiagonalMatrix<ArraySequence, int> matrix(seq, 3, 1);
    DiagonalMatrix<ArraySequence, int> fuller(seq, 7, 3);
    DiagonalMatrix<ArraySequence, int> bigger(seq, 4, 1);

    matrix.set(0, 0, 7);
    matrix = matrix.multiply_by_scalar(2);
    matrix = matrix.summary_with_scalar(1);

    EXPECT_EQ(matrix.get(0, 2), 1);
    EXPECT_EQ(matrix.get(0, 0), 15);
    EXPECT_EQ(matrix.get(1, 1), 5);
    EXPECT_EQ(matrix.get(2, 2), 7);
    EXPECT_DOUBLE_EQ(matrix.frobenius_norm(), std::sqrt(305.0));

    ArraySequence<int> res(0);
    ArraySequence<int> curr(0);
    res.append(15)->append(1)->append(1)->append(1)->append(5)->append(1)->append(1)->append(1)->append(7);
    
    for (auto item : matrix){

        curr.append(item);

    }

    for (size_t i = 0; i < 9; ++i){

        EXPECT_EQ(res[i], curr[i]);

    }

    EXPECT_THROW(matrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(matrix.get(-1, 0), index_out_of_range);

    DiagonalMatrix<ArraySequence, double> mamatrix;
    mamatrix = matrix.summary_with_scalar(1.5);
    mamatrix = mamatrix.multiply_by_scalar(2.5);

    EXPECT_DOUBLE_EQ(mamatrix.get(0, 0), 41.25);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 1), 16.25);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 2), 21.25);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(2651.5625));

    auto bigger_double = bigger.multiply_by_scalar(1.0);
    auto fuller_double = fuller.multiply_by_scalar(1.0);

    EXPECT_THROW(mamatrix.summary_with_matrix(bigger_double), different_matrix_size);

    mamatrix = mamatrix.summary_with_matrix(mamatrix);

    EXPECT_DOUBLE_EQ(mamatrix.get(0, 0), 82.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 1), 32.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 2), 42.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(0, 1), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(0, 2), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 0), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 2), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 0), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 1), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(10606.25));
    EXPECT_THROW(mamatrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(mamatrix.get(-1, 0), index_out_of_range);

    mamatrix = mamatrix.summary_with_matrix(fuller_double);

    EXPECT_EQ(mamatrix.get_diag_count(), 5);
    EXPECT_EQ(mamatrix.get_matrix_size(), 3);
    EXPECT_DOUBLE_EQ(mamatrix.get(0, 0), 85.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 1), 36.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 2), 47.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(0, 1), 13.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 2), 14.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(1, 0), 18.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 1), 19.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(0, 2), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.get(2, 0), 12.5);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(12326.25));
    EXPECT_THROW(mamatrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(mamatrix.get(-1, 0), index_out_of_range);

    DiagonalMatrix<ArraySequence, int> mtrx(seq, 2, 1);

    auto ans = mtrx.get_inverse_matrix();

    EXPECT_DOUBLE_EQ(ans.get(0, 0), 1);
    EXPECT_DOUBLE_EQ(ans.get(1, 1), 1.0 / 2.0);
    EXPECT_DOUBLE_EQ(ans.get(1, 0), 0);
    EXPECT_DOUBLE_EQ(ans.get(0, 1), 0);

    ans = ans.get_inverse_matrix();

    EXPECT_DOUBLE_EQ(ans.get(0, 0), 1);
    EXPECT_DOUBLE_EQ(ans.get(1, 1), 2);
    EXPECT_DOUBLE_EQ(ans.get(1, 0), 0);
    EXPECT_DOUBLE_EQ(ans.get(0, 1), 0);

}

TEST(TestDiagonalMatrix, check_methods_for_complex){

    std::complex<int> items[] = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1}};
    std::complex<double> d_items[] = {{1.1, 1.1}, {2.2, 1.1}};

    ArraySequence<std::complex<int>> seq(items, 7);
    ListSequence<std::complex<double>> d_seq(d_items, 2);
    DiagonalMatrix<ArraySequence, std::complex<int>> matrix(seq, 3, 1);
    DiagonalMatrix<ArraySequence, std::complex<int>> fuller(seq, 7, 3);
    DiagonalMatrix<ArraySequence, std::complex<int>> bigger(seq, 4, 1);

    matrix.set(0, 0, std::complex<int>(7, 1));
    matrix = matrix.multiply_by_scalar(std::complex<int>(2, 0));
    matrix = matrix.summary_with_scalar(std::complex<int>(1, 0));

    EXPECT_EQ(matrix.get(0, 2).real(), 1);
    EXPECT_EQ(matrix.get(0, 2).imag(), 0);
    EXPECT_EQ(matrix.get(0, 0).real(), 15);
    EXPECT_EQ(matrix.get(0, 0).imag(), 2);
    EXPECT_EQ(matrix.get(1, 1).real(), 5);
    EXPECT_EQ(matrix.get(1, 1).imag(), 2);
    EXPECT_EQ(matrix.get(2, 2).real(), 7);
    EXPECT_EQ(matrix.get(2, 2).imag(), 2);
    EXPECT_DOUBLE_EQ(matrix.frobenius_norm(), std::sqrt(317.0));

    ArraySequence<std::complex<int>> res(0);
    ArraySequence<std::complex<int>> curr(0);
    res.append({15, 2})->append({1, 0})->append({1, 0})->append({1, 0})->append({5, 2})->append({1, 0})->append({1, 0})->append({1, 0})->append({7, 2});
    
    for (auto item : matrix){

        curr.append(item);

    }

    for (size_t i = 0; i < 9; ++i){

        EXPECT_EQ(res[i], curr[i]);

    }

    EXPECT_THROW(matrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(matrix.get(-1, 0), index_out_of_range);

    DiagonalMatrix<ArraySequence, std::complex<int>> mamatrix;

    mamatrix = matrix.summary_with_scalar(std::complex<int>(1, 1));
    mamatrix = mamatrix.multiply_by_scalar(std::complex<int>(2, 2));

    EXPECT_EQ(mamatrix.get(0, 0).real(), 26);
    EXPECT_EQ(mamatrix.get(0, 0).imag(), 38);
    EXPECT_EQ(mamatrix.get(1, 1).real(), 6);
    EXPECT_EQ(mamatrix.get(1, 1).imag(), 18);
    EXPECT_EQ(mamatrix.get(2, 2).real(), 10);
    EXPECT_EQ(mamatrix.get(2, 2).imag(), 22);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(3304.0));

    EXPECT_THROW(mamatrix.summary_with_matrix(bigger), different_matrix_size);
    
    mamatrix = mamatrix.summary_with_matrix(mamatrix);

    EXPECT_EQ(mamatrix.get(0, 0).real(), 52);
    EXPECT_EQ(mamatrix.get(0, 0).imag(), 76);
    EXPECT_EQ(mamatrix.get(1, 1).real(), 12);
    EXPECT_EQ(mamatrix.get(1, 1).imag(), 36);
    EXPECT_EQ(mamatrix.get(2, 2).real(), 20);
    EXPECT_EQ(mamatrix.get(2, 2).imag(), 44);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(13216.0));
    EXPECT_THROW(mamatrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(mamatrix.get(-1, 0), index_out_of_range);

    mamatrix = mamatrix.summary_with_matrix(fuller);

    EXPECT_EQ(mamatrix.get_diag_count(), 5);
    EXPECT_EQ(mamatrix.get_matrix_size(), 3);
    EXPECT_EQ(mamatrix.get(0, 0).real(), 55);
    EXPECT_EQ(mamatrix.get(0, 0).imag(), 77);
    EXPECT_EQ(mamatrix.get(1, 1).real(), 16);
    EXPECT_EQ(mamatrix.get(1, 1).imag(), 37);
    EXPECT_EQ(mamatrix.get(2, 2).real(), 25);
    EXPECT_EQ(mamatrix.get(2, 2).imag(), 45);
    EXPECT_EQ(mamatrix.get(0, 1).real(), 5);
    EXPECT_EQ(mamatrix.get(0, 1).imag(), 13);
    EXPECT_EQ(mamatrix.get(1, 2).real(), 6);
    EXPECT_EQ(mamatrix.get(1, 2).imag(), 13);
    EXPECT_EQ(mamatrix.get(1, 0).real(), 10);
    EXPECT_EQ(mamatrix.get(1, 0).imag(), 13);
    EXPECT_EQ(mamatrix.get(2, 1).real(), 11);
    EXPECT_EQ(mamatrix.get(2, 1).imag(), 13);
    EXPECT_DOUBLE_EQ(mamatrix.frobenius_norm(), std::sqrt(14507.0));
    EXPECT_THROW(mamatrix.get(3, 0), index_out_of_range);
    EXPECT_THROW(mamatrix.get(-1, 0), index_out_of_range);

    DiagonalMatrix<ArraySequence, std::complex<int>> mtrx(seq, 2, 1);
    DiagonalMatrix<ListSequence, std::complex<double>> d_mtrx(d_seq, 2, 1);

    auto ans = mtrx.get_inverse_matrix();

    EXPECT_DOUBLE_EQ(ans.get(0, 0).real(), 0.5);
    EXPECT_DOUBLE_EQ(ans.get(0, 0).imag(), -0.5);
    EXPECT_DOUBLE_EQ(ans.get(0, 1).real(), 0);
    EXPECT_DOUBLE_EQ(ans.get(0, 1).imag(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 0).real(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 0).imag(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 1).real(), 0.4);
    EXPECT_DOUBLE_EQ(ans.get(1, 1).imag(), -0.2);

    ans = ans.get_inverse_matrix();

    EXPECT_DOUBLE_EQ(ans.get(0, 0).real(), 1);
    EXPECT_DOUBLE_EQ(ans.get(0, 0).imag(), 1);
    EXPECT_DOUBLE_EQ(ans.get(0, 1).real(), 0);
    EXPECT_DOUBLE_EQ(ans.get(0, 1).imag(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 0).real(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 0).imag(), 0);
    EXPECT_DOUBLE_EQ(ans.get(1, 1).real(), 2);
    EXPECT_DOUBLE_EQ(ans.get(1, 1).imag(), 1);

    auto ressss = mtrx.summary_with_matrix(d_mtrx);

    EXPECT_DOUBLE_EQ(ressss.get(0, 0).real(), 2.1);
    EXPECT_DOUBLE_EQ(ressss.get(0, 0).imag(), 2.1);
    EXPECT_DOUBLE_EQ(ressss.get(0, 1).real(), 0);
    EXPECT_DOUBLE_EQ(ressss.get(0, 1).imag(), 0);
    EXPECT_DOUBLE_EQ(ressss.get(1, 0).real(), 0);
    EXPECT_DOUBLE_EQ(ressss.get(1, 0).imag(), 0);
    EXPECT_DOUBLE_EQ(ressss.get(1, 1).real(), 4.2);
    EXPECT_DOUBLE_EQ(ressss.get(1, 1).imag(), 2.1);

}

TEST(TestLazyOperations, lazy_map){

    int items[] = {1, 2, 3, 4, 5, 6, 7};
    ArraySequence<int> cocont(items, 7);

    DynamicArray<int> cont1(items, 3);
    LinkedList<int> cont2(items, 4);
    ArraySequence<int> cont3(items, 5);
    ListSequence<int> cont4(items, 6);
    DiagonalMatrix<ArraySequence, int> cont5(cocont, 7, 3);

    auto arr_squares = map(map(map(map(cont1, [](int a){return a * a;}), [](int a){return a;}), [](int a){return a - 10;}), [](int a){return a + 10;});
    auto list_squares = map(cont2, [](int a){return a * a;});
    auto arr_seq_squares = map(cont3, [](int a){return a * a;});
    auto list_seq_squares = map(cont4, [](int a){return a * a;});
    auto matrix_squares = map(cont5, [](int a){return a * a;});

    DynamicArray<int> expected(items, 3);

    for (auto &item : expected){

        item = item * item;

    }

    EXPECT_TRUE(std::equal(arr_squares.begin(), arr_squares.end(), expected.begin()));

    expected.append(16);
    EXPECT_TRUE(std::equal(list_squares.begin(), list_squares.end(), expected.begin()));

    expected.append(25);
    EXPECT_TRUE(std::equal(arr_seq_squares.begin(), arr_seq_squares.end(), expected.begin()));
    
    expected.append(36);
    EXPECT_TRUE(std::equal(list_seq_squares.begin(), list_seq_squares.end(), expected.begin()));

    expected.append(49);
    DiagonalMatrix<DynamicArray, int> matrix_expected(expected, 7, 3);
    EXPECT_TRUE(std::equal(matrix_squares.begin(), matrix_squares.end(), matrix_expected.begin()));

}

TEST(TestLazyOperations, lazy_where_reduce_composition){

    int items[] = {1, 2, 3, 4, 5, 6, 7};
    ArraySequence<int> cocont(items, 1);
    cocont.append(3)->append(5)->append(7);

    DynamicArray<int> cont1(items, 3);
    LinkedList<int> cont2(items, 4);
    ArraySequence<int> cont3(items, 5);
    ListSequence<int> cont4(items, 6);
    DiagonalMatrix<ArraySequence, int> cont5(cocont, 4, 1);

    auto arr_squares = where(cont1, [](int a){return (a % 2 == 1);});
    auto list_squares = where(cont2, [](int a){return (a % 2 == 1);});
    auto arr_seq_squares = where(cont3, [](int a){return (a % 2 == 1);});
    auto list_seq_squares = where(cont4, [](int a){return (a % 2 == 1);});
    auto matrix_squares = where(cont5, [](int a){return (a % 2 == 1);});

    DynamicArray<int> expected(items, 1);

    expected.append(3);
    EXPECT_TRUE(std::equal(arr_squares.begin(), arr_squares.end(), expected.begin()));

    EXPECT_TRUE(std::equal(list_squares.begin(), list_squares.end(), expected.begin()));

    expected.append(5);
    EXPECT_TRUE(std::equal(arr_seq_squares.begin(), arr_seq_squares.end(), expected.begin()));
    
    EXPECT_TRUE(std::equal(list_seq_squares.begin(), list_seq_squares.end(), expected.begin()));

    expected.append(7);
    EXPECT_TRUE(std::equal(matrix_squares.begin(), matrix_squares.end(), expected.begin()));

    auto res_1 = reduce(arr_squares, [](int a, int c){return a * a + c;}, 2);
    auto res_2 = reduce(list_squares, [](int a, int c){return a * a + c;}, 2);
    auto res_3 = reduce(arr_seq_squares, [](int a, int c){return a * a + c;}, 2);
    auto res_4 = reduce(list_seq_squares, [](int a, int c){return a * a + c;}, 2);
    auto res_5 = reduce(matrix_squares, [](int a, int c){return a * a + c;}, 2);

    EXPECT_EQ(res_1, (1 * 1 + 2) * (1 * 1 + 2) + 3);
    EXPECT_EQ(res_2, ((1 * 1 + 2) * (1 * 1 + 2) + 3));
    EXPECT_EQ(res_3, ((1 * 1 + 2) * (1 * 1 + 2) + 3) * ((1 * 1 + 2) * (1 * 1 + 2) + 3) + 5);
    EXPECT_EQ(res_4, ((1 * 1 + 2) * (1 * 1 + 2) + 3) * ((1 * 1 + 2) * (1 * 1 + 2) + 3) + 5);
    EXPECT_EQ(res_5, (((1 * 1 + 2) * (1 * 1 + 2) + 3) * ((1 * 1 + 2) * (1 * 1 + 2) + 3) + 5) * (((1 * 1 + 2) * (1 * 1 + 2) + 3) * ((1 * 1 + 2) * (1 * 1 + 2) + 3) + 5) + 7);

    DiagonalMatrix<ArraySequence, int> cont6(cocont, 2, 1);

    auto res_6 = reduce(where(map(cont1, [](int a){return a + 1;}), [](int a){return a % 2 == 1;}), [](int a, int c){return a * a + c;}, 2);
    auto res_7 = reduce(where(map(cont2, [](int a){return a + 1;}), [](int a){return a % 2 == 1;}), [](int a, int c){return a * a + c;}, 2);
    auto res_8 = reduce(where(map(cont3, [](int a){return a + 1;}), [](int a){return a % 2 == 1;}), [](int a, int c){return a * a + c;}, 2);
    auto res_9 = reduce(where(map(cont4, [](int a){return a + 1;}), [](int a){return a % 2 == 1;}), [](int a, int c){return a * a + c;}, 2);
    auto res_10 = reduce(where(map(cont6, [](auto a){return a + 1;}), [](auto a){return a % 2 == 1;}), [](auto a, auto c){return a * a + c;}, 2);

    EXPECT_EQ(res_6, 3 * 3 + 2);
    EXPECT_EQ(res_7, ((3 * 3 + 2) * (3 * 3 + 2) + 5));
    EXPECT_EQ(res_8, ((3 * 3 + 2) * (3 * 3 + 2) + 5));
    EXPECT_EQ(res_9, ((3 * 3 + 2) * (3 * 3 + 2) + 5) * ((3 * 3 + 2) * (3 * 3 + 2) + 5) + 7);
    EXPECT_EQ(res_10, (1 * 1 + 2) * (1 * 1 + 2) + 1);

}

TEST(TestDiagonalMatrix, check_convert){

    int items[] = {1, 2, 3, 4, 5, 6, 7};

    ArraySequence<int> seq(items, 7);
    DiagonalMatrix<ArraySequence, int> matrix(seq, 3, 1);
    DiagonalMatrix<ArraySequence, int> matrix2(seq, 3, 1);
    ArraySequence<int> res(0);
    ArraySequence<int> res2(0);
    res.append(1)->append(0)->append(-10)->append(0)->append(2)->append(0)->append(10)->append(0)->append(3);

    matrix.set(2, 0, 10);
    matrix.set(0, 2, -10);

    EXPECT_TRUE(std::equal(matrix.begin(), matrix.end(), res.begin()));

    matrix = matrix.summary_with_matrix(matrix2);
    res2.append(2)->append(0)->append(-10)->append(0)->append(4)->append(0)->append(10)->append(0)->append(6);

    EXPECT_TRUE(std::equal(matrix.begin(), matrix.end(), res2.begin()));

}

TEST(TestDiagonalMatrix, check_shaker){

    int items[] = {1, 2, 3, 4, 5, 6, 7};

    ArraySequence<int> seq(items, 7);
    ArraySequence<int> res(items, 7);
    shaker(seq, 2);

    EXPECT_TRUE(!(std::equal(seq.begin(), seq.end(), res.begin())));
    
    std::sort(seq.begin(), seq.end());

    EXPECT_TRUE(std::equal(seq.begin(), seq.end(), res.begin()));

    // for (size_t i = 0; i < 10000; ++i){

    //     shaker(seq, 2);

    //     EXPECT_TRUE(!(std::equal(seq.begin(), seq.end(), res.begin())));
    //     std::cout << "  " << i;

    // }
}

TEST(TestOption, create_empty){

    Option<int> opt;

    EXPECT_EQ(opt.has_value(), false);
    EXPECT_THROW(opt.value(), empty_option);

}

TEST(TestOption, create_not_empty){

    Option<int> opt(322);

    EXPECT_EQ(opt.has_value(), true);
    EXPECT_EQ(opt.value(), 322);

}

TEST(TestOption, create_from_another){

    Option<int> opt(322);
    Option<int> res(opt);

    EXPECT_EQ(res.has_value(), true);
    EXPECT_EQ(res.value(), 322);

    opt.value() = 11;
    res.value() = 12;

    EXPECT_EQ(res.has_value(), true);
    EXPECT_EQ(res.value(), 12);
    EXPECT_EQ(opt.has_value(), true);
    EXPECT_EQ(opt.value(), 11);

}

TEST(TestOption, check_operators){

    Option<int> opt(322);
    Option<int> opt2;

    opt2 = opt;

    EXPECT_EQ(opt2.has_value(), true);
    EXPECT_EQ(opt2.value(), 322);

    opt.value() = 11;
    opt2.value() = 12;

    EXPECT_EQ(opt2.has_value(), true);
    EXPECT_EQ(opt2.value(), 12);
    EXPECT_EQ(opt.has_value(), true);
    EXPECT_EQ(opt.value(), 11);

    opt2.value() = opt.value();

    EXPECT_TRUE(opt == opt2);

}

TEST(TestOption, check_reset){

    Option<int> opt(322);

    EXPECT_EQ(opt.has_value(), true);
    EXPECT_EQ(opt.value(), 322);

    opt.reset();

    EXPECT_EQ(opt.has_value(), false);
    EXPECT_THROW(opt.value(), empty_option);

}

TEST(TestGenerator, create_empty){

    Generator<int> gen;

    EXPECT_EQ(gen.get_position(), 0);
    EXPECT_FALSE(gen.has_next());
    EXPECT_EQ(gen.try_get_next(), Option<int>());
    EXPECT_TRUE(gen.begin() == gen.end());
    EXPECT_THROW(gen.get_next(), index_out_of_range);

}

TEST(TestGenerator, create_not_empty_and_check_NOTiterable){

    Generator<int> gen([](size_t i){return i * i;});

    int expected[] = {0, 1, 4, 9};

    EXPECT_THROW(gen.begin(), not_usable);
    EXPECT_THROW(gen.end(), not_usable);
    EXPECT_EQ(gen.get_position(), 0);

    for (size_t i = 0; i < 4; ++i){

        EXPECT_EQ(gen.try_get_next().value(), expected[i]);

    }

    EXPECT_TRUE(gen.has_next());
    EXPECT_EQ(gen.get_position(), 4);
    EXPECT_EQ(gen.get_next(), 16);

}

TEST(TestGenerator, create_not_empty_and_check_iterable){

    Generator<int> gen([](size_t i){return i * i;}, 4);

    int expected[] = {0, 1, 4, 9};
    size_t index = 0;

    for (auto val : gen){

        EXPECT_EQ(val, expected[index]);
        ++index;

    }

    index = 0;

    EXPECT_EQ(gen.get_position(), 0);

    while (gen.has_next()){

        EXPECT_EQ(gen.try_get_next().value(), expected[index]);
        ++index;

    }

}