/**************************************************************
 * Kevin Trinh
 * Summer CMPS 101 2019
 * kevatrin
 * List.c
 * Contains List manipulation routines
***************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

 typedef struct NodeObj{
 	int data;
        struct NodeObj* next;
        struct NodeObj* prev; 
            
 }NodeObj;
 typedef NodeObj* Node;

 typedef struct ListObj{
 	Node front;
        Node back;
        int length; 
        int index;
 } ListObj; 
 typedef ListObj* List;

 Node newNode(int data){
 Node N = calloc(sizeof(Node),sizeof(Node));
 N->data = data;
 N->next = NULL;
 N->prev = NULL;
 return N; 
 }

// newList
 List newList(void){
 List L;
 L = calloc(1,sizeof(ListObj));
 L->front = NULL;
 L->back = NULL; 
 L->length = 0;
 L->index = -1;
 return L;   
 }

 // freeList
 void freeList(List* pL){
 List L = *pL;
    if(L->front != NULL){
    clear(*pL);
    }
    
    free(*pL);
    pL = NULL;
 } 

 //length
 int length(List L){
 return L->length;
 }
 
 //index
 int index(List L){   
 return L->index;
 }

 // front
 // Pre: L->length > 0
 int front(List L){
 Node temp = L->front;
    if(L->length <= 0){
        fprintf(stderr,"List Error: Cannot call front on empty List\n");
        exit(1);
    }
 return temp->data;
 }
  
 // back
 // Pre: L->length > 0
 int back(List L){
 Node temp = L->back;
    if(L->length <= 0){
       fprintf(stderr,"List Error: Cannot call back on empty List\n");
       exit(1);
    }
 return temp->data;
 }
 
 // get
 // Pre: L->length > 0, L->index >= 0
 int get(List L){
 Node temp = L->front;
 //printf("This is L.index: %d\n", L->index);
    if(L->length <= 0){
       return -1; 
    }
    if(L->index < 0){
       return -1;
    }
    for(int i =0; i < L->index; i++){
        temp = temp->next;
    } 
 return temp->data;
 }

 // equals
 int equals(List A, List B){
 Node N = A->front;
 Node M = B->front;
   if(A->length == 0 || B->length == 0){
      return 0; 
   }
   if(A->length != B->length){
      return 0;
   }
   while(N != NULL){
       if(N->data != M->data){
          return 0;
       }
   N = N->next;
   M = M->next;
   }
 return 1;
 }

 // clear
 void clear(List L){
 Node current = L->front;
 Node temp; 
    if(L->front == NULL){
       return;
    } 
    else if(current->next == NULL){ 
       free(L->front);
       L->front = NULL;
       L->back = NULL;
       current = NULL;
    }
    else{
       while(current != NULL){
          temp = current;
          current->prev = NULL;
          current = current->next;
          free(temp);
          temp->prev = NULL;
          temp->next = NULL;
          
       }
    }
 L->length = 0;
 L->index = -1;
 }

 // moveFront{
 void moveFront(List L){
     if(L->length <= 0){
        return;
     }
     L->index = 0;
 }
 
 // moveBack
 void moveBack(List L){
    if(L->length <= 0){
       return;
    }
    L->index = L->length-1;
 }
 
 // movePrev
 void movePrev(List L){
    if(L->length <= 0){
       return;   
   } 
    if(L->index == -1){
       return;
    }
    L->index--;
 } 

 // moveNext
 void moveNext(List L){
 if(L->length <= 0){
       return;   
    }
    if(L->index == -1){
       return;
    }
    if(L->index == L->length -1){
       L->index= -1;
       return;
    }
    L->index++;
 }
 
 // prepend
 void prepend(List L, int data){
 Node insert = newNode(data);
    if(L->length == 0){
        L->front = insert;
        L->back = insert;
        L->length++;
        return;
    }
    if(L->length == 1){
       L->front->prev = insert; 
       insert->next = L->front;
       L->front = insert;  
       L->back = L->front->next; 
       L->length++;
          if(L->index == 0){
             L->index++;
          }
    return;
    }
 L->front->prev = insert;
 insert->next = L->front;
 L->front = insert;
    if(L->index >= 0){
       L->index++;
    }
 L->length++;
 }

 // append
 void append(List L, int data){
 Node insert = newNode(data);
    if(L->length == 0){
        L->front = insert;
        L->back = insert;
        L->length++;
        return;
    }
    if(L->length == 1){
       L->back->next = insert;
       insert->prev = L->back;
       L->back = insert;   
       L->length++;
          if(L->index == 0){
             L->index++;
          }
    return;
    }
 L->back->next = insert;
 insert->prev = L->back; 
 L->back = insert;
 L->length++; 
 }

 // insertBefore
 void insertBefore(List L, int data){
 Node temp = L->front;
 Node insert = newNode(data);
 Node prev = NULL;
    if(L->length == 0){
       fprintf(stderr,"List Error: Cannot call insertBefore on empty List\n");
       exit(1);
    }
    if(L->index < 0){
       fprintf(stderr,"List Error: Cannot call insertBefore with undefined index\n");
       exit(1);
    }
    if(L->index == 0){
       L->front->prev = insert;
       insert->next = L->front;
       insert->prev = NULL;
       L->front = insert;   
    }
    else{
       for(int i = 0; i < L->index; i++){
          temp = temp->next;
       }
    prev = temp->prev;
    temp->prev = insert;
    prev->next = insert;
    insert->prev = prev;
    insert->next = temp;
    }
 L->length++;
 L->index++;
 }
 
 // insertAfter
 void insertAfter(List L, int data){
 Node temp = L->front;
 Node insert = newNode(data);
 Node next = NULL;
    if(L->length < 0){
       fprintf(stderr,"List Error: Cannot call insertAfter on empty List\n");
       exit(1);
    }
    if(L->index < 0){
       fprintf(stderr,"List Error: Cannot call insertAfter on undefined index\n");
       exit(1);
    } 
    if(L->index == L->length-1){
       L->back->next = insert;
       insert->prev = L->back;
       insert->next = NULL;
       L->back = insert;    
    }
    else{
       for(int i = 0; i < L->index; i++){
          temp = temp->next;
       }
    next = temp->next;
    temp->next = insert;
    next->prev = insert;
    insert->prev = temp;
    insert->next = next;
    }
 L->length++;
 } 

 // deleteFront
 void deleteFront(List L){
 Node temp = L->front;
    if(L->length == 0){
       fprintf(stderr,"List Error: Cannot call deleteFront on empty List\n");
       exit(1);
    }
    if(L->length == 1){  
       free(L->front);
       L->front = NULL;
       L->back = NULL;
       L->length = 0;
       L->index = -1;
       return;
    }
    if(L->length == 2){
       L->front->next = L->front;
       L->front->next = NULL;
       L->front = L->back;
       free(temp);
       temp = NULL;
       if(L->index == 0){
          L->index = -1;
       }
       else{
          L->index--;
       }
    L->length--;
    return;
    } 
 L->front = L->front->next;
 L->front->prev = NULL;
 free(temp);
 temp = NULL;
    if(L->index == 0){
       L->index = -1;
    }   
    else{
       L->index--;
    }
 L->length--;
 }
 
 // deleteBack
 void deleteBack(List L){
 Node temp = L->back;
    if(L->length == 0){
       fprintf(stderr,"List Error: Cannot call deleteBack on empty List\n");
       exit(1);
    }
    if(L->length == 1){
       free(L->front);
       L->front = NULL;
       L->back = NULL;
       L->length = 0;
       L->index = -1;
       return;
    }
    if(L->length == 2){
       L->back->prev = L->back;
       L->back->prev = NULL;
       L->front->next = NULL;
       L->back = L->front;
       free(temp);
       temp = NULL;
       if(L->index == L->length-1){
          L->index =-1;
       }
       L->length--;
       return;
    }
 L->back = L->back->prev;
 L->back->next = NULL;
 free(temp);
 temp = NULL;
    if(L->index == L->length -1){
       L->index = -1;
    }
 L->length--;
 }

 // delete
 void delete(List L){
 Node temp = L->front;
 Node next;
 Node prev;
    if(L->length == 0){
       fprintf(stderr,"List Error: Cannot call delete on empty List\n");
       exit(1);
    }
    if(L->index == 0){
       if(L->length == 1){
          free(L->front);
          L->front = NULL;
          L->back = NULL;
          L->length = 0;
          L->index = -1;
          return;
       } 
       if(L->length == 2){
          L->front->next = L->front;
          L->front->next = NULL;
          L->front = L->back;
          free(temp);
          temp = NULL;
          L->length--;
          L->index = -1;
          return;
       }
    L->front = L->front->next; 
    L->front->prev = NULL;
    free(temp);
    temp = NULL;
    L->length--;
    return;
    }
    if(L->index == L->length -1){
    temp = L->back;
       if(L->length == 2){
          L->back = L->back->prev;
          L->front = L->back;
          free(temp); 
          temp = NULL;
          L->length--;
          L->index = -1;
	  return;   
       }
    L->back = L->back->prev;
    L->back->next = NULL;
    L->length--;
    L->index =-1;
    return;
    }
    for(int i = 0; i < L->index; i++){
       temp = temp->next;
    }
 prev = temp->prev;
 next = temp->next;
 prev->next = next;
 next->prev = prev;
 free(temp);
 temp = NULL;
 L->length--;
 L->index = -1;
 }

 //printList
 void printList(FILE* out, List L){
    Node temp = NULL;
    if(out == NULL){
       fprintf(stderr,"List Error: Cannot pass NULL out file as argument\n");
       exit(1);
    }
    
    for(temp = L->front; temp != NULL; temp = temp->next){
       fprintf(out, "%d ", temp->data);
    }
 fprintf(out,"\n");
 }

 // copyList
 List copyList(List L){
 List copy = newList();
// Node temp = L->front;
    if(L->length == 0){
       return copy;      
    }
 Node temp = L->front;
    while(temp != NULL){
       append(copy,temp->data);
       temp = temp->next;   
    }
 copy->length = L->length;
 copy->index = -1;
 return copy;
 }


