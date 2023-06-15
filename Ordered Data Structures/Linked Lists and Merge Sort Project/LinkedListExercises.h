/**
 * @file LinkedListExercises.h
 * University of Illinois CS 400, MOOC 2, Week 1: Linked List
 * Spring 2019
 *                        STUDENT STARTER FILE
 *
 * @author Eric Huber - University of Illinois staff
 *
 **/

/********************************************************************
  Week 1: Linked List and Merge Sort Exercises

  There are two exercises in this file. Please read the code comments
  below and see the provided instructions PDF before you begin. The
  other provided code files in the starter zip also contain important
  comments and hints about how to approach this.

  This is the only file you can edit for the sake of grading! You can
  edit the other provided starter files for testing purposes, but the
  autograder will assume that this is the only file that has been edited
  by you, and the others will be replaced with the original intended
  versions at grading time.
 ********************************************************************/

// Prevent the header from being included more than once per cpp file
#pragma once

// It's good to put system headers first, so that if your own libraries
// cause conflicts, the compiler will most likely identify the problem
// as being in your own source code files, where it arises later.
#include <iostream>
#include <string>

#include "LinkedList.h"

/********************************************************************
  Exercise 1: insertOrdered

  You can use "make test" followed by "./test" to check the correctness
  of your implementation, and then you can use "./test [bench]" to run
  some interesting benchmarks on the speed of your code.
 ********************************************************************/

template <typename T> void LinkedList<T>::insertOrdered(const T &newData) {
  //      *****************************************************
  //                           EXERCISE 1
  //    TODO: Your work here! You should edit this function body!
  //      *****************************************************
  // Hints:
  // Make your new node on the heap and then find where it needs to
  // go in the list. A good way to do this is by considering special
  // base cases first, then walk the list from front to back and find
  // the earliest position where you should insert the new node.
  Node *newNode = new Node(newData);
  if (!head_) {
    head_ = newNode;
    tail_ = newNode;
    ++size_;
    return;
  }
  Node *curr = head_;
  if (curr->data >= newData) {
    newNode->next = head_;
    newNode->next->prev = newNode;
    head_ = newNode;
    ++size_;
    return;
  } else {
    do {
      if (!curr->next) {
        newNode->prev = curr;
        curr->next = newNode;
        tail_ = newNode;
        ++size_;
        return;
      }
      curr = curr->next;
    } while (curr->data < newData);
  }

  // When you insert the node, make sure to update any and all pointers
  // between it and adjacent nodes accordingly (next and prev pointers).
  // You may also need to update the head_ and tail_ pointers in some
  // cases. Also update the size_ variable of the list.
  newNode->next = curr;
  newNode->prev = curr->prev;
  curr->prev = newNode;
  newNode->prev->next = newNode;
  ++size_;

  // There are explicit examples of how to do all those things in the
  // other provided code for this project!

  // More hints:
  // First, practice your technique for traversing the list from front
  // to back. You can see examples of several ways to do this throughout
  // the provided code for this project. We recommend that you try using
  // a temporary pointer that you update to track your position as you
  // traverse from node to node.

  // Consider all the cases that can happen when you're trying to insert
  // the new node. Is the list currently empty? Does the new node go
  // at the beginning? Does it go somewhere in the middle? Does it go
  // at the end? Remember that this is a doubly-linked list, so there
  // may be prev and next pointers to adjust on both sides of the node
  // that you insert.

  // Be careful to make your conditional cases mutually exclusive when
  // necessary. Are you using "else" where you should?

  // Don't dereference a null pointer, ever! Always make sure the logic
  // checks for that before dereferencing. This is the most common cause
  // of crashes. The test program will show you which test cases are
  // causing you issues with that. A common issue is that when students
  // traverse an empty list or when they traverse to the end of the list,
  // they don't handle the null pointer at the tail properly. Be careful
  // to update all next, prev, head_, and tail_ pointers as needed on your
  // new node or on those existing nodes that are adjacent to the new node.
}

/********************************************************************
  Exercise 2: Linear-time Merge

  A correct implementation of this function has O(n) time complexity
  for a list of length n. That is, in the worst case, you would
  traverse each element of the list some constant number of times.

  Important notes for getting the correct running time:
  1. Since both lists being merged are already sorted themselves, there
     is a way to merge them together into a single sorted list in a single
     traversal pass down the lists. This can run in O(n) time.
  2. You SHOULD NOT call any sorting function in your merge function.
  3. You SHOULD NOT call the insertOrdered function in merge. That would
     result in a very slow running time. (The insertOrdered function was
     part of the insertion sort exercise. It has nothing to do with merge
     or merge sort.)
 ********************************************************************/

template <typename T>
LinkedList<T> LinkedList<T>::merge(const LinkedList<T> &other) const {

  // You can't edit the original instance of LinkedList that is calling
  // merge because the function is marked const, and the "other" input
  // list is also marked const. However, here we'll make some convenient
  // "working copies" of the two lists: "*this" refers to the current
  // list object instance that is calling the merge member function, and
  // "other" refers to the list that was passed as an argument:
  // LinkedList<T> left = *this;
  // LinkedList<T> right = other;
  // So if this function was called as "A.merge(B)", then now, "left"
  // is a temporary copy of the "A" and "right" is a temporary copy
  // of the "B".

  // We will also create an empty list called "merged" where we can build
  // the final result we want. This is what we will return at the end of
  // the function.
  LinkedList<T> merged;
  //      *****************************************************
  //                           EXERCISE 2
  //    TODO: Your work here! You should edit this function body!
  //      *****************************************************
  // Hints:
  // 1. Assuming that the left and right lists are already sorted, remember
  //    that the smallest items are already available at the front. You can
  //    access them immediately.
  Node *leftptr = head_;
  Node *rightptr = other.head_;

  // 2. Think of which item needs to be placed first in the merged list.
  //    Then think about what item should be placed second. You need to
  //    think carefully about which list to take from next after you take
  //    each single item.
  // 3. You can do this while walking down the left and right lists exactly
  //    once. Do not loop over the lists multiple times. If you are doing
  //    that, your implementation is probably already running in O(n^2)
  //    time or worse, and not O(n).
  // 4. Remember, DO NOT try to use insertOrdered here. That would be
  //    very slow.
  while (leftptr && rightptr) {
    if (leftptr->data < rightptr->data) {
      merged.pushBack(leftptr->data);
      leftptr = leftptr->next;
    } else {
      merged.pushBack(rightptr->data);
      rightptr = rightptr->next;
    }
  }

  while (leftptr) {
    merged.pushBack(leftptr->data);
    leftptr = leftptr->next;
  }
  while (rightptr) {
    merged.pushBack(rightptr->data);
    rightptr = rightptr->next;
  }

  // We return the merged list by value here. It may be copied out of the
  // function, but usually the compiler will optimize this to automatically
  // create it directly in the correct memory space outside without copying.
  // Don't worry about the speed of that right now. (By the way, did you
  // notice that all of our nodes are created on the heap? The part of the
  // list that we pass back is really small; it just contains two pointers
  // and an int.)
  merged.size_ = size_ + other.size_;
  return merged;
}
