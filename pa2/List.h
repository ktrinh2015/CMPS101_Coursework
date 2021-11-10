// -------------------------------------------------------------------
// Kevin Trinh, kevatrin
// 2019 Summer CMPS101 PA2
// List.h
// Header file for List.c
// Contains function protypes for List ADT
// -------------------------------------------------------------------
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

// newList
// Creates a new ListObj 
List newList(void);

// frees and deallocates memory 
void freeList(List* pL);

// length
// Returns List length
int length(List L);

// index
// If cursor is defined, returns the index of the cursor element,
// otherwise return -1
int index(List L);

// front
// returns front element.
// Pre: index() > 0 
void* front(List L);

// back
// returns back element
void* back(List L);

// get
// returns element at cursor
void* get(List L);
/*
// equals
// Compares the integer sequece between the two List Objects.
int equals(List A, List B);
*/
// clear
// Clears List values
void clear(List L);

// moveFront
// moves cursor to front element
void moveFront(List L);

// moveBack
// moves cursor to back element
void moveBack(List L);

// movePrev
// Moves cursor one element towards head of List
void movePrev(List L);

// moveFront
// Moves cursor one element towards bakc of List
void moveNext(List L);

// prepend
// Inserts new element before front element;
void prepend(List L, void* data);

// append
// Inserts new element after back element
void append(List L, void* data);

// insertBefore
// Inserts new element before cursor
void insertBefore(List L, void* data);

// insertAfter
// Inserts new element after cursor
void insertAfter(List L, void* data);

// deleteFront
// Deletes front element in List
void deleteFront(List L);

// deleteBack
// Deletes back element in List
void deleteBack(List L);

// delete
// Deletes element at cursor
void delete(List L);

// printList
// prints L to file to out, formatted as a space-separated string.
void printList(FILE* out, List L);

// copyList
// Copies passed List Object into another List Object. 
// This function is independent of cursor position
List copyList(List L);
#endif
