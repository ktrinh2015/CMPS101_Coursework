// --------------------------------------------------------------------------
// Kevin Trinh, kevatrin
// 2019 Summer CMPS101 PA2
// Matrix.c
// Contains Matrix ADT mainpulation routines
// --------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

 typedef struct EntryObj{
 int col;
 double  val;
 }EntryObj;
 typedef EntryObj* Entry;

 typedef struct MatrixObj{
 int nnz;
 List* matrix;
 }MatrixObj;
 typedef struct MatrixObj* Matrix;

Entry newEntry(int column, double value){
    Entry E = malloc(sizeof(Entry));
    E->col = column;
    E->val = value;
    return E;
 }

 int equalsEntry(Entry E, Entry x){
    int val;
    val = (E->val == x->val);
    return val;
 }
 
 void printEntry(FILE* out, Entry E){
	if(out == NULL){
	   fprintf(stderr, "Entry Error: Cannot pass NULL FILE\n");
	   exit(1);
	}
    fprintf(out,"(%d),(%.1f) ", E->col, E->val);
 }

 // newMatrix
 // Constructor
 // Returns a reference to a new nXn Matrix object in the zero state
 // Pre: n>=1
 Matrix newMatrix(int n){
    if(n<1){
	   fprintf(stderr, "Matrix Error: Must create matrix with n greater than 1\n");
	exit(1);
	}
 Matrix M = malloc(sizeof(MatrixObj*));
 M->matrix = malloc(sizeof(List)*(n+1));
 M->nnz = 0;
    for(int i = 0; i < n+1; i++){
       M->matrix[i] = newList();
    } 
 return M;
 }

 //freeMatrix()
 //Frees the heap memory asociated with *pM, sets *pM to NULL
 void freeMatrix(Matrix *pM){
   Matrix M = *pM;
   if(M != NULL){
      makeZero(M);
   }  
   M->nnz = 0;
   free(*pM);
 } 


 // size()
 // Returns the size of square Matrix M
 int size(Matrix M){
    return sizeof(M->matrix)-1;   
 }

 // NNZ
 // Returns the number of non-zero entries in this Matrix
 int NNZ(Matrix M){
    return M->nnz;
 }

 // equals
 // Returns true (1) if Matrices A and B are equal, false(0) otherwise
 int equals (Matrix A, Matrix B){
    int val = 0;
    if(size(A) != size(B))
       return val;
    if(A->nnz != B->nnz)
       return val;

    Entry current = NULL;
    Entry temp = NULL;

       for(int i = 1; i < size(A)+1; i++){
          if(length(A->matrix[i]) != 0 && length(B->matrix[i]) != 0){
             moveFront(A->matrix[i]);
             moveFront(B->matrix[i]);
                if(length(A->matrix[i]) != length(B->matrix[i])){
                   return val;
                }
             while(index(A->matrix[i]) != -1 && index(B->matrix[i]) != -1){
                current = (Entry)get(A->matrix[i]); 
                temp = (Entry)get(B->matrix[i]);
                   if(!(equalsEntry(current, temp))){
                      return val;
                   }
                moveNext(A->matrix[i]);
                moveNext(B->matrix[i]);
             }
          }
       }
 val = 1;
 return val;
 }

 // Manipulation Routines

 // makeZero()
 // Re-sets this M to the zero Matrix
 void makeZero(Matrix M){
    for (int i = 0 ; i < size(M); i++){
       clear(M->matrix[i]);
    }
 M->nnz = 0;
 }

 // changeEntry 
 // Changes the ith row, jth column of M to the value x.
 // pre: 1<=i<=size(M), 1<=j<=size(M)
 void changeEntry(Matrix M, int i, int j, double x){
 Entry temp = NULL;
 Entry insert = NULL;
    if(i <= 0){
       fprintf(stderr,"Matrix Error: Cannot have row value less than 1\n");
       exit(1);
    }
    if(i > size(M)){
       fprintf(stderr,"Matrix Error: Cannot pass row value greater than Matrix size\n");
       exit(1);
    }
    if(j <= 0){
       fprintf(stderr,"Matrix Error: Cannot pass column value less than 1\n");
       exit(1);
    }
    if(j > size(M)){
       fprintf(stderr,"Matrix Error: Cannot pass column value greater than Matrix size\n");
       exit(1);
    }
 
    if(length(M->matrix[i]) == 0){
       if(x==0){
          return;
       }
       else{
          insert = newEntry(j,x);
          append(M->matrix[i], insert);
          M->nnz++; 
       }
    }
    else{
       moveFront(M->matrix[i]);
       while(index(M->matrix[i]) != -1){
          temp = (Entry)get(M->matrix[i]);
             if(temp->col == j){
                if(x == 0){
                   delete(M->matrix[i]);
                   M->nnz--;
                   return;
                }
                else{
                   temp->val = x;
                   return;
                }
             }
             else if(j < temp->col){
                if(x == 0){
                   return; 
                }
                else{
                   insert = newEntry(j,x);
                   insertBefore(M->matrix[i],insert);
                   M->nnz++;
                   return;
                }
             }
             else if(back(M->matrix[i]) == get(M->matrix[i])){// check this out  
                if(x == 0){
                   return;
                }
                else{
                   insert = newEntry(j,x);
                   append(M->matrix[i],insert);
                   M->nnz++;
                   return;
                }
             }      
       moveNext(M->matrix[i]);
       }
    }
 }

 // copy()
 // Returns a reference to a new Matrix object having the same entries as A
 Matrix copy(Matrix A){
 Matrix newCopy = newMatrix(size(A));
 Entry temp = NULL;
 
   for(int i = 1; i < size(A); i++){
      if(length(A->matrix[i]) != 0){
         moveFront(newCopy->matrix[i]);
            for(int k = 0; k < length(newCopy->matrix[i]); k++){
            temp = (Entry)get(A->matrix[i]);
            changeEntry(newCopy,i,temp->col,temp->val);
            moveNext(A->matrix[i]);
         }
      }
   } 
 return newCopy;
 }

 // transpose()
 // Returns a reference to a new Matrix object having the same entries as A
 Matrix transpose(Matrix A){
 Matrix B = NULL;
 Entry temp = NULL;
 int k = 0;
    if(A->matrix == NULL){
       fprintf(stderr,"Matrix Error: Cannot call on transpose on NULL Matrix\n");
       exit(1);
    } 
    if(A->nnz == 0){
       B = newMatrix(size(A));
       return B;
    }
 B = newMatrix(size(A));
    for(int i = 1; i < size(A)+1; i++){
       if(length(A->matrix[i]) != 0){
          moveFront(A->matrix[i]);
          while(k != length(A->matrix[i]) && index(A->matrix[i]) != -1){
             temp = (Entry)get(A->matrix[i]);
             changeEntry(B,temp->col, i, temp->val);
             moveNext(A->matrix[i]);
             k++;
          }
       k = 0;
       }
    }
 return B;
 }

 // scalarMult()
 // Returns a reference to a new Matrix object representing xA
 Matrix scalarMult(double x, Matrix A){
 Matrix M = newMatrix(size(A));
 Entry temp = NULL;
    for(int i = 1; i < size(A)+1; i++){
       if(length(A->matrix[i]) != 0){
          moveFront(A->matrix[i]);
             while(index(A->matrix[i]) != -1){
                temp = (Entry)get(A->matrix[i]);
                changeEntry(M,i,temp->col,(temp->val)*x);
                moveNext(A->matrix[i]);
             }
       }
    } 
 return M;
 }

 // sum
 // Returns a reference to a new Matrix object representing A+B
 // Pre: size(A) == size(B)
 Matrix sum(Matrix A, Matrix B){
 Matrix M = NULL;
 List resultAdd = NULL;
 Entry temp = NULL;
    if(size(A) != size(B)){
       fprintf(stderr,"Matrix Error: Must pass matrices with same dimensions\n");
       exit(1);
    }
 M = newMatrix(size(A));
    for(int i = 1; i < size(A)+1; i++){
       resultAdd = listAdd(A->matrix[i], B->matrix[i]);
          if(length(resultAdd) != 0){
             moveFront(resultAdd);
                while(index(resultAdd) != -1){
                   temp = (Entry)get(resultAdd);
                   changeEntry(M,i,temp->col,temp->val);
                   moveNext(resultAdd);
                }
          } 
    }
 return M;
 }
   
 // diff
 // Returns a reference to a new Matrix object representing A-B
 Matrix diff(Matrix A, Matrix B){
 Matrix M = NULL;
 List resultSub = NULL;
 Entry temp = NULL;
    if(size(A) != size(B)){
       fprintf(stderr,"Matrix Error: Must pass matrices with same dimensions\n");
       exit(1);
    } 
 M = newMatrix(size(A));
    for(int i = 1; i < size(A)+1; i++){
       resultSub = listSub(A->matrix[i], B->matrix[i]);
          if(length(resultSub) != 0){
             moveFront(resultSub);
                while(index(resultSub) != -1){
                   temp = (Entry)get(resultSub);
                   changeEntry(M,i,temp->col, temp->val);
                   moveNext(resultSub);
                }
          }
    }
 return M;
 }

 // product
 // Returns a reference to a Matrix object representing AB
 // Pre: size(A) == size(B)
 Matrix product(Matrix A, Matrix B){
 Matrix M = NULL;
 double product;
    if(size(A) != size(B)){
       fprintf(stderr,"Matrix Error: Must pass matrices with proper dimensions\n");
       exit(1);
    } 
 M = newMatrix(size(A));
 B = transpose(B);
    for(int i = 1; i < size(A)+1; i++){
       for(int j = 1; j < size(A); j++){
          product = dot(A->matrix[i], B->matrix[j]);
             if(product != 0){
                changeEntry(M,i,j,product);
             }
       }
    }
 return M;
 } 

 // dot
 // Helper Function
 // Calculates product of two matrices
 double dot (List P, List Q){
 Entry tempP = NULL;
 Entry tempQ = NULL;
 double product = 0;
    if(length(P) == 0 || length(Q) == 0){
       return product;
    }
    if(length(P) != 0 && length(Q) != 0){
       moveFront(P);
       moveFront(Q);
       while(index(P) != -1 && index(Q) != -1){
          tempP = (Entry)get(P);
          tempQ = (Entry)get(Q);
             if(tempP->col == tempQ->col){
                product += (tempP->val)*(tempQ->val);
                if(tempP == tempQ){
                   moveNext(P);
                }
                else{
                   moveNext(P);
                   moveNext(Q);
                }
             }
             else if(tempP->col < tempQ->col){
                moveNext(P);
             }
             else{
                moveNext(Q);
             }
       }
    } 
 return product;
 }

 // listAdd
 // Helper Function
 // Computes the sum of two Matrices
 List listAdd(List P, List Q){
 List result = newList();
 Entry tempP = NULL;
 Entry tempQ = NULL;
 Entry temp = NULL;

   if(length(P) == 0 && length(Q) == 0){
      return result;
   }
   if(length(P) != 0 && length(Q) == 0){
      moveFront(P);
         while(index(P) != -1){
            tempP = (Entry)get(P);
            append(result,tempP);
            moveNext(P);
         }
   return result;
   }
   if(length(P) == 0 && length(Q) != 0){
      moveFront(Q);
         while(index(Q) != -1){
            tempQ = (Entry)get(Q);
            append(result,tempQ);
            moveNext(Q);
         }
   return result;
   }
   if(length(P) != 0 && length(Q) != 0){
      moveFront(P);
      moveFront(Q);
         while(index(P) != -1 && index(Q) != -1){
            tempP = get(P);
            tempQ = get(Q);
               if(tempP->col == tempQ->col){
                  temp = newEntry(tempP->col, tempP->val + tempQ->val);
                  append(result, temp);
                     if(tempP == tempQ){
                        moveNext(P);
                     }
                     else{
                        moveNext(P);
                        moveNext(Q);
                     }
               }
               else if(tempP->col < tempQ->col){
                  temp = newEntry(tempP->col, tempP->val);
                  append(result,temp);
                  moveNext(P);
               }
               else if(tempP->col > tempQ->col){
                  temp = newEntry(tempQ->col, tempQ->val);
                  append(result, temp);
                  moveNext(Q);
               }
         }
         while(index(P) != -1){
            tempP = (Entry)get(P);
            append(result, tempP);
            moveNext(P);
         } 
         while(index(Q) != -1){
            temp = (Entry)get(Q);
            append(result,temp);
            moveNext(Q);
         }
   }
 return result;
 }

 // listSub
 // Helper Function
 // Computes the difference between Matrices
 List listSub(List P, List Q){
 List result = newList();
 Entry tempP = NULL;
 Entry tempQ = NULL;
 Entry temp = NULL;
 double diff = 0.0;
    if(length(P) != 0 && length(Q) == 0){
       moveFront(P);
       while(index(P) != -1){
          temp = (Entry)get(P);
          append(result,temp);
          moveNext(P);
       }
    return result;
    }
    if(length(P) == 0 && length(Q) != 0){
       moveFront(Q);
       while(index(Q) != -1){
          tempQ = (Entry)get(Q);
          diff = 0 - temp->val;
          temp = newEntry(tempQ->col, diff);
          append(result, temp);
          moveNext(Q);
       }
    return result;
    }
    if(length(P) != 0 && length(Q) != 0){
       moveFront(P);
       moveFront(Q);
          while(index(P) != -1 && index(Q) != -1){
             tempP = (Entry)get(P);
             tempQ = (Entry)get(Q);
             if(tempP->col == tempQ->col){
                diff = tempP->val - tempQ->val;
                if(diff != 0){
                   temp = newEntry(tempP->col, diff);
                   append(result,temp);
                }
                   if(tempP == tempQ){
                      moveNext(P);
                   }
                   else{
                      moveNext(P);
                      moveNext(Q);
                   }
             }
             else if(tempP->col < tempQ->col){
                if(tempP->val != 0){
                   append(result, tempP);
                }
                moveNext(P);
             }
             else{
                if(tempQ->val != 0){
                   diff = 0 - tempQ->val;
                   temp = newEntry(tempQ->col, diff);
                   append(result,temp);
                }
             moveNext(Q);
             } 
           }
   }  
   while(index(P) != -1){
   tempP = (Entry)get(P);
   temp = newEntry(tempQ->col, diff);
   moveNext(P);
   } 
   while(index(Q) != -1){
      tempQ = (Entry)get(Q);
      diff = 0 - tempQ->val;
      temp = newEntry(tempQ->col,diff);
      append(result, temp);
      moveNext(Q);
   }
 return result;
 }

 // printMatrix()
 // Prints a string representation of Matrix M to filestream out. Zero rows are not printed.
 // Each non-zero is represented as one line consisting of the row number, followed by a colon,
 // a space, then a space separated list of pairs "(col, val)" giving the column numbers
 // and non-zero values in that row. The double val will be rounded to 1 decimal point.
 void printMatrix(FILE* out, Matrix M){
 Entry temp = NULL;   
    if(out == NULL){
       fprintf(stderr,"Matrix Error: Cannot pass NULL File for printing\n");
       exit(1);
    }
    for(int i = 1; i < size(M)+1; i++){
       if(length(M->matrix[i]) != 0){
          moveFront(M->matrix[i]);
          fprintf(out,"%d: ", i);
          while(index(M->matrix[i]) != -1){
             temp = (Entry)get(M->matrix[i]);
             printEntry(out, temp);
             moveNext(M->matrix[i]); 
          }
        fprintf(out,"\n"); 
       }
    } 
 }






